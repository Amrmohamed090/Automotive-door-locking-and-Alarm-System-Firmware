#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

#include "Std_Types.h"

/* USART Register Structure for STM32F2 */
typedef struct {
    uint32 SR;    /* Status register */
    uint32 DR;    /* Data register */
    uint32 BRR;   /* Baud rate register */
    uint32 CR1;   /* Control register 1 */
    uint32 CR2;   /* Control register 2 */
    uint32 CR3;   /* Control register 3 */
    uint32 GTPR; /* Guard time and prescaler register */
} USART_Type;

/* USART Base Addresses for STM32F2 */
#define USART1_BASE  0x40011000
#define USART2_BASE  0x40004400
#define USART6_BASE  0x40011400

#define USART1  ((USART_Type*)USART1_BASE)
#define USART2  ((USART_Type*)USART2_BASE)
#define USART6  ((USART_Type*)USART6_BASE)

/* SR Register Bit Positions */
#define USART_SR_PE    0   /* Parity error */
#define USART_SR_FE    1   /* Framing error */
#define USART_SR_NF    2   /* Noise detected flag */
#define USART_SR_ORE   3   /* Overrun error */
#define USART_SR_IDLE  4   /* IDLE line detected */
#define USART_SR_RXNE  5   /* Read data register not empty */
#define USART_SR_TC    6   /* Transmission complete */
#define USART_SR_TXE   7   /* Transmit data register empty */
#define USART_SR_LBD   8   /* LIN break detection flag */
#define USART_SR_CTS   9   /* CTS flag */

/* CR1 Register Bit Positions */
#define USART_CR1_SBK     0   /* Send break */
#define USART_CR1_RWU     1   /* Receiver wakeup */
#define USART_CR1_RE      2   /* Receiver enable */
#define USART_CR1_TE      3   /* Transmitter enable */
#define USART_CR1_IDLEIE  4   /* IDLE interrupt enable */
#define USART_CR1_RXNEIE  5   /* RXNE interrupt enable */
#define USART_CR1_TCIE    6   /* Transmission complete interrupt enable */
#define USART_CR1_TXEIE   7   /* TXE interrupt enable */
#define USART_CR1_PEIE    8   /* PE interrupt enable */
#define USART_CR1_PS      9   /* Parity selection */
#define USART_CR1_PCE     10  /* Parity control enable */
#define USART_CR1_WAKE    11  /* Wakeup method */
#define USART_CR1_M       12  /* Word length */
#define USART_CR1_UE      13  /* USART enable */
#define USART_CR1_OVER8   15  /* Oversampling mode */

/* CR2 Register Bit Positions */
#define USART_CR2_ADD     0   /* Address of the USART node (4 bits) */
#define USART_CR2_LBDL    5   /* LIN break detection length */
#define USART_CR2_LBDIE   6   /* LIN break detection interrupt enable */
#define USART_CR2_LBCL    8   /* Last bit clock pulse */
#define USART_CR2_CPHA    9   /* Clock phase */
#define USART_CR2_CPOL    10  /* Clock polarity */
#define USART_CR2_CLKEN   11  /* Clock enable */
#define USART_CR2_STOP    12  /* STOP bits (2 bits) */
#define USART_CR2_LINEN   14  /* LIN mode enable */

/* CR3 Register Bit Positions */
#define USART_CR3_EIE     0   /* Error interrupt enable */
#define USART_CR3_IREN    1   /* IrDA mode enable */
#define USART_CR3_IRLP    2   /* IrDA low-power */
#define USART_CR3_HDSEL   3   /* Half-duplex selection */
#define USART_CR3_NACK    4   /* Smartcard NACK enable */
#define USART_CR3_SCEN    5   /* Smartcard mode enable */
#define USART_CR3_DMAR    6   /* DMA enable receiver */
#define USART_CR3_DMAT    7   /* DMA enable transmitter */
#define USART_CR3_RTSE    8   /* RTS enable */
#define USART_CR3_CTSE    9   /* CTS enable */
#define USART_CR3_CTSIE   10  /* CTS interrupt enable */
#define USART_CR3_ONEBIT  11  /* One sample bit method enable */

#endif /* UART_PRIVATE_H */
