
#ifndef I2C_H
#define I2C_H

#include "Std_Types.h"

/* I2C Peripheral Selection */
#define I2C_1  1
#define I2C_2  2
#define I2C_3  3

/* I2C Speed Modes */
#define I2C_SPEED_STANDARD  100000  /* 100 KHz */
#define I2C_SPEED_FAST      400000  /* 400 KHz */

/* I2C Duty Cycle (for Fast Mode) */
#define I2C_DUTY_2     0x00  /* Tlow/Thigh = 2 */
#define I2C_DUTY_16_9  0x01  /* Tlow/Thigh = 16/9 */

/* I2C Addressing Mode */
#define I2C_ADDR_7BIT   0x00
#define I2C_ADDR_10BIT  0x01

/* I2C Direction */
#define I2C_WRITE  0x00
#define I2C_READ   0x01

/* Status */
#define I2C_OK       0x00
#define I2C_NOK      0x01
#define I2C_BUSY     0x02
#define I2C_TIMEOUT  0x03
#define I2C_NACK     0x04

/* I2C Configuration Structure */
typedef struct {
    uint8  I2cId;
    uint32 ClockSpeed;
    uint8  DutyCycle;
    uint8  AddressingMode;
    uint16 OwnAddress;
} I2c_ConfigType;

/**
 * @brief Initialize I2C peripheral with the given configuration
 * @param Config Pointer to configuration structure
 * @return I2C_OK if successful, I2C_NOK otherwise
 */
uint8 I2c_Init(const I2c_ConfigType* Config);

/**
 * @brief Generate I2C start condition
 * @param I2cId I2C peripheral to use
 * @return I2C_OK if successful, I2C_NOK otherwise
 */
uint8 I2c_Start(uint8 I2cId);

/**
 * @brief Generate I2C stop condition
 * @param I2cId I2C peripheral to use
 * @return I2C_OK if successful, I2C_NOK otherwise
 */
uint8 I2c_Stop(uint8 I2cId);

/**
 * @brief Send slave address with read/write direction
 * @param I2cId I2C peripheral to use
 * @param Address 7-bit slave address
 * @param Direction I2C_WRITE or I2C_READ
 * @return I2C_OK if ACK received, I2C_NACK if NACK received
 */
uint8 I2c_SendAddress(uint8 I2cId, uint8 Address, uint8 Direction);

/**
 * @brief Write a single byte to I2C bus
 * @param I2cId I2C peripheral to use
 * @param Data Byte to write
 * @return I2C_OK if ACK received, I2C_NACK if NACK received
 */
uint8 I2c_WriteByte(uint8 I2cId, uint8 Data);

/**
 * @brief Read a single byte from I2C bus with ACK
 * @param I2cId I2C peripheral to use
 * @param Data Pointer to store received byte
 * @return I2C_OK if successful
 */
uint8 I2c_ReadByteAck(uint8 I2cId, uint8* Data);

/**
 * @brief Read a single byte from I2C bus with NACK (last byte)
 * @param I2cId I2C peripheral to use
 * @param Data Pointer to store received byte
 * @return I2C_OK if successful
 */
uint8 I2c_ReadByteNack(uint8 I2cId, uint8* Data);

/**
 * @brief Write data to a slave device
 * @param I2cId I2C peripheral to use
 * @param SlaveAddr 7-bit slave address
 * @param Data Pointer to data buffer
 * @param Length Number of bytes to write
 * @return I2C_OK if successful, error code otherwise
 */
uint8 I2c_MasterTransmit(uint8 I2cId, uint8 SlaveAddr, const uint8* Data, uint16 Length);

/**
 * @brief Read data from a slave device
 * @param I2cId I2C peripheral to use
 * @param SlaveAddr 7-bit slave address
 * @param Data Pointer to store received data
 * @param Length Number of bytes to read
 * @return I2C_OK if successful, error code otherwise
 */
uint8 I2c_MasterReceive(uint8 I2cId, uint8 SlaveAddr, uint8* Data, uint16 Length);

/**
 * @brief Write to a register of a slave device
 * @param I2cId I2C peripheral to use
 * @param SlaveAddr 7-bit slave address
 * @param RegAddr Register address
 * @param Data Pointer to data buffer
 * @param Length Number of bytes to write
 * @return I2C_OK if successful, error code otherwise
 */
uint8 I2c_MemWrite(uint8 I2cId, uint8 SlaveAddr, uint8 RegAddr, const uint8* Data, uint16 Length);

/**
 * @brief Read from a register of a slave device
 * @param I2cId I2C peripheral to use
 * @param SlaveAddr 7-bit slave address
 * @param RegAddr Register address
 * @param Data Pointer to store received data
 * @param Length Number of bytes to read
 * @return I2C_OK if successful, error code otherwise
 */
uint8 I2c_MemRead(uint8 I2cId, uint8 SlaveAddr, uint8 RegAddr, uint8* Data, uint16 Length);

/**
 * @brief Check if I2C bus is busy
 * @param I2cId I2C peripheral to check
 * @return 1 if busy, 0 if free
 */
uint8 I2c_IsBusy(uint8 I2cId);

/**
 * @brief Disable I2C peripheral
 * @param I2cId I2C peripheral to disable
 */
void I2c_Disable(uint8 I2cId);

#endif /* I2C_H */
