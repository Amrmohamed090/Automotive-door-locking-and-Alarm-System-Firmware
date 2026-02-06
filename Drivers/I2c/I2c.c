
#include "I2c.h"
#include "I2c_Private.h"
#include "Bit_Operations.h"

static I2C_Type* I2c_GetPeripheral(uint8 I2cId)
{
    I2C_Type* i2c = (I2C_Type*)0;

    switch (I2cId)
    {
    case I2C_1:
        i2c = I2C1;
        break;
    case I2C_2:
        i2c = I2C2;
        break;
    case I2C_3:
        i2c = I2C3;
        break;
    default:
        break;
    }

    return i2c;
}

uint8 I2c_Init(const I2c_ConfigType* Config)
{
    I2C_Type* i2c;
    uint32 ccr_value;
    uint32 trise_value;

    if (Config == (void*)0)
    {
        return I2C_NOK;
    }

    i2c = I2c_GetPeripheral(Config->I2cId);

    if (i2c == (void*)0)
    {
        return I2C_NOK;
    }

    /* Disable I2C before configuration */
    CLEAR_BIT(i2c->CR1, I2C_CR1_PE);

    /* Software reset */
    SET_BIT(i2c->CR1, I2C_CR1_SWRST);
    CLEAR_BIT(i2c->CR1, I2C_CR1_SWRST);

    /* Set peripheral clock frequency */
    i2c->CR2 &= ~(0x3F << I2C_CR2_FREQ);
    i2c->CR2 |= (I2C_APB1_FREQ_MHZ << I2C_CR2_FREQ);

    /* Configure clock control register */
    if (Config->ClockSpeed <= I2C_SPEED_STANDARD)
    {
        /* Standard mode */
        ccr_value = (I2C_APB1_FREQ_MHZ * 1000000) / (2 * Config->ClockSpeed);
        if (ccr_value < 4)
        {
            ccr_value = 4;
        }
        i2c->CCR = ccr_value & 0x0FFF;

        /* Configure rise time for standard mode (1000ns max) */
        trise_value = I2C_APB1_FREQ_MHZ + 1;
    }
    else
    {
        /* Fast mode */
        SET_BIT(i2c->CCR, I2C_CCR_FS);

        if (Config->DutyCycle == I2C_DUTY_16_9)
        {
            SET_BIT(i2c->CCR, I2C_CCR_DUTY);
            ccr_value = (I2C_APB1_FREQ_MHZ * 1000000) / (25 * Config->ClockSpeed);
        }
        else
        {
            CLEAR_BIT(i2c->CCR, I2C_CCR_DUTY);
            ccr_value = (I2C_APB1_FREQ_MHZ * 1000000) / (3 * Config->ClockSpeed);
        }

        if (ccr_value < 1)
        {
            ccr_value = 1;
        }

        i2c->CCR &= ~(0x0FFF);
        i2c->CCR |= (ccr_value & 0x0FFF);

        /* Configure rise time for fast mode (300ns max) */
        trise_value = ((I2C_APB1_FREQ_MHZ * 300) / 1000) + 1;
    }

    i2c->TRISE = trise_value & 0x3F;

    /* Configure own address */
    if (Config->AddressingMode == I2C_ADDR_10BIT)
    {
        SET_BIT(i2c->OAR1, I2C_OAR1_ADDMODE);
        i2c->OAR1 |= (Config->OwnAddress & 0x03FF);
    }
    else
    {
        CLEAR_BIT(i2c->OAR1, I2C_OAR1_ADDMODE);
        i2c->OAR1 |= ((Config->OwnAddress & 0x7F) << 1);
    }

    /* Enable I2C */
    SET_BIT(i2c->CR1, I2C_CR1_PE);

    /* Enable acknowledge */
    SET_BIT(i2c->CR1, I2C_CR1_ACK);

    return I2C_OK;
}

uint8 I2c_Start(uint8 I2cId)
{
    I2C_Type* i2c = I2c_GetPeripheral(I2cId);
    uint32 timeout = 100000;

    if (i2c == (void*)0)
    {
        return I2C_NOK;
    }

    /* Generate start condition */
    SET_BIT(i2c->CR1, I2C_CR1_START);

    /* Wait for start bit to be set */
    while (READ_BIT(i2c->SR1, I2C_SR1_SB) == 0)
    {
        if (--timeout == 0)
        {
            return I2C_TIMEOUT;
        }
    }

    return I2C_OK;
}

uint8 I2c_Stop(uint8 I2cId)
{
    I2C_Type* i2c = I2c_GetPeripheral(I2cId);

    if (i2c == (void*)0)
    {
        return I2C_NOK;
    }

    /* Generate stop condition */
    SET_BIT(i2c->CR1, I2C_CR1_STOP);

    return I2C_OK;
}

