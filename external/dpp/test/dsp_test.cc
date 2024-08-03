#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ion/ion.h>
#include "dsp_ioctl.h"

#define TEST_SIZE (1280 * 1280)

struct test_params {
  unsigned long src_phy;
  unsigned long dst_phy;
};

static int prepare_test_params(struct test_params *params)
{
  int ret = -1;
  int client = -1;
  ion_user_handle_t src_hdl, dst_hdl;

  client = ion_open();
  if (client < 0) {
    std::cout << "Cannot open ion device" << std::endl;
    return -1;
  }

  ret = ion_alloc(client, TEST_SIZE, 0, ION_HEAP_TYPE_DMA_MASK, 0, &src_hdl);
  if (ret) {
    std::cout << "Cannot alloc test src buffer" << std::endl;
    return ret;
  }

  ret = ion_alloc(client, TEST_SIZE, 0, ION_HEAP_TYPE_DMA_MASK, 0, &dst_hdl);
  if (ret) {
    std::cout << "Cannot alloc test dst buffer" << std::endl;
    return ret;
  }

  ion_get_phys(client, src_hdl, &params->src_phy);
  ion_get_phys(client, dst_hdl, &params->dst_phy);

  ion_close(client);

  return 0;
}

int main(int argc, char **argv)
{
  int dsp_fd = -1;
  struct dsp_user_work test_work;
  struct test_params params;

  memset(&test_work, 0, sizeof(test_work));
  memset(&params, 0, sizeof(params));

  // Open DSP device
  dsp_fd = open("/dev/dsp", O_RDWR);
  if (dsp_fd < 0) {
    std::cout << "Cannot open dsp device" << std::endl;
    return -1;
  }

  // Initialize work struct
  if (prepare_test_params(&params)) {
    std::cout << "Prepare test parameter failed" << std::endl;
    return -1;
  }
  test_work.magic = DSP_RENDER_WORK_MAGIC;
  test_work.id = 0x78787878;
  test_work.render.type = DSP_RENDER_TEST;
  test_work.render.packet_virt = (u32)&params;
  test_work.render.size = sizeof(params);

  // Request DSP work
  std::cout << "Test work start" << std::endl;
  ioctl(dsp_fd, DSP_IOC_QUEUE_WORK, &test_work);
  ioctl(dsp_fd, DSP_IOC_DEQUEUE_WORK, &test_work);
  std::cout << "Test work done" << std::endl;

  close(dsp_fd);
  return 0;
}
