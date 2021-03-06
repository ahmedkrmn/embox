/**
 * @file stm32_spi1.c
 * @brief
 * @author Denis Deryugin <deryugin.denis@gmail.com>
 * @version
 * @date 25.12.2019
 */

#include <string.h>
#include <drivers/spi.h>
#include <drivers/spi/stm32_spi_conf.h>

#include <embox/unit.h>

#include "stm32_spi.h"

EMBOX_UNIT_INIT(stm32_spi1_init);

static struct stm32_spi stm32_spi1 = {
	.nss_port = SPI1_NSS_GPIO_PORT,
	.nss_pin  = SPI1_NSS_PIN
};

static int stm32_spi1_init(void) {
	GPIO_InitTypeDef  GPIO_InitStruct;

	spi1_enable_gpio_clocks();
	spi1_enable_spi_clocks();

	stm32_spi_init(&stm32_spi1, SPI1);

	memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
	GPIO_InitStruct.Pin       = SPI1_SCK_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_LOW;
	GPIO_InitStruct.Alternate = SPI1_SCK_AF;
	HAL_GPIO_Init(SPI1_SCK_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = SPI1_MISO_PIN;
	GPIO_InitStruct.Alternate = SPI1_MISO_AF;
	HAL_GPIO_Init(SPI1_MISO_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = SPI1_MOSI_PIN;
	GPIO_InitStruct.Alternate = SPI1_MOSI_AF;
	HAL_GPIO_Init(SPI1_MOSI_GPIO_PORT, &GPIO_InitStruct);

	/* Chip Select is usual GPIO pin. */
	GPIO_InitStruct.Pin       = SPI1_NSS_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	HAL_GPIO_Init(SPI1_NSS_GPIO_PORT, &GPIO_InitStruct);

	/* Chip Select is in inactive state by default. */
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_PORT, SPI1_NSS_PIN, GPIO_PIN_SET);

	return 0;
}

SPI_DEV_DEF("STM32 SPI", &stm32_spi_ops, &stm32_spi1, 1);
