/**
 * Copyright (C) 2016 Fuzhou Rockchip Electronics Co., Ltd
 * author: ZhiChao Yu zhichao.yu@rock-chips.com
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include "wlan_service.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <string>
#include <vector>

#include "console.h"

namespace rockchip {

const char* WlanService::kWlanServiceSocketName = "/tmp/socket/wlan_service.sock";
const int WlanService::kWlanServiceCommandMaxLen = 128;

// TODO
void SplitString(const std::string& str,
                 std::vector<std::string>& v, const std::string& delim) {
  std::string::size_type pos1, pos2;
  pos2 = str.find(delim);
  pos1 = 0;
  while(std::string::npos != pos2) {
    v.push_back(str.substr(pos1, pos2 - pos1));

    pos1 = pos2 + delim.size();
    pos2 = str.find(delim, pos1);
  }
  if(pos1 != str.length())
    v.push_back(str.substr(pos1));
}

// TODO
int WriteAccesspointConfigFile(const char* name, const char* password) {
  FILE* fp;
  char text[1024] = {0};
  fp = fopen("/tmp/hostapd.conf", "wt+");

  if (fp != 0) {
    fputs("interface=wlan0\n", fp);
    fputs("driver=nl80211\n", fp);
    fputs("ssid=", fp);
    fputs(name, fp);
    fputs("\n", fp);
    fputs("channel=6\n", fp);
    fputs("hw_mode=g\n", fp);
    fputs("ieee80211n=1\n", fp);
    fputs("ht_capab=[SHORT-GI-20]\n", fp);
    fputs("ignore_broadcast_ssid=0\n", fp);
    fputs("auth_algs=1\n", fp);
    fputs("wpa=3\n", fp);
    fputs("wpa_passphrase=", fp);
    fputs(password, fp);
    fputs("\n", fp);
    fputs("wpa_key_mgmt=WPA-PSK\n", fp);
    fputs("wpa_pairwise=TKIP\n", fp);
    fputs("rsn_pairwise=CCMP", fp);

    fclose(fp);
    return 0;
  }
  return -1;
}

// TODO
int WriteStationConfigFile(const char* name, const char* password) {
  FILE* fp;
  char text[1024] = {0};
  fp = fopen("/tmp/wpa_supplicant.config", "wt+");

  if (fp != 0) {
    fputs("ctrl_interface=/var/run/wpa_supplicant\n", fp);
    fputs("ap_scan=1\n", fp);
    fputs("network={\n", fp);
    fputs("proto=RSN\n", fp);
    fputs("key_mgmt=WPA-PSK\n", fp);
    fputs("pairwise=CCMP TKIP\n", fp);
    fputs("group=CCMP TKIP\n", fp);
    fputs("ssid=\"", fp);
    fputs(name, fp);
    fputs("\"\n", fp);
    fputs("psk=\"", fp);
    fputs(password, fp);
    fputs("\"\n", fp);
    fputs("}", fp);
    fclose(fp);
    return 0;
  }
  return -1;
}

// TODO
void WlanAccesspointStart(const char* ssid, const char* password) {
  WriteAccesspointConfigFile(ssid, password);

  printf("wlan_service: accesspoint start: ssid = %s, password = %s\n",
         ssid, password);

  sleep(2);

  utils::Console::Run("echo \"/system/etc/firmware/fw_bcm4339a0_ag_apsta.bin\" "
                      "> /sys/module/bcmdhd/parameters/firmware_path");
  utils::Console::Run("ifconfig lo 127.0.0.1 netmask 255.255.255.0");
  utils::Console::Run("ifconfig wlan0 up");
  utils::Console::Run("ifconfig wlan0 192.168.100.1 netmask 255.255.255.0");
  utils::Console::Run("/usr/local/sbin/dnsmasq -C /etc/dnsmasq.conf");
  utils::Console::Run("/usr/local/sbin/hostapd /tmp/hostapd.conf -B");
}

// TODO
void WlanStationStart(const char* ssid, const char* password) {
  WriteStationConfigFile(ssid, password);

  printf("wlan_service: station start: ssid = %s, password = %s\n",
         ssid, password);

  sleep(1);

  utils::Console::Run("ifconfig wlan0 up");
  utils::Console::Run("/usr/local/sbin/wpa_supplicant"
                      " -Dnl80211 -c /tmp/wpa_supplicant.config -iwlan0 -B");
  utils::Console::Run("/sbin/udhcpc -i wlan0 -b");
}

bool WlanService::WlanOn(void) {
  printf("wlan_service: wlan on.\n");

  // utils::Console::Run("echo 1 > /sys/class/rkwifi/driver");

  return true;
}

bool WlanService::WlanOff(void) {
  printf("wlan_service: wlan off.\n");

  utils::Console::Run("kill -15 $(pidof hostapd)");
  utils::Console::Run("kill -15 $(pidof dnsmasq)");

  // utils::Console::Run("echo 0 > /sys/class/rkwifi/driver");
  return true;
}

bool WlanService::WlanSetMode(const std::string& mode,
                              const std::string& ssid,
                              const std::string& password) {
  if (mode_.empty() == false) {
    printf("wlan_service: already in %s mode, cannot set again.\n",
           mode_.c_str());
    return false;
  }

  if (mode == "station") {
    WlanStationStart(ssid.c_str(), password.c_str());
    mode_ = "station";
  } else if (mode == "ap") {
    WlanAccesspointStart(ssid.c_str(), password.c_str());
    mode_ = "ap";
  } else {
    printf("wlan_service: invalid wlan mode: %s.\n", mode.c_str());
    return false;
  }
  return true;
}

const void WlanService::ProcessCommand(const std::string& cmdline) {
  printf("wlan_service: Received a cmdline: %s.\n", cmdline.c_str());

  std::vector<std::string> argv;
  SplitString(cmdline, argv, std::string("/"));

  std::string cmd = argv[0];
  if (cmd == "exit") {
    exit(0);
  } else if (cmd == "set_power") {
    std::string power = argv[1];
    if (power == "on")
      WlanOn();
    else if (power == "off")
      WlanOff();
    else
      printf("wlan_service: invliad parameter of set_power.\n");
  } else if (cmd == "set_mode") {
    std::string mode = argv[1];
    std::string ssid = argv[2];
    std::string password = argv[3];
    WlanSetMode(mode, ssid, password);
  } else {
    printf("wlan_service: unknow command: %s.\n", cmd.c_str());
  }
}

int WlanService::Run() {
  utils::Console::Run("mkdir -p /tmp/socket");

  Listen(WlanService::kWlanServiceSocketName);
  while (1) {
    char buf[128] = { 0 }; // TODO, fixme
    bool result;

    result = Accept();
    if (result == false)
      continue;

    result = Receive(buf, 128);
    if (result == true) {
      std::string cmd(buf);
      ProcessCommand(cmd);
    }

    Disconnect();
  }
}

} // namespace rockchip