uint8 I2c_SendAddress(uint8 I2cId, uint8 Address, uint8 Direction)
{
    I2C_Type* i2c = I2c_GetPeripheral(I2cId);
    uint32 timeout = 100000;
    uint8 addr_byte;
    volatile uint32 temp;

    if (i2c == (void*)0)
    {
        return I2C_NOK;
    }

    /* Prepare address byte with direction bit */
    addr_byte = (Address << 1) | (Direction & 0x01);

    /* Send address */
    i2c->DR = addr_byte;

    /* Wait for address to be sent */
    while (READ_BIT(i2c->SR1, I2C_SR1_ADDR) == 0)
    {
        /* Check for NACK */
        if (READ_BIT(i2c->SR1, I2C_SR1_AF))
        {
            CLEAR_BIT(i2c->SR1, I2C_SR1_AF);
            I2c_Stop(I2cId);
            return I2C_NACK;
        }

        if (--timeout == 0)
        {
            return I2C_TIMEOUT;
        }
    }

    /* Clear ADDR flag by reading SR1 and SR2 */
    temp = i2c->SR1;
    temp = i2c->SR2;
    (void)temp;

    return I2C_OK;
}

uint8 I2c_WriteByte(uint8 I2cId, uint8 Data)
{
    I2C_Type* i2c = I2c_GetPeripheral(I2cId);
    uint32 timeout = 100000;

    if (i2c == (void*)0)
    {
        return I2C_NOK;
    }

    /* Wait for TXE flag */
    while (READ_BIT(i2c->SR1, I2C_SR1_TXE) == 0)
    {
        if (--timeout == 0)
        {
            return I2C_TIMEOUT;
        }
    }

    /* Write data to data register */
    i2c->DR = Data;

    /* Wait for BTF flag */
    timeout = 100000;
    while (READ_BIT(i2c->SR1, I2C_SR1_BTF) == 0)
    {
        /* Check for NACK */
        if (READ_BIT(i2c->SR1, I2C_SR1_AF))
        {
            CLEAR_BIT(i2c->SR1, I2C_SR1_AF);
            return I2C_NACK;
        }

        if (--timeout == 0)
        {
            return I2C_TIMEOUT;
        }
    }

    return I2C_OK;
}

uint8 I2c_ReadByteAck(uint8 I2cId, uint8* Data)
{
    I2C_Type* i2c = I2c_GetPeripheral(I2cId);
    uint32 timeout = 100000;

    if (i2c == (void*)0 || Data == (void*)0)
    {
        return I2C_NOK;
    }

    /* Enable ACK */
    SET_BIT(i2c->CR1, I2C_CR1_ACK);

    /* Wait for RXNE flag */
    while (READ_BIT(i2c->SR1, I2C_SR1_RXNE) == 0)
    {
        if (--timeout == 0)
        {
            return I2C_TIMEOUT;
        }
    }

    /* Read data from data register */
    *Data = (uint8)(i2c->DR & 0xFF);

    return I2C_OK;
}

uint8 I2c_ReadByteNack(uint8 I2cId, uint8* Data)
{
    I2C_Type* i2c = I2c_GetPeripheral(I2cId);
    uint32 timeout = 100000;

    if (i2c == (void*)0 || Data == (void*)0)
    {
        return I2C_NOK;
    }

    /* Disable ACK */
    CLEAR_BIT(i2c->CR1, I2C_CR1_ACK);

    /* Wait for RXNE flag */
    while (READ_BIT(i2c->SR1, I2C_SR1_RXNE) == 0)
    {
        if (--timeout == 0)
        {
            return I2C_TIMEOUT;
        }
    }

    /* Read data from data register */
    *Data = (uint8)(i2c->DR & 0xFF);

    return I2C_OK;
}

uint8 I2c_MasterTransmit(uint8 I2cId, uint8 SlaveAddr, const uint8* Data, uint16 Length)
{
    uint8 status;
    uint16 i;

    if (Data == (void*)0)
    {
        return I2C_NOK;
    }

    /* Generate start condition */
    status = I2c_Start(I2cId);
    if (status != I2C_OK)
    {
        return status;
    }

    /* Send slave address with write direction */
    status = I2c_SendAddress(I2cId, SlaveAddr, I2C_WRITE);
    if (status != I2C_OK)
    {
        return status;
    }

    /* Send data bytes */
    for (i = 0; i < Length; i++)
    {
        status = I2c_WriteByte(I2cId, Data[i]);
        if (status != I2C_OK)
        {
            I2c_Stop(I2cId);
            return status;
        }
    }

    /* Generate stop condition */
    I2c_Stop(I2cId);

    return I2C_OK;
}

uint8 I2c_MasterReceive(uint8 I2cId, uint8 SlaveAddr, uint8* Data, uint16 Length)
{
    uint8 status;
    uint16 i;

    if (Data == (void*)0 || Length == 0)
    {
        return I2C_NOK;
    }

    /* Generate start condition */
    status = I2c_Start(I2cId);
    if (status != I2C_OK)
    {
        return status;
    }

    /* Send slave address with read direction */
    status = I2c_SendAddress(I2cId, SlaveAddr, I2C_READ);
    if (status != I2C_OK)
    {
        return status;
    }

    /* Receive data bytes */
    for (i = 0; i < Length; i++)
    {
        if (i == (Length - 1))
        {
            /* Last byte - send NACK */
            status = I2c_ReadByteNack(I2cId, &Data[i]);
        }
        else
        {
            /* Send ACK for more bytes */
            status = I2c_ReadByteAck(I2cId, &Data[i]);
        }

        if (status != I2C_OK)
        {
            I2c_Stop(I2cId);
            return status;
        }
    }

    /* Generate stop condition */
    I2c_Stop(I2cId);

    return I2C_OK;
}

uint8 I2c_MemWrite(uint8 I2cId, uint8 SlaveAddr, uint8 RegAddr, const uint8* Data, uint16 Length)
{
    uint8 status;
    uint16 i;

    if (Data == (void*)0)
    {
        return I2C_NOK;
    }

    /* Generate start condition */
    status = I2c_Start(I2cId);
    if (status != I2C_OK)
    {
        return status;
    }

    /* Send slave address with write direction */
    status = I2c_SendAddress(I2cId, SlaveAddr, I2C_WRITE);
    if (status != I2C_OK)
    {
        return status;
    }

    /* Send register address */
    status = I2c_WriteByte(I2cId, RegAddr);
    if (status != I2C_OK)
    {
        I2c_Stop(I2cId);
        return status;
    }

    /* Send data bytes */
    for (i = 0; i < Length; i++)
    {
        status = I2c_WriteByte(I2cId, Data[i]);
        if (status != I2C_OK)
        {
            I2c_Stop(I2cId);
            return status;
        }
    }

    /* Generate stop condition */
    I2c_Stop(I2cId);

    return I2C_OK;
}

uint8 I2c_MemRead(uint8 I2cId, uint8 SlaveAddr, uint8 RegAddr, uint8* Data, uint16 Length)
{
    uint8 status;
    uint16 i;

    if (Data == (void*)0 || Length == 0)
    {
        return I2C_NOK;
    }

    /* Generate start condition */
    status = I2c_Start(I2cId);
    if (status != I2C_OK)
    {
        return status;
    }

    /* Send slave address with write direction */
    status = I2c_SendAddress(I2cId, SlaveAddr, I2C_WRITE);
    if (status != I2C_OK)
    {
        return status;
    }

    /* Send register address */
    status = I2c_WriteByte(I2cId, RegAddr);
    if (status != I2C_OK)
    {
        I2c_Stop(I2cId);
        return status;
    }

    /* Generate repeated start condition */
    status = I2c_Start(I2cId);
    if (status != I2C_OK)
    {
        return status;
    }

    /* Send slave address with read direction */
    status = I2c_SendAddress(I2cId, SlaveAddr, I2C_READ);
    if (status != I2C_OK)
    {
        return status;
    }

    /* Receive data bytes */
    for (i = 0; i < Length; i++)
    {
        if (i == (Length - 1))
        {
            /* Last byte - send NACK */
            status = I2c_ReadByteNack(I2cId, &Data[i]);
        }
        else
        {
            /* Send ACK for more bytes */
            status = I2c_ReadByteAck(I2cId, &Data[i]);
        }

        if (status != I2C_OK)
        {
            I2c_Stop(I2cId);
            return status;
        }
    }

    /* Generate stop condition */
    I2c_Stop(I2cId);

    return I2C_OK;
}

uint8 I2c_IsBusy(uint8 I2cId)
{
    I2C_Type* i2c = I2c_GetPeripheral(I2cId);

    if (i2c == (void*)0)
    {
        return 0;
    }

    return READ_BIT(i2c->SR2, I2C_SR2_BUSY);
}

void I2c_Disable(uint8 I2cId)
{
    I2C_Type* i2c = I2c_GetPeripheral(I2cId);

    if (i2c != (void*)0)
    {
        /* Disable I2C */
        CLEAR_BIT(i2c->CR1, I2C_CR1_PE);
    }
}
