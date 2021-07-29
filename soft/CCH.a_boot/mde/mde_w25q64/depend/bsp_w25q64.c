//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#include "gd32f4xx.h"
#include <stdbool.h>
//------------------------------E N D-------------------------------------------     GPIOC       //左边GPIO
#define SPI_CS_PIN       GPIO_PIN_12
#define SPI_CLK_PIN      GPIO_PIN_13
#define SPI_MISO_PIN     GPIO_PIN_14
#define SPI_MOSI_PIN     GPIO_PIN_15
#define SPI_PORT         GPIOB

void bsp_spi1_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_SPI1);
    /* SPI1 GPIO config */
    gpio_af_set(SPI_PORT, GPIO_AF_5, SPI_CLK_PIN | SPI_MISO_PIN |SPI_MOSI_PIN);
    gpio_mode_set(SPI_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, SPI_CLK_PIN | SPI_MISO_PIN |SPI_MOSI_PIN);
    gpio_output_options_set(SPI_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI_CLK_PIN | SPI_MISO_PIN |SPI_MOSI_PIN);

    /* set SPI1_NSS as GPIO*/
    gpio_mode_set(SPI_PORT,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,SPI_CS_PIN);
    gpio_output_options_set(SPI_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI_CS_PIN);
    
    spi_parameter_struct spi_init_struct;

    /* SPI1 parameter config */
    spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode          = SPI_MASTER;
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
    spi_init_struct.nss                  = SPI_NSS_SOFT;
    spi_init_struct.prescale             = SPI_PSC_32;
    spi_init_struct.endian               = SPI_ENDIAN_MSB;
    spi_init(SPI1, &spi_init_struct);
    gpio_bit_set(SPI_PORT,SPI_CS_PIN);
     /* SPI enable */
    spi_enable(SPI1);
    gpio_bit_reset(SPI_PORT,SPI_CS_PIN);
}


void bsp_nss_high(void)
{
    gpio_bit_set(SPI_PORT,SPI_CS_PIN);
}

void bsp_nss_low(void)
{
    gpio_bit_reset(SPI_PORT,SPI_CS_PIN);
}
//-----------------------BSP_LED.c--END-----------------------------------
