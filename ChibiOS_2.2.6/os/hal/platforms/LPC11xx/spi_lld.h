/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,2011 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.

                                      ---

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes ChibiOS/RT, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/

/**
 * @file    LPC11xx/spi_lld.h
 * @brief   LPC11xx low level SPI driver header.
 *
 * @addtogroup SPI
 * @{
 */

#ifndef _SPI_LLD_H_
#define _SPI_LLD_H_

#if HAL_USE_SPI || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Hardware FIFO depth.
 */
#define LPC11xx_SSP_FIFO_DEPTH  8

#define CR0_DSSMASK             0x0F
#define CR0_DSS4BIT             3
#define CR0_DSS5BIT             4
#define CR0_DSS6BIT             5
#define CR0_DSS7BIT             6
#define CR0_DSS8BIT             7
#define CR0_DSS9BIT             8
#define CR0_DSS10BIT            9
#define CR0_DSS11BIT            0xA
#define CR0_DSS12BIT            0xB
#define CR0_DSS13BIT            0xC
#define CR0_DSS14BIT            0xD
#define CR0_DSS15BIT            0xE
#define CR0_DSS16BIT            0xF
#define CR0_FRFSPI              0
#define CR0_FRFSSI              0x10
#define CR0_FRFMW               0x20
#define CR0_CPOL                0x40
#define CR0_CPHA                0x80
#define CR0_CLOCKRATE(n)        ((n) << 8)

#define CR1_LBM                 1
#define CR1_SSE                 2
#define CR1_MS                  4
#define CR1_SOD                 8

#define SR_TFE                  1
#define SR_TNF                  2
#define SR_RNE                  4
#define SR_RFF                  8
#define SR_BSY                  16

#define IMSC_ROR                1
#define IMSC_RT                 2
#define IMSC_RX                 4
#define IMSC_TX                 8

#define RIS_ROR                 1
#define RIS_RT                  2
#define RIS_RX                  4
#define RIS_TX                  8

#define MIS_ROR                 1
#define MIS_RT                  2
#define MIS_RX                  4
#define MIS_TX                  8

#define ICR_ROR                 1
#define ICR_RT                  2

/**
 * @brief   SCK0 signal assigned to pin PIO0_10.
 */
#define SCK0_IS_PIO0_10         0

/**
 * @brief   SCK0 signal assigned to pin PIO2_11.
 */
#define SCK0_IS_PIO2_11         1

/**
 * @brief   SCK0 signal assigned to pin PIO0_6.
 */
#define SCK0_IS_PIO0_6          2

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @brief   SPI1 driver enable switch.
 * @details If set to @p TRUE the support for device SSP0 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(LPC11xx_SPI_USE_SSP0) || defined(__DOXYGEN__)
#define LPC11xx_SPI_USE_SSP0                TRUE
#endif

/**
 * @brief   SPI2 driver enable switch.
 * @details If set to @p TRUE the support for device SSP1 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(LPC11xx_SPI_USE_SSP1) || defined(__DOXYGEN__)
#define LPC11xx_SPI_USE_SSP1                TRUE
#endif

/**
 * @brief   SSP0 PCLK divider.
 */
#if !defined(LPC11xx_SPI_SSP0CLKDIV) || defined(__DOXYGEN__)
#define LPC11xx_SPI_SSP0CLKDIV              1
#endif

/**
 * @brief   SSP1 PCLK divider.
 */
#if !defined(LPC11xx_SPI_SSP1CLKDIV) || defined(__DOXYGEN__)
#define LPC11xx_SPI_SSP1CLKDIV              1
#endif

/**
 * @brief   SPI0 interrupt priority level setting.
 */
#if !defined(LPC11xx_SPI_SSP0_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define LPC11xx_SPI_SSP0_IRQ_PRIORITY       1
#endif

/**
 * @brief   SPI1 interrupt priority level setting.
 */
#if !defined(LPC11xx_SPI_SSP1_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define LPC11xx_SPI_SSP1_IRQ_PRIORITY       1
#endif

/**
 * @brief   Overflow error hook.
 * @details The default action is to stop the system.
 */
#if !defined(LPC11xx_SPI_SSP_ERROR_HOOK) || defined(__DOXYGEN__)
#define LPC11xx_SPI_SSP_ERROR_HOOK(spip)    chSysHalt()
#endif

/**
 * @brief   SCK0 signal selector.
 */
#if !defined(LPC11xx_SPI_SCK0_SELECTOR) || defined(__DOXYGEN__)
#define LPC11xx_SPI_SCK0_SELECTOR           SCK0_IS_PIO2_11
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if (LPC11xx_SPI_SSP0CLKDIV < 1) || (LPC11xx_SPI_SSP0CLKDIV > 255)
#error "invalid LPC11xx_SPI_SSP0CLKDIV setting"
#endif

