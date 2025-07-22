#include <zephyr/types.h>
#include <zephyr/device.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "hww.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DT_DRV_COMPAT fake_hww

static int fake_print(const struct device *dev)
{
	const struct fake_driver_api *api = (const struct fake_driver_api *)dev->api;
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

static const struct fake_driver_api fake_hww_drv_api_struct = {
    .fake_api_print = fake_print,
};

static int fake_hww_init(const struct device *dev)
{
    printk("Fake HWW driver initialized for device: %s\n", dev->name);
    return 0;
}

DEVICE_DEFINE(fakee_hww, "FAKEE_HWW_INIT", fake_hww_init, NULL, NULL, NULL,
              POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &fake_hww_drv_api_struct);

// HWW_DEVICE_INIT(0)

// DT_INST_FOREACH_STATUS_OKAY(HWW_DEVICE_INIT)

#ifdef __cplusplus
}
#endif