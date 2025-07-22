# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.20.0)

zephyr_library()
zephyr_library_sources_ifdef(CONFIG_HWW_FAKEE hww.c hww.h)
