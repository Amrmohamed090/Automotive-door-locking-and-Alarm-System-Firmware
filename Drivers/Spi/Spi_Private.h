#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

#include "Std_Types.h"

/* SPI Register Structure for STM32F2 */
typedef struct {
    uint32 CR1;     /* Control register 1 */
    uint32 CR2;     /* Control register 2 */
    uint32 SR;      /* Status register */
    uint32 DR;      /* Data register */
    uint32 CRCPR;   /* CRC polynomial register */
    uint32 RXCRCR;  /* RX CRC register */
    uint32 TXCRCR;  /* TX CRC register */
    uint32 I2SCFGR; /* I2S configuration register */
    uint32 I2SPR;   /* I2S prescaler register */
} SPI_Type;

/* SPI Base Addresses for STM32F2 */
#define SPI1_BASE  0x40013000
#define SPI2_BASE  0x40003800
#define SPI3_BASE  0x40003C00
#define SPI4_BASE  0x40013400

#define SPI1  ((SPI_Type*)SPI1_BASE)
#define SPI2  ((SPI_Type*)SPI2_BASE)
#define SPI3  ((SPI_Type*)SPI3_BASE)
#define SPI4  ((SPI_Type*)SPI4_BASE)

/* CR1 Register Bit Positions */
#define SPI_CR1_CPHA      0   /* Clock phase */
#define SPI_CR1_CPOL      1   /* Clock polarity */
#define SPI_CR1_MSTR      2   /* Master selection */
#define SPI_CR1_BR        3   /* Baud rate control (3 bits) */
#define SPI_CR1_SPE       6   /* SPI enable */
#define SPI_CR1_LSBFIRST  7   /* Frame format */
#define SPI_CR1_SSI       8   /* Internal slave select */
#define SPI_CR1_SSM       9   /* Software slave management */
#define SPI_CR1_RXONLY    10  /* Receive only */
#define SPI_CR1_DFF       11  /* Data frame format */
#define SPI_CR1_CRCNEXT   12  /* CRC transfer next */
#define SPI_CR1_CRCEN     13  /* Hardware CRC calculation enable */
#define SPI_CR1_BIDIOE    14  /* Output enable in bidirectional mode */
#define SPI_CR1_BIDIMODE  15  /* Bidirectional data mode enable */

/* CR2 Register Bit Positions */
#define SPI_CR2_RXDMAEN   0   /* Rx buffer DMA enable */
#define SPI_CR2_TXDMAEN   1   /* Tx buffer DMA enable */
#define SPI_CR2_SSOE      2   /* SS output enable */
#define SPI_CR2_FRF       4   /* Frame format (0=Motorola, 1=TI) */
#define SPI_CR2_ERRIE     5   /* Error interrupt enable */
#define SPI_CR2_RXNEIE    6   /* RX buffer not empty interrupt enable */
#define SPI_CR2_TXEIE     7   /* Tx buffer empty interrupt enable */

/* SR Register Bit Positions */
#define SPI_SR_RXNE    0   /* Receive buffer not empty */
#define SPI_SR_TXE     1   /* Transmit buffer empty */
#define SPI_SR_CHSIDE  2   /* Channel side */
#define SPI_SR_UDR     3   /* Underrun flag */
#define SPI_SR_CRCERR  4   /* CRC error flag */
#define SPI_SR_MODF    5   /* Mode fault */
#define SPI_SR_OVR     6   /* Overrun flag */
#define SPI_SR_BSY     7   /* Busy flag */
#define SPI_SR_FRE     8   /* Frame format error */

/* I2SCFGR Register Bit Positions */
#define SPI_I2SCFGR_CHLEN    0   /* Channel length */
#define SPI_I2SCFGR_DATLEN   1   /* Data length (2 bits) */
#define SPI_I2SCFGR_CKPOL    3   /* Steady state clock polarity */
#define SPI_I2SCFGR_I2SSTD   4   /* I2S standard selection (2 bits) */
#define SPI_I2SCFGR_PCMSYNC  7   /* PCM frame synchronization */
#define SPI_I2SCFGR_I2SCFG   8   /* I2S configuration mode (2 bits) */
#define SPI_I2SCFGR_I2SE     10  /* I2S enable */
#define SPI_I2SCFGR_I2SMOD   11  /* I2S mode selection */

#endif /* SPI_PRIVATE_H */
