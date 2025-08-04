#ifndef ZEPHYR_INCLUDE_DRIVERS_FAKEE_HWW_H
#define ZEPHYR_INCLUDE_DRIVERS_FAKEE_HWW_H
#include <zephyr/device.h>

struct fakee_driver_api {
    /** Print function for the fake hardware */
    int (*fakee_api_print)(const struct device *dev);
};

#endif /* ZEPHYR_INCLUDE_DRIVERS_FAKEE_HWW_H */