/*
 * Copyright (c) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <errno.h>
#ifndef CONFIG_PINCTRL
#include <zephyr/drivers/pinmux.h>
#endif
#include <zephyr/logging/log.h>
#include "gpio_ec.h"
#include "common_mec172x.h"

LOG_MODULE_REGISTER(gpio_ec, CONFIG_GPIO_EC_LOG_LEVEL);

#define MAX_PINS_PER_PORT	32
#define OCTAL_BASE		8

#if 0
struct gpio_device {
	char name[Z_DEVICE_MAX_NAME_LEN];
	const struct device *port;
};
#else
typedef struct device gpio_device;
#endif
#ifndef CONFIG_PINCTRL
static struct gpio_device pinmux_ports[] = {
	{ "pinmux_000_036", DEVICE_DT_GET(DT_NODELABEL(pinmux_000_036)) },
	{ "pinmux_040_076", DEVICE_DT_GET(DT_NODELABEL(pinmux_040_076)) },
	{ "pinmux_100_136", DEVICE_DT_GET(DT_NODELABEL(pinmux_100_136)) },
	{ "pinmux_140_176", DEVICE_DT_GET(DT_NODELABEL(pinmux_140_176)) },
	{ "pinmux_200_236", DEVICE_DT_GET(DT_NODELABEL(pinmux_200_236)) },
	{ "pinmux_240_276", DEVICE_DT_GET(DT_NODELABEL(pinmux_240_276)) },
};
#endif

static const gpio_device *ports[] = {
#if DT_NODE_HAS_STATUS(DT_INST(0, microchip_xec_gpio_v2), okay)
	DEVICE_DT_GET(DT_INST(0, microchip_xec_gpio_v2)),
#endif
#if DT_NODE_HAS_STATUS(DT_INST(1, microchip_xec_gpio_v2), okay)
	DEVICE_DT_GET(DT_INST(1, microchip_xec_gpio_v2)),
#endif
#if DT_NODE_HAS_STATUS(DT_INST(2, microchip_xec_gpio_v2), okay)
	DEVICE_DT_GET(DT_INST(2, microchip_xec_gpio_v2)),
#endif
#if DT_NODE_HAS_STATUS(DT_INST(3, microchip_xec_gpio_v2), okay)
	DEVICE_DT_GET(DT_INST(3, microchip_xec_gpio_v2)),
#endif
#if DT_NODE_HAS_STATUS(DT_INST(4, microchip_xec_gpio_v2), okay)
	DEVICE_DT_GET(DT_INST(4, microchip_xec_gpio_v2)),
#endif
#if DT_NODE_HAS_STATUS(DT_INST(5, microchip_xec_gpio_v2), okay)
	DEVICE_DT_GET(DT_INST(5, microchip_xec_gpio_v2)),
#endif
#if DT_NODE_HAS_STATUS(DT_INST(0, microchip_xec_vci_v2), okay)
	DEVICE_DT_GET(DT_INST(0, microchip_xec_vci_v2)),
#endif
	/* Handle 1 or more IO expanders */
#ifdef CONFIG_GPIO_PCA95XX
#if DT_NODE_HAS_STATUS(DT_INST(0, nxp_pca95xx), okay)
	{ DT_LABEL(DT_INST(0, nxp_pca95xx)), NULL},
#endif
#if DT_NODE_HAS_STATUS(DT_INST(1, nxp_pca95xx), okay)
	{ DT_LABEL(DT_INST(1, nxp_pca95xx)), NULL},
#endif
#endif
};

struct gpio_port_pin {
	const struct device *gpio_dev;
	gpio_pin_t pin;
};

static uint32_t convert_decimal_to_octal(uint32_t decimal_num)
{
	uint32_t octal_num = 0, i = 1;

	while (decimal_num != 0) {
		octal_num += (decimal_num % OCTAL_BASE) * i;
		decimal_num /= OCTAL_BASE;
		i *= 10;
	}

	return octal_num;
}

uint32_t get_absolute_gpio_num(uint32_t port_pin)
{
	return convert_decimal_to_octal(MAX_PINS_PER_PORT *
					gpio_get_port(port_pin) +
					gpio_get_pin(port_pin));
}

static int validate_device(uint32_t port_pin, struct gpio_port_pin *pp)
{
	uint32_t port_idx;
	gpio_pin_t pin;

	port_idx = gpio_get_port(port_pin);
	pin = gpio_get_pin(port_pin);

	/* Fail gracefully when GPIO table is misconfigured which easily
	 * results in a CPU fault
	 */
	if (port_idx >= ARRAY_SIZE(ports)) {
		return -EINVAL;
	}
#if 0
	if (!ports[port_idx].port) {
		LOG_ERR("Invalid gpio dev");
		return -ENODEV;
	}

	LOG_DBG("%s: port idx: %d port ptr: %p pin: %d",
		__func__, port_idx, ports[port_idx].port, pin);

	pp->gpio_dev = ports[port_idx].port;
#else
	if (!ports[port_idx]) {
		LOG_ERR("Invalid gpio dev");
		return -ENODEV;
	}
	
	pp->gpio_dev = ports[port_idx];
#endif
	pp->pin = pin;

	return 0;
}

static bool is_dummy_gpio(uint32_t port_pin)
{
	uint32_t port_idx;

	port_idx = gpio_get_port(port_pin);
	return (port_idx == EC_DUMMY_GPIO_PORT);
}

static bool gpio_read_dummy_pin(uint32_t port_pin)
{
	return gpio_get_pin(port_pin);
}

