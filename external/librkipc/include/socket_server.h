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
#ifndef RKIPC_SOCKET_SERVER_H_
#define RKIPC_SOCKET_SERVER_H_

#include <unistd.h>

namespace rockchip {
namespace ipc {

// SocketServer, use to receive message from client
// TODO, only support only one connection
class SocketServer {
public:
  SocketServer() {
    fd_ = -1;
    client_fd_ = -1;
  }

  virtual ~SocketServer() {
    Disconnect();

    if (fd_ > 0) {
      close(fd_);
      fd_ = -1;
    }
  }

  // Create a server endpoint of a connection.
  // Returns true if socket fd is OK.
  bool Listen(const char* server_name);

  void Disconnect(void) {
    if (client_fd_ > 0) {
      close(client_fd_);
      client_fd_ = -1;
    }
  }

  // Wait a client connection
  bool Accept(void);

  // Receive messages from the client
  bool Receive(char* buf, size_t len);

  static const int kMaxConnection;

private:
  int fd_;
  int client_fd_;
};

} // namespace ipc
} // namespace rockchip

#endif // RKIPC_SOCKET_SERVER_H_