#if (LPC11xx_SPI_SSP1CLKDIV < 1) || (LPC11xx_SPI_SSP1CLKDIV > 255)
#error "invalid LPC11xx_SPI_SSP1CLKDIV setting"
#endif

#if !LPC11xx_SPI_USE_SSP0 && !LPC11xx_SPI_USE_SSP1
#error "SPI driver activated but no SPI peripheral assigned"
#endif

#if (LPC11xx_SPI_SCK0_SELECTOR != SCK0_IS_PIO0_10) &&                       \
    (LPC11xx_SPI_SCK0_SELECTOR != SCK0_IS_PIO2_11) &&                       \
    (LPC11xx_SPI_SCK0_SELECTOR != SCK0_IS_PIO0_6)
#error "invalid pin assigned to SCK0 signal"
#endif

/**
 * @brief   SSP0 clock.
 */
#define  LPC11xx_SERIAL_SSP0_PCLK                                          \
  (LPC11xx_MAINCLK / LPC11xx_SERIAL_SSP0CLKDIV)

/**
 * @brief   SSP1 clock.
 */
#define  LPC11xx_SERIAL_SSP1_PCLK                                          \
  (LPC11xx_MAINCLK / LPC11xx_SERIAL_SSP1CLKDIV)

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a structure representing an SPI driver.
 */
typedef struct SPIDriver SPIDriver;

/**
 * @brief   SPI notification callback type.
 *
 * @param[in] spip      pointer to the @p SPIDriver object triggering the
 *                      callback
 */
typedef void (*spicallback_t)(SPIDriver *spip);

/**
 * @brief   Driver configuration structure.
 */
typedef struct {
  /**
   * @brief Operation complete callback or @p NULL.
   */
  spicallback_t         spc_endcb;
  /* End of the mandatory fields.*/
  /**
   * @brief The chip select line port.
   */
  ioportid_t            spc_ssport;
  /**
   * @brief The chip select line pad number.
   */
  uint16_t              spc_sspad;
  /**
   * @brief SSP CR0 initialization data.
   */
  uint16_t              spc_cr0;
  /**
   * @brief SSP CPSR initialization data.
   */
  uint32_t              spc_cpsr;
} SPIConfig;

/**
 * @brief   Structure representing a SPI driver.
 */
struct SPIDriver {
  /**
   * @brief Driver state.
   */
  spistate_t            spd_state;
  /**
   * @brief Current configuration data.
   */
  const SPIConfig       *spd_config;
#if SPI_USE_WAIT || defined(__DOXYGEN__)
  /**
   * @brief Waiting thread.
   */
  Thread                *spd_thread;
#endif /* SPI_USE_WAIT */
#if SPI_USE_MUTUAL_EXCLUSION || defined(__DOXYGEN__)
#if CH_USE_MUTEXES || defined(__DOXYGEN__)
  /**
   * @brief Mutex protecting the bus.
   */
  Mutex                 spd_mutex;
#elif CH_USE_SEMAPHORES
  Semaphore             spd_semaphore;
#endif
#endif /* SPI_USE_MUTUAL_EXCLUSION */
#if defined(SPI_DRIVER_EXT_FIELDS)
  SPI_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
  /**
   * @brief Pointer to the SSP registers block.
   */
  LPC_SSP_TypeDef       *spd_ssp;
  /**
   * @brief Number of bytes yet to be received.
   */
  uint32_t              spd_rxcnt;
  /**
   * @brief Receive pointer or @p NULL.
   */
  void                  *spd_rxptr;
  /**
   * @brief Number of bytes yet to be transmitted.
   */
  uint32_t              spd_txcnt;
  /**
   * @brief Transmit pointer or @p NULL.
   */
  const void            *spd_txptr;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if LPC11xx_SPI_USE_SSP0 && !defined(__DOXYGEN__)
extern SPIDriver SPID1;
#endif

#if LPC11xx_SPI_USE_SSP1 && !defined(__DOXYGEN__)
extern SPIDriver SPID2;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void spi_lld_init(void);
  void spi_lld_start(SPIDriver *spip);
  void spi_lld_stop(SPIDriver *spip);
  void spi_lld_select(SPIDriver *spip);
  void spi_lld_unselect(SPIDriver *spip);
  void spi_lld_ignore(SPIDriver *spip, size_t n);
  void spi_lld_exchange(SPIDriver *spip, size_t n,
                        const void *txbuf, void *rxbuf);
  void spi_lld_send(SPIDriver *spip, size_t n, const void *txbuf);
  void spi_lld_receive(SPIDriver *spip, size_t n, void *rxbuf);
  uint16_t spi_lld_polled_exchange(SPIDriver *spip, uint16_t frame);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_SPI */

#endif /* _SPI_LLD_H_ */

/** @} */
