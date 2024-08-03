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
#include "console.h"

#include <stdio.h>

namespace rockchip {
namespace utils {

const bool Console::Run(const char *cmdline) {
  FILE *fp = popen(cmdline, "r");
  if (!fp) {
    printf("Running cmdline failed: %s\n", cmdline);
    return false;
  }

  pclose(fp);
  return true;
}

} // namespace utils
} // namespace rockchip