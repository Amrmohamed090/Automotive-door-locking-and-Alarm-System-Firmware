
#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H

#include "Std_Types.h"

/* I2C Register Structure for STM32F2 */
typedef struct {
    uint32 CR1;    /* Control register 1 */
    uint32 CR2;    /* Control register 2 */
    uint32 OAR1;   /* Own address register 1 */
    uint32 OAR2;   /* Own address register 2 */
    uint32 DR;     /* Data register */
    uint32 SR1;    /* Status register 1 */
    uint32 SR2;    /* Status register 2 */
    uint32 CCR;    /* Clock control register */
    uint32 TRISE;  /* Rise time register */
    uint32 FLTR;   /* Filter register */
} I2C_Type;

/* I2C Base Addresses for STM32F2 */
#define I2C1_BASE  0x40005400
#define I2C2_BASE  0x40005800
#define I2C3_BASE  0x40005C00

#define I2C1  ((I2C_Type*)I2C1_BASE)
#define I2C2  ((I2C_Type*)I2C2_BASE)
#define I2C3  ((I2C_Type*)I2C3_BASE)

/* CR1 Register Bit Positions */
#define I2C_CR1_PE        0   /* Peripheral enable */
#define I2C_CR1_SMBUS     1   /* SMBus mode */
#define I2C_CR1_SMBTYPE   3   /* SMBus type */
#define I2C_CR1_ENARP     4   /* ARP enable */
#define I2C_CR1_ENPEC     5   /* PEC enable */
#define I2C_CR1_ENGC      6   /* General call enable */
#define I2C_CR1_NOSTRETCH 7   /* Clock stretching disable */
#define I2C_CR1_START     8   /* Start generation */
#define I2C_CR1_STOP      9   /* Stop generation */
#define I2C_CR1_ACK       10  /* Acknowledge enable */
#define I2C_CR1_POS       11  /* Acknowledge/PEC Position */
#define I2C_CR1_PEC       12  /* Packet error checking */
#define I2C_CR1_ALERT     13  /* SMBus alert */
#define I2C_CR1_SWRST     15  /* Software reset */

/* CR2 Register Bit Positions */
#define I2C_CR2_FREQ      0   /* Peripheral clock frequency (6 bits) */
#define I2C_CR2_ITERREN   8   /* Error interrupt enable */
#define I2C_CR2_ITEVTEN   9   /* Event interrupt enable */
#define I2C_CR2_ITBUFEN   10  /* Buffer interrupt enable */
#define I2C_CR2_DMAEN     11  /* DMA requests enable */
#define I2C_CR2_LAST      12  /* DMA last transfer */

/* OAR1 Register Bit Positions */
#define I2C_OAR1_ADD0     0   /* Interface address bit 0 */
#define I2C_OAR1_ADD      1   /* Interface address (7 bits for 7-bit mode) */
#define I2C_OAR1_ADDMODE  15  /* Addressing mode (0=7-bit, 1=10-bit) */

/* OAR2 Register Bit Positions */
#define I2C_OAR2_ENDUAL   0   /* Dual addressing mode enable */
#define I2C_OAR2_ADD2     1   /* Interface address 2 (7 bits) */

/* SR1 Register Bit Positions */
#define I2C_SR1_SB        0   /* Start bit (Master mode) */
#define I2C_SR1_ADDR      1   /* Address sent/matched */
#define I2C_SR1_BTF       2   /* Byte transfer finished */
#define I2C_SR1_ADD10     3   /* 10-bit header sent */
#define I2C_SR1_STOPF     4   /* Stop detection (Slave mode) */
#define I2C_SR1_RXNE      6   /* Data register not empty */
#define I2C_SR1_TXE       7   /* Data register empty */
#define I2C_SR1_BERR      8   /* Bus error */
#define I2C_SR1_ARLO      9   /* Arbitration lost */
#define I2C_SR1_AF        10  /* Acknowledge failure */
#define I2C_SR1_OVR       11  /* Overrun/underrun */
#define I2C_SR1_PECERR    12  /* PEC error in reception */
#define I2C_SR1_TIMEOUT   14  /* Timeout or Tlow error */
#define I2C_SR1_SMBALERT  15  /* SMBus alert */

/* SR2 Register Bit Positions */
#define I2C_SR2_MSL       0   /* Master/slave */
#define I2C_SR2_BUSY      1   /* Bus busy */
#define I2C_SR2_TRA       2   /* Transmitter/receiver */
#define I2C_SR2_GENCALL   4   /* General call address */
#define I2C_SR2_SMBDEFAULT 5  /* SMBus device default address */
#define I2C_SR2_SMBHOST   6   /* SMBus host header */
#define I2C_SR2_DUALF     7   /* Dual flag */
#define I2C_SR2_PEC       8   /* Packet error checking register (8 bits) */

/* CCR Register Bit Positions */
#define I2C_CCR_CCR       0   /* Clock control register (12 bits) */
#define I2C_CCR_DUTY      14  /* Fast mode duty cycle */
#define I2C_CCR_FS        15  /* I2C master mode selection */

/* APB1 Clock Frequency (assuming 16 MHz - adjust based on your clock config) */
#define I2C_APB1_FREQ_MHZ  16

#endif /* I2C_PRIVATE_H */