int gpio_init(void)
{
#if 0
	const struct device *gpio_dev;

	for (int i = 0; i < ARRAY_SIZE(ports); i++) {
		gpio_dev = device_get_binding(ports[i].name);

		if (!gpio_dev) {
			LOG_ERR("Unable to find %s", ports[i].name);
		}

		ports[i].port = gpio_dev;
		LOG_DBG("[Port %c] %p", (i+0x31), gpio_dev);
	}
#endif
	return 0;
}

int gpio_configure_pin(uint32_t port_pin, gpio_flags_t flags)
{
	int ret;
	struct gpio_port_pin pp = { 0, 0 };

	ret = validate_device(port_pin, &pp);
	if (ret) {
		LOG_ERR("Invalid pin %d", pp.pin);
		return ret;
	}

	ret = gpio_pin_configure(pp.gpio_dev, pp.pin, flags);

	if (ret) {
		LOG_ERR("Failed to configure pin %d", pp.pin);
		return ret;
	}

	return 0;
}

int gpio_configure_array(struct gpio_ec_config *gpios, uint32_t len)
{
	int ret;
	struct gpio_port_pin pp = { 0, 0 };

	/* Configure static board gpios */
	for (int i = 0; i < len; i++) {
		if (is_dummy_gpio(gpios[i].port_pin)) {
			continue;
		}

		ret = validate_device(gpios[i].port_pin, &pp);
		if (ret) {
			return ret;
		}

		LOG_DBG("i: %d port: %p pin: %d cfg: %x", i, pp.gpio_dev,
			pp.pin,
			gpios[i].cfg);

		if (!pp.gpio_dev) {
			LOG_ERR("Invalid port at %d", i);
			continue;
		}

		ret = gpio_pin_configure(pp.gpio_dev, pp.pin,
					 gpios[i].cfg);

		if (ret) {
			LOG_ERR("Config fail: %d i:%d port:%p pin: %d cfg: %d",
				ret, i, pp.gpio_dev, pp.pin,
				gpios[i].cfg);
		}
	}

	return 0;
}

int gpio_write_pin(uint32_t port_pin, int value)
{
	int ret;
	struct gpio_port_pin pp = { 0, 0 };

	if (is_dummy_gpio(port_pin)) {
		return 0;
	}

	ret = validate_device(port_pin, &pp);
	if (ret) {
		return ret;
	}

	return gpio_pin_set(pp.gpio_dev, pp.pin, value);
}

int gpio_read_pin(uint32_t port_pin)
{
	int ret;
	struct gpio_port_pin pp = { 0, 0 };

	if (is_dummy_gpio(port_pin)) {
		return gpio_read_dummy_pin(port_pin);
	}

	ret = validate_device(port_pin, &pp);
	if (ret) {
		return ret;
	}

	return gpio_pin_get(pp.gpio_dev, pp.pin);
}

int gpio_init_callback_pin(uint32_t port_pin,
			   struct gpio_callback *callback,
			   gpio_callback_handler_t handler)
{
	int ret;
	struct gpio_port_pin pp = { 0, 0 };

	if (is_dummy_gpio(port_pin)) {
		return 0;
	}

	ret = validate_device(port_pin, &pp);
	if (ret) {
		return ret;
	}

	/* zephyr function is void */
	gpio_init_callback(callback, handler, BIT(pp.pin));

	return 0;
}

int gpio_add_callback_pin(uint32_t port_pin,
			  struct gpio_callback *callback)
{
	int ret;
	struct gpio_port_pin pp = { 0, 0 };

	if (is_dummy_gpio(port_pin)) {
		return 0;
	}

	ret = validate_device(port_pin, &pp);
	if (ret) {
		return ret;
	}

	return gpio_add_callback(pp.gpio_dev, callback);
}

int gpio_remove_callback_pin(uint32_t port_pin,
			     struct gpio_callback *callback)
{
	int ret;
	struct gpio_port_pin pp = { 0, 0 };

	if (is_dummy_gpio(port_pin)) {
		return 0;
	}

	ret = validate_device(port_pin, &pp);
	if (ret) {
		return ret;
	}

	return gpio_remove_callback(pp.gpio_dev, callback);
}

int gpio_interrupt_configure_pin(uint32_t port_pin, gpio_flags_t flags)
{
	int ret;
	struct gpio_port_pin pp = { 0, 0 };

	if (is_dummy_gpio(port_pin)) {
		return 0;
	}

	ret = validate_device(port_pin, &pp);
	if (ret) {
		return ret;
	}

	return gpio_pin_interrupt_configure(pp.gpio_dev, pp.pin, flags);
}

bool gpio_port_enabled(uint32_t port_pin)
{
	int ret;
	struct gpio_port_pin pp = { 0, 0 };

	if (is_dummy_gpio(port_pin)) {
		return 0;
	}

	ret = validate_device(port_pin, &pp);

	return ret == 0;
}

int gpio_force_configure_pin(uint32_t port_pin, gpio_flags_t flags)
{
	int ret;
	uint32_t port_idx;
	struct gpio_port_pin pp = { 0, 0 };

	ret = validate_device(port_pin, &pp);
	if (ret) {
		LOG_ERR("Invalid pin %d", pp.pin);
		return ret;
	}

	port_idx = gpio_get_port(port_pin);

#ifndef CONFIG_PINCTRL
	LOG_WRN("%s pinmux port: %d pin: %d ", __func__, port_idx, pp.pin);
	ret = pinmux_pin_set(pinmux_ports[port_idx].port, pp.pin,
			     MCHP_GPIO_CTRL_MUX_F0);
	if (ret) {
		LOG_ERR("Failed to switch muxing %d", pp.pin);
		return ret;
	}

	ret = gpio_pin_configure(pp.gpio_dev, pp.pin, flags);

	if (ret) {
		LOG_ERR("Failed to configure pin %d", pp.pin);
		return ret;
	}
#endif
	return 0;
}
