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
#ifndef WLAN_SERVICE_H_
#define WLAN_SERVICE_H_
#include <string>

#include "socket_server.h"

namespace rockchip {

class WlanService : ipc::SocketServer{
public:
  WlanService() {}
  ~WlanService() {}

  int Run(void);

  // Wlan power on
  // command line: "set_power/on"
  bool WlanOn(void);

  // Wlan power off
  // command line: "set_power/off"
  bool WlanOff(void);

  // Set wlan station/ap mode
  // command line: "set_mode/station[ap]/ssid/password"
  bool WlanSetMode(const std::string& mode,
                   const std::string& ssid,
                   const std::string& password);

private:
  std::string mode_;

  static const char* kWlanServiceSocketName;
  static const int kWlanServiceCommandMaxLen;

  const void ProcessCommand(const std::string& cmd);
};

} // namespace rockchip

#endif // WLAN_SERVICE_H_