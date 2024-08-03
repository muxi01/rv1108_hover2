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

#include "socket_client.h"

int main(int argc, char** argv) {
  rockchip::ipc::SocketClient *client = new rockchip::ipc::SocketClient();

  client->Connect("/tmp/socket/wlan_service.sock");
  client->Send("set_power/on");
  client->Disconnect();

  // client->Connect("/tmp/socket/wlan_service.sock");
  // client->Send(rockchip::WlanServiceCommand::kServiceExit);
  // client->Disconnect();
  return 0;
}