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

#include "cmdline/cmdline.h"

static int wlan_start(void) {
  return 0;
}

static int wlan_stop(void) {
  return 0;
}

int main(int argc, char **argv) {
  cmdline::parser cmdline_parser;
  cmdline_parser.add<std::string>("mode", 'm',
                                  "WLAN mode, station/ap",
                                  false, "station",
                                  cmdline::oneof<std::string>("station", "ap"));
  cmdline_parser.parse_check(argc, argv);

  rockchip::WlanService* service = new rockchip::WlanService();
  service->Run();

  delete service;
  return 0;
}