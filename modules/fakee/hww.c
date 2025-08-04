#include <zephyr/types.h>
#include <zephyr/device.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "hww.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DT_DRV_COMPAT hww_fakee

static int fake_print(const struct device *dev)
{
	const struct fakee_driver_api *api = (const struct fakee_driver_api *)dev->api;
    printk("Fake HWW print function called for device from module folder: %s\n", dev->name);

	return 123; //0x7B
}

/**
 * @brief LED strip driver API
 *
 * This is the mandatory API any LED strip driver needs to expose.
 */
// static DEVICE_API(fake, hw_func) =
// {
//     .fake_api_print = fake_print,
// };

static const struct fakee_driver_api fakee_hww_drv_api_struct = {
    .fakee_api_print = fake_print,
};

static int fakee_hww_init(const struct device *dev)
{
    printk("Fake HWW driver initialized for device: %s\n", dev->name);
    return 0;
}

DEVICE_DT_DEFINE(DT_ALIAS(my_hw), fakee_hww_init, NULL, NULL, NULL, POST_KERNEL,
              CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &fakee_hww_drv_api_struct);

// DEVICE_DT_INST_DEFINE(0, fake_hww_init, NULL, NULL, NULL, POST_KERNEL,
//                   CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &fake_hww_drv_api_struct);

#ifdef __cplusplus
}
#endif