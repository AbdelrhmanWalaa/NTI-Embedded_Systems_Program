/*
 * UART_Config.h
 *
 *     Created on: Aug 5, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Universal Asynchronous Receiver Transmitter (UART) pre-build configurations, through which user can configure before using the UART peripheral.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* UART Configurations' Definitions */

/* UART Modes */
#define UART_U8_ASYNC_MODE                    0
#define UART_U8_SYNC_MODE                     1

/* UART Transmission Speeds */
#define UART_U8_NORMAL_SPEED                  0
#define UART_U8_DOUBLE_SPEED                  1

/* UART Multi-processor Communication Mode */
#define UART_U8_MPCM_DISABLED                 0
#define UART_U8_MPCM_ENABLED                  1

/* UART Receiver RX */
#define UART_U8_RX_DISABLED                   0
#define UART_U8_RX_ENABLED                    1

/* UART Transmitter TX */
#define UART_U8_TX_DISABLED                   0
#define UART_U8_TX_ENABLED                    1

/* UART RX Complete Interrupt */
#define UART_U8_RX_INT_DISABLED               0
#define UART_U8_RX_INT_ENABLED                1

/* TX Complete Interrupt */
#define UART_U8_TX_INT_DISABLED               0
#define UART_U8_TX_INT_ENABLED                1

/* UART Data Register Empty Interrupt */
#define UART_U8_UDRE_INT_DISABLED			  0
#define UART_U8_UDRE_INT_ENABLED			  1

/* UART Parity Modes */
#define UART_U8_PARITY_MODE_DISABLED          0
#define UART_U8_EVEN_PARITY_MODE              1
#define UART_U8_ODD_PARITY_MODE               2

/* UART Stop Bit(s) */
#define UART_U8_ONE_STOP_BIT                  0
#define UART_U8_TWO_STOP_BIT                  1

/* UART Data Bits */
#define UART_U8_5_BITS_DATA                   0
#define UART_U8_6_BITS_DATA                   1
#define UART_U8_7_BITS_DATA                   2
#define UART_U8_8_BITS_DATA                   3
#define UART_U8_9_BITS_DATA                   4

/* UART Baud Rates ( Symbol Per Second -> Bit Per Second ( bps ) ) */
#define UART_U8_BAUD_RATE_2400                0
#define UART_U8_BAUD_RATE_4800                1
#define UART_U8_BAUD_RATE_9600                2
#define UART_U8_BAUD_RATE_14400               3
#define UART_U8_BAUD_RATE_19200               4
#define UART_U8_BAUD_RATE_28800               5
#define UART_U8_BAUD_RATE_38400               6
#define UART_U8_BAUD_RATE_57600               7

/* End of Configurations' Definitions */

/*******************************************************************************************************************************************************************/
/* UART Configurations */

/* UART Mode Select */
/* Options: UART_U8_ASYNC_MODE
 *          UART_U8_SYNC_MODE
 */
#define UART_U8_MODE_SELECT			          UART_U8_ASYNC_MODE

/* UART Transmission Speed Select */
/* Options: UART_U8_NORMAL_SPEED
 *          UART_U8_DOUBLE_SPEED
 */
#define UART_U8_SPEED_SELECT			      UART_U8_NORMAL_SPEED

/* UART Multi-processor Communication Mode Enable */
/* Options: UART_U8_MPCM_DISABLED
 *          UART_U8_MPCM_ENABLED
 */
#define UART_U8_MPCM_ENABLE			          UART_U8_MPCM_DISABLED

/* UART Receiver Enable */
/* Options: UART_U8_RX_DISABLED
 *          UART_U8_RX_ENABLED
 */
#define UART_U8_RX_ENABLE   		          UART_U8_RX_DISABLED

/* UART Transmitter Enable */
/* Options: UART_U8_TX_DISABLED
 *          UART_U8_TX_ENABLED
 */
#define UART_U8_TX_ENABLE   		          UART_U8_TX_ENABLED

/* UART RX Complete Interrupt Enable */
/* Options: UART_U8_RX_INT_DISABLED
 *          UART_U8_RX_INT_ENABLED
 */
#define UART_U8_RX_INT_ENABLE		          UART_U8_RX_INT_DISABLED

/* UART TX Complete Interrupt Enable */
/* Options: UART_U8_TX_INT_DISABLED
 *          UART_U8_TX_INT_ENABLED
 */
#define UART_U8_TX_INT_ENABLE		          UART_U8_TX_INT_DISABLED

/* UART Data Register Empty Interrupt Enable */
/* Options: UART_U8_UDRE_INT_DISABLED
 *          UART_U8_UDRE_INT_ENABLED
 */
#define UART_U8_DATA_REG_EMPTY_INT_ENABLE     UART_U8_UDRE_INT_DISABLED

/* UART Parity Bit Mode Select */
/* Options: UART_U8_PARITY_MODE_DISABLED
 *          UART_U8_EVEN_PARITY_MODE
 *          UART_U8_ODD_PARITY_MODE
 */
#define UART_U8_PARITY_MODE_SELECT            UART_U8_PARITY_MODE_DISABLED

/* UART Stop Bit(s) Select */
/* Options: UART_U8_ONE_STOP_BIT
 *          UART_U8_TWO_STOP_BIT
 */
#define UART_U8_STOP_BIT_SELECT		          UART_U8_ONE_STOP_BIT

/* UART Data Bits Select */
/* Options: UART_U8_5_BITS_DATA
 *          UART_U8_6_BITS_DATA
 *          UART_U8_7_BITS_DATA
 *          UART_U8_8_BITS_DATA
 *          UART_U8_9_BITS_DATA
 */
#define UART_U8_DATA_BITS_SELECT		      UART_U8_8_BITS_DATA

/* UART Baud Rate Select */
/* Options: UART_U8_BAUD_RATE_2400
 *          UART_U8_BAUD_RATE_4800
 *          UART_U8_BAUD_RATE_9600
 *          UART_U8_BAUD_RATE_14400
 *          UART_U8_BAUD_RATE_19200
 *          UART_U8_BAUD_RATE_28800
 *          UART_U8_BAUD_RATE_38400
 *          UART_U8_BAUD_RATE_57600
 */
#define UART_U8_BAUD_RATE_SELECT              UART_U8_BAUD_RATE_9600

/* TimeOutCounter Max Value */
#define UART_U16_TIME_OUT_MAX_VALUE		      50000

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* UART_CONFIG_H_ */