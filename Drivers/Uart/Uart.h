#ifndef UART_H
#define UART_H

#include "Std_Types.h"

/* UART Peripheral Selection */
#define UART_1  1
#define UART_2  2
#define UART_6  6

/* Word Length */
#define UART_WORD_8BIT  0x00
#define UART_WORD_9BIT  0x01

/* Parity Control */
#define UART_PARITY_DISABLE  0x00
#define UART_PARITY_EVEN     0x01
#define UART_PARITY_ODD      0x02

/* Stop Bits */
#define UART_STOP_1BIT   0x00
#define UART_STOP_0_5BIT 0x01
#define UART_STOP_2BIT   0x02
#define UART_STOP_1_5BIT 0x03

/* Oversampling Mode */
#define UART_OVERSAMPLING_16  0x00
#define UART_OVERSAMPLING_8   0x01

/* Status */
#define UART_OK   0x00
#define UART_NOK  0x01

/* Common Baud Rates (assuming 16MHz clock with OVER8=0) */
#define UART_BAUD_9600    0x0683
#define UART_BAUD_19200   0x0341
#define UART_BAUD_38400   0x01A1
#define UART_BAUD_57600   0x0116
#define UART_BAUD_115200  0x008B

/* UART Configuration Structure */
typedef struct {
    uint8  UartId;
    uint8  WordLength;
    uint8  Parity;
    uint8  StopBits;
    uint8  Oversampling;
    uint16 BaudRate;
} Uart_ConfigType;

/**
 * @brief Initialize UART peripheral with the given configuration
 * @param Config Pointer to configuration structure
 * @return UART_OK if successful, UART_NOK otherwise
 */
uint8 Uart_Init(const Uart_ConfigType* Config);

/**
 * @brief Transmit a single byte over UART
 * @param UartId UART peripheral to use (UART_1, UART_2, or UART_6)
 * @param Data Byte to transmit
 * @return UART_OK if successful, UART_NOK otherwise
 */
uint8 Uart_TransmitByte(uint8 UartId, uint8 Data);

/**
 * @brief Receive a single byte from UART (blocking)
 * @param UartId UART peripheral to use
 * @param Data Pointer to store received byte
 * @return UART_OK if successful, UART_NOK otherwise
 */
uint8 Uart_ReceiveByte(uint8 UartId, uint8* Data);

/**
 * @brief Transmit a string over UART
 * @param UartId UART peripheral to use
 * @param String Null-terminated string to transmit
 * @return UART_OK if successful, UART_NOK otherwise
 */
uint8 Uart_TransmitString(uint8 UartId, const uint8* String);

/**
 * @brief Transmit a buffer of bytes over UART
 * @param UartId UART peripheral to use
 * @param Buffer Pointer to data buffer
 * @param Length Number of bytes to transmit
 * @return UART_OK if successful, UART_NOK otherwise
 */
uint8 Uart_TransmitBuffer(uint8 UartId, const uint8* Buffer, uint16 Length);

/**
 * @brief Receive a buffer of bytes from UART (blocking)
 * @param UartId UART peripheral to use
 * @param Buffer Pointer to store received data
 * @param Length Number of bytes to receive
 * @return UART_OK if successful, UART_NOK otherwise
 */
uint8 Uart_ReceiveBuffer(uint8 UartId, uint8* Buffer, uint16 Length);

/**
 * @brief Check if data is available to read
 * @param UartId UART peripheral to check
 * @return 1 if data available, 0 otherwise
 */
uint8 Uart_DataAvailable(uint8 UartId);

/**
 * @brief Disable UART peripheral
 * @param UartId UART peripheral to disable
 */
void Uart_Disable(uint8 UartId);

#endif /* UART_H */
