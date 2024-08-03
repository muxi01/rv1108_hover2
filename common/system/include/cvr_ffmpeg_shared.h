#ifndef __CVR_FFMEPG_SHARED_H__
#define __CVR_FFMEPG_SHARED_H__

#include <mpp/vpu_api.h>

/* encoder */
//copy from mpp_include/mpp_utils.h, TODO replace the vpu_api.h
typedef struct {
    uint8_t *vir_addr;
    int phy_fd;//-1 means normal memory
    void *handle;
    size_t buf_size;
}DataBuffer_t;

typedef DataBuffer_t* pdata_handle;//typedef void* pdata_handle;

/* decoder */
typedef void (*free_vpu_mem)(void *ctx, void *mem);
typedef struct {
	VPUMemLinear_t image_buf;
    void *rkdec_ctx;
    free_vpu_mem free_func;
}DataBuffer_VPU_t;

typedef DataBuffer_VPU_t* image_handle;

#endif
