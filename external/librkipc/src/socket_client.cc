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

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stddef.h>

#include <sys/un.h>
#include <sys/socket.h>

namespace rockchip {
namespace ipc {

bool SocketClient::Connect(const char* server_name) {
  assert(server_name != NULL);
  assert(fd_ < 0);

  int fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd < 0) {
    printf("SocketClient: Create socket failed.\n");
    return false;
  }

  // Fill socket address structure with our address.
  struct sockaddr_un sun;
  memset(&sun, 0, sizeof(sun));
  sun.sun_family = AF_UNIX;
  sprintf(sun.sun_path, "/tmp/socket/ipc%05d.sock", getpid());
  int len = offsetof(struct sockaddr_un, sun_path) + strlen(sun.sun_path);
  unlink(sun.sun_path);
  if (bind(fd, (struct sockaddr *)&sun, len) < 0) {
    printf("SocketClient: Bind socket failed.\n");
    close(fd);
    return false;
  }

  // Fill socket address structure with server's address.
  memset(&sun, 0, sizeof(sun));
  sun.sun_family = AF_UNIX;
  strcpy(sun.sun_path, server_name);
  len = offsetof(struct sockaddr_un, sun_path) + strlen(server_name);
  if (connect(fd, (struct sockaddr *)&sun, len) < 0) {
    printf("SocketClient: Bind server socket failed.\n");
    close(fd);
    return false;
  }

  fd_ = fd;
  return true;
}

bool SocketClient::Send(const char* msg) {
  assert(msg != NULL);
  assert(fd_ > 0);

  int len = strlen(msg);
  printf("SocketClient: Send a message to server: %s.\n", msg);
  int send_bytes = send(fd_, msg, len, 0);
  if (send_bytes < -1) {
    printf("SocketClient: Send message to server failed.\n");
    return false;
  }

  return true;
}

} // namespace ipc
} // namespace rockchip