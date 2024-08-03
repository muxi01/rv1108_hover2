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
#ifndef RKIPC_SOCKET_CLIENT_H_
#define RKIPC_SOCKET_CLIENT_H_

#include <unistd.h>

namespace rockchip {
namespace ipc {

class SocketClient {
public:
  SocketClient() {
    fd_ = -1;
  }

  virtual ~SocketClient() {
    Disconnect();
  }

  // Create a client endpoint and connect to a server.
  // If success the client socket fd will be save in fd_
  // and return true else retrun false.
  bool Connect(const char* server_name);

  // Disconnect the connection to server socket.
  void Disconnect(void) {
    if (fd_ > 0) {
      close(fd_);
      fd_ = -1;
    }
  }

  // Send a message to the connected server.
  bool Send(const char* msg);

private:
  int fd_;
};

} // namespace ipc
} // namespace rockchip

#endif // RKIPC_SOCKET_CLIENT_H_