/**
 * Copyright (C) 2015 Fuzhou Rockchip Electronics Co., Ltd
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
 *
 */
#ifndef _ARCH_ARM_MACH_RK_DSP_H_
#define _ARCH_ARM_MACH_RK_DSP_H_
#include <sys/ioctl.h>

#define u32 unsigned int
#define s32 signed int
#define u16 unsigned short
#define s16 signed short
#define s8  unsigned char
#define u8  signed char

#define DSP_MAX_IMAGE 8

/*
 * DSP driver ioctl definition
 */
#define DSP_IOC_MAGIC             'x'
#define DSP_IOC_QUEUE_WORK         _IOW(DSP_IOC_MAGIC, 1, unsigned long)
#define DSP_IOC_DEQUEUE_WORK       _IOR(DSP_IOC_MAGIC, 2, unsigned long)

/*
 * DSP error codes which will be returned in result
 */
#define DSP_WORK_SUCCESS   0x00000000
#define DSP_WORK_EABANDON  0x80000001
#define DSP_WORK_ECOPY     0x80000002
#define DSP_WORK_ETIMEOUT  0x80000003

/*
 * User work magic, used by dsp kernel driver to check
 * the work parameter is valid or not
 */
#define DSP_RENDER_WORK_MAGIC 0x20462046
#define DSP_CONFIG_WORK_MAGIC 0x95279527

/*
 * DSP render types. User application should set type
 * in the type member of struct dsp_render_work
 */
#define DSP_RENDER_COPY    0x00000001
#define DSP_RENDER_ADAS    0x00000002
#define DSP_RENDER_2DNR    0x00000004
#define DSP_RENDER_3DNR    0x00000008
#define DSP_RENDER_HDR     0x00000010
#define DSP_RENDER_DEFOG   0x00000020
#define DSP_RENDER_LLE     0x00000040
#define DSP_RENDER_TEST    0x80000000

/*
 * DSP config types
 */
#define DSP_CONFIG_INIT   0x80000001

enum dsp_work_type {
	DSP_RENDER_WORK = 1,
	DSP_CONFIG_WORK = 2,
};

/*
 * dsp_render_params - parameters used by DSP core
 * hardware to render a frame
 *
 * @type: render type, DSP_RENDER_3DNR etc
 * @reserved: reserved for kernel driver use
 * @packet_virt: packet virt address
 * @size: render algrithm config packet size
 */
struct dsp_render_params {
	u32 type;
	u32 reserved;
	u32 packet_virt;
	u32 size;
};


/*
 * dsp_user_work - This struct is used by user ioctl
 *
 * @magic: work magic should be DSP_RENDER_WORK_MAGIC
 * @id: work id
 * @result: work result, if success result is 0
 * @render: render params
 */
struct dsp_user_work {
	u32 magic;
	u32 id;
	u32 result;

	struct dsp_render_params render;
};

#endif
