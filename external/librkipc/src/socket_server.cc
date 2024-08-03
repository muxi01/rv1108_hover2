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
#include "socket_server.h"

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stddef.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>

namespace rockchip {
namespace ipc {

const int SocketServer::kMaxConnection = 8;

bool SocketServer::Listen(const char* server_name) {
  assert(server_name != NULL);
  assert(fd_ < 0);

  printf("SocketServer: Listen to %s.\n", server_name);

  int fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd < 0) {
    printf("SocketServer: Create server socket failed.\n");
    return false;
  }

  struct sockaddr_un sun;
  unlink(server_name);
  memset(&sun, 0, sizeof(sun));
  sun.sun_family = AF_UNIX;
  strcpy(sun.sun_path, server_name);
  int len = offsetof(struct sockaddr_un, sun_path) + strlen(server_name);
  if (int ret = bind(fd, (struct sockaddr *)&sun, len) < 0) {
    printf("SocketServer: Bind socket failed, ret=%d.\n", ret);
    close(fd);
    return false;
  }

  if (listen(fd, kMaxConnection) < 0) {
    printf("SocketServer: Listen socket failed.\n");
    close(fd);
    return false;
  }

  fd_ = fd;
  return true;
}

bool SocketServer::Accept(void) {
  assert(client_fd_ < 0);

  printf("SocketServer: Wait a client connection.\n");

  int client_fd;
  struct sockaddr_un sun;
  int len = sizeof(sun);
  while (1) {
    client_fd = accept(fd_, (struct sockaddr *)&sun, (socklen_t *)&len);
    if (client_fd < 0) {
      if (EINTR == errno) {
        printf("SocketServer: Accept failed by EINTR, continue.\n");
        continue;
      } else {
        printf("SocketServer: Accept failed, errno=%d.\n", errno);
        return false;
      }
    }
    break;
  }

  len -= offsetof(struct sockaddr_un, sun_path);
  sun.sun_path[len] = 0;

  struct stat statbuf;
  if (stat(sun.sun_path, &statbuf) < 0) {
    close(client_fd);
    printf("SocketServer: Call stat failed.\n");
    return false;
  }

  if (!S_ISSOCK(statbuf.st_mode)) {
    printf("SocketServer: Invalid socket.\n");
    close(client_fd);
    return false;
  }

  unlink(sun.sun_path);
  client_fd_ = client_fd;
  return true;
}

bool SocketServer::Receive(char* buf, size_t len) {
  assert(buf != NULL);
  assert(len > 0);

  printf("SocketServer: Ready to receive message from client.\n");

  const int received_bytes = recv(client_fd_, buf, len, 0);
  if (received_bytes < -2) {
    printf("SocketServer: Failed to reveived data.\n");
    return false;
  }

  printf("SocketServer: Reveived a message: %s.\n", buf);
  return true;
}

} // namespace ipc
} // namespace rockchip