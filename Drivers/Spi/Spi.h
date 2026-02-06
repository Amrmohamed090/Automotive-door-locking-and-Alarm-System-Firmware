#ifndef SPI_H
#define SPI_H

#include "Std_Types.h"

/* SPI Peripheral Selection */
#define SPI_1  1
#define SPI_2  2
#define SPI_3  3
#define SPI_4  4

/* SPI Mode (Master/Slave) */
#define SPI_MODE_SLAVE   0x00
#define SPI_MODE_MASTER  0x01

/* SPI Direction */
#define SPI_DIRECTION_2LINES         0x00  /* Full duplex */
#define SPI_DIRECTION_2LINES_RXONLY  0x01  /* Receive only */
#define SPI_DIRECTION_1LINE_RX       0x02  /* Half duplex receive */
#define SPI_DIRECTION_1LINE_TX       0x03  /* Half duplex transmit */

/* Data Frame Format */
#define SPI_DATASIZE_8BIT   0x00
#define SPI_DATASIZE_16BIT  0x01

/* Clock Polarity */
#define SPI_CPOL_LOW   0x00  /* Clock idle low */
#define SPI_CPOL_HIGH  0x01  /* Clock idle high */

/* Clock Phase */
#define SPI_CPHA_1EDGE  0x00  /* Data sampled on first clock edge */
#define SPI_CPHA_2EDGE  0x01  /* Data sampled on second clock edge */

/* Slave Select Management */
#define SPI_NSS_HARD  0x00  /* Hardware NSS management */
#define SPI_NSS_SOFT  0x01  /* Software NSS management */

/* Baud Rate Prescaler */
#define SPI_BAUDRATE_DIV2    0x00
#define SPI_BAUDRATE_DIV4    0x01
#define SPI_BAUDRATE_DIV8    0x02
#define SPI_BAUDRATE_DIV16   0x03
#define SPI_BAUDRATE_DIV32   0x04
#define SPI_BAUDRATE_DIV64   0x05
#define SPI_BAUDRATE_DIV128  0x06
#define SPI_BAUDRATE_DIV256  0x07

/* Frame Format */
#define SPI_FIRSTBIT_MSB  0x00  /* MSB transmitted first */
#define SPI_FIRSTBIT_LSB  0x01  /* LSB transmitted first */

/* Status */
#define SPI_OK       0x00
#define SPI_NOK      0x01
#define SPI_BUSY     0x02
#define SPI_TIMEOUT  0x03

/* SPI Configuration Structure */
typedef struct {
    uint8 SpiId;
    uint8 Mode;
    uint8 Direction;
    uint8 DataSize;
    uint8 ClockPolarity;
    uint8 ClockPhase;
    uint8 NssMode;
    uint8 BaudRatePrescaler;
    uint8 FirstBit;
} Spi_ConfigType;

/**
 * @brief Initialize SPI peripheral with the given configuration
 * @param Config Pointer to configuration structure
 * @return SPI_OK if successful, SPI_NOK otherwise
 */
uint8 Spi_Init(const Spi_ConfigType* Config);

/**
 * @brief Transmit a single byte over SPI
 * @param SpiId SPI peripheral to use
 * @param Data Byte to transmit
 * @return SPI_OK if successful, SPI_NOK otherwise
 */
uint8 Spi_TransmitByte(uint8 SpiId, uint8 Data);

/**
 * @brief Receive a single byte from SPI
 * @param SpiId SPI peripheral to use
 * @param Data Pointer to store received byte
 * @return SPI_OK if successful, SPI_NOK otherwise
 */
uint8 Spi_ReceiveByte(uint8 SpiId, uint8* Data);

/**
 * @brief Transmit and receive a single byte (full duplex)
 * @param SpiId SPI peripheral to use
 * @param TxData Byte to transmit
 * @param RxData Pointer to store received byte
 * @return SPI_OK if successful, SPI_NOK otherwise
 */
uint8 Spi_TransmitReceiveByte(uint8 SpiId, uint8 TxData, uint8* RxData);

/**
 * @brief Transmit a buffer of bytes over SPI
 * @param SpiId SPI peripheral to use
 * @param Buffer Pointer to data buffer
 * @param Length Number of bytes to transmit
 * @return SPI_OK if successful, SPI_NOK otherwise
 */
uint8 Spi_TransmitBuffer(uint8 SpiId, const uint8* Buffer, uint16 Length);

/**
 * @brief Receive a buffer of bytes from SPI
 * @param SpiId SPI peripheral to use
 * @param Buffer Pointer to store received data
 * @param Length Number of bytes to receive
 * @return SPI_OK if successful, SPI_NOK otherwise
 */
uint8 Spi_ReceiveBuffer(uint8 SpiId, uint8* Buffer, uint16 Length);

/**
 * @brief Transmit and receive a buffer of bytes (full duplex)
 * @param SpiId SPI peripheral to use
 * @param TxBuffer Pointer to transmit data buffer
 * @param RxBuffer Pointer to store received data
 * @param Length Number of bytes to transmit/receive
 * @return SPI_OK if successful, SPI_NOK otherwise
 */
uint8 Spi_TransmitReceiveBuffer(uint8 SpiId, const uint8* TxBuffer, uint8* RxBuffer, uint16 Length);

/**
 * @brief Check if SPI is busy
 * @param SpiId SPI peripheral to check
 * @return 1 if busy, 0 if free
 */
uint8 Spi_IsBusy(uint8 SpiId);

/**
 * @brief Set NSS pin high (software NSS mode)
 * @param SpiId SPI peripheral
 */
void Spi_NssHigh(uint8 SpiId);

/**
 * @brief Set NSS pin low (software NSS mode)
 * @param SpiId SPI peripheral
 */
void Spi_NssLow(uint8 SpiId);

/**
 * @brief Disable SPI peripheral
 * @param SpiId SPI peripheral to disable
 */
void Spi_Disable(uint8 SpiId);

#endif /* SPI_H */
