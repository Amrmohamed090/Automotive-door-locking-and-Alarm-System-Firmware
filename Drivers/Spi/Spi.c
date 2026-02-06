#include "Spi.h"
#include "Spi_Private.h"
#include "Bit_Operations.h"

static SPI_Type* Spi_GetPeripheral(uint8 SpiId)
{
    SPI_Type* spi = (SPI_Type*)0;

    switch (SpiId)
    {
    case SPI_1:
        spi = SPI1;
        break;
    case SPI_2:
        spi = SPI2;
        break;
    case SPI_3:
        spi = SPI3;
        break;
    case SPI_4:
        spi = SPI4;
        break;
    default:
        break;
    }

    return spi;
}

uint8 Spi_Init(const Spi_ConfigType* Config)
{
    SPI_Type* spi;

    if (Config == (void*)0)
    {
        return SPI_NOK;
    }

    spi = Spi_GetPeripheral(Config->SpiId);

    if (spi == (void*)0)
    {
        return SPI_NOK;
    }

    /* Disable SPI before configuration */
    CLEAR_BIT(spi->CR1, SPI_CR1_SPE);

    /* Configure clock phase */
    if (Config->ClockPhase == SPI_CPHA_2EDGE)
    {
        SET_BIT(spi->CR1, SPI_CR1_CPHA);
    }
    else
    {
        CLEAR_BIT(spi->CR1, SPI_CR1_CPHA);
    }

    /* Configure clock polarity */
    if (Config->ClockPolarity == SPI_CPOL_HIGH)
    {
        SET_BIT(spi->CR1, SPI_CR1_CPOL);
    }
    else
    {
        CLEAR_BIT(spi->CR1, SPI_CR1_CPOL);
    }

    /* Configure master/slave mode */
    if (Config->Mode == SPI_MODE_MASTER)
    {
        SET_BIT(spi->CR1, SPI_CR1_MSTR);
    }
    else
    {
        CLEAR_BIT(spi->CR1, SPI_CR1_MSTR);
    }

    /* Configure baud rate prescaler */
    spi->CR1 &= ~(0x07 << SPI_CR1_BR);
    spi->CR1 |= ((Config->BaudRatePrescaler & 0x07) << SPI_CR1_BR);

    /* Configure data frame format */
    if (Config->DataSize == SPI_DATASIZE_16BIT)
    {
        SET_BIT(spi->CR1, SPI_CR1_DFF);
    }
    else
    {
        CLEAR_BIT(spi->CR1, SPI_CR1_DFF);
    }

    /* Configure first bit (MSB/LSB) */
    if (Config->FirstBit == SPI_FIRSTBIT_LSB)
    {
        SET_BIT(spi->CR1, SPI_CR1_LSBFIRST);
    }
    else
    {
        CLEAR_BIT(spi->CR1, SPI_CR1_LSBFIRST);
    }

    /* Configure NSS management */
    if (Config->NssMode == SPI_NSS_SOFT)
    {
        SET_BIT(spi->CR1, SPI_CR1_SSM);
        SET_BIT(spi->CR1, SPI_CR1_SSI);  /* Keep NSS high by default */
    }
    else
    {
        CLEAR_BIT(spi->CR1, SPI_CR1_SSM);
        SET_BIT(spi->CR2, SPI_CR2_SSOE);  /* Enable SS output */
    }

    /* Configure direction */
    switch (Config->Direction)
    {
    case SPI_DIRECTION_2LINES:
        CLEAR_BIT(spi->CR1, SPI_CR1_BIDIMODE);
        CLEAR_BIT(spi->CR1, SPI_CR1_RXONLY);
        break;
    case SPI_DIRECTION_2LINES_RXONLY:
        CLEAR_BIT(spi->CR1, SPI_CR1_BIDIMODE);
        SET_BIT(spi->CR1, SPI_CR1_RXONLY);
        break;
    case SPI_DIRECTION_1LINE_RX:
        SET_BIT(spi->CR1, SPI_CR1_BIDIMODE);
        CLEAR_BIT(spi->CR1, SPI_CR1_BIDIOE);
        break;
    case SPI_DIRECTION_1LINE_TX:
        SET_BIT(spi->CR1, SPI_CR1_BIDIMODE);
        SET_BIT(spi->CR1, SPI_CR1_BIDIOE);
        break;
    default:
        break;
    }

    /* Enable SPI */
    SET_BIT(spi->CR1, SPI_CR1_SPE);

    return SPI_OK;
}

uint8 Spi_TransmitByte(uint8 SpiId, uint8 Data)
{
    SPI_Type* spi = Spi_GetPeripheral(SpiId);
    uint32 timeout = 100000;
    volatile uint8 dummy;

    if (spi == (void*)0)
    {
        return SPI_NOK;
    }

    /* Wait until TXE is set */
    while (READ_BIT(spi->SR, SPI_SR_TXE) == 0)
    {
        if (--timeout == 0)
        {
            return SPI_TIMEOUT;
        }
    }

    /* Write data to data register */
    spi->DR = Data;

    /* Wait until TXE is set */
    timeout = 100000;
    while (READ_BIT(spi->SR, SPI_SR_TXE) == 0)
    {
        if (--timeout == 0)
        {
            return SPI_TIMEOUT;
        }
    }

    /* Wait until BSY is cleared */
    timeout = 100000;
    while (READ_BIT(spi->SR, SPI_SR_BSY) != 0)
    {
        if (--timeout == 0)
        {
            return SPI_TIMEOUT;
        }
    }

    /* Clear RXNE by reading DR */
    dummy = (uint8)spi->DR;
    (void)dummy;

    return SPI_OK;
}

uint8 Spi_ReceiveByte(uint8 SpiId, uint8* Data)
{
    SPI_Type* spi = Spi_GetPeripheral(SpiId);
    uint32 timeout = 100000;

    if (spi == (void*)0 || Data == (void*)0)
    {
        return SPI_NOK;
    }

    /* Send dummy byte to generate clock */
    while (READ_BIT(spi->SR, SPI_SR_TXE) == 0)
    {
        if (--timeout == 0)
        {
            return SPI_TIMEOUT;
        }
    }

    spi->DR = 0xFF;

    /* Wait until RXNE is set */
    timeout = 100000;
    while (READ_BIT(spi->SR, SPI_SR_RXNE) == 0)
    {
        if (--timeout == 0)
        {
            return SPI_TIMEOUT;
        }
    }

    /* Read data from data register */
    *Data = (uint8)(spi->DR & 0xFF);

    return SPI_OK;
}

uint8 Spi_TransmitReceiveByte(uint8 SpiId, uint8 TxData, uint8* RxData)
{
    SPI_Type* spi = Spi_GetPeripheral(SpiId);
    uint32 timeout = 100000;

    if (spi == (void*)0 || RxData == (void*)0)
    {
        return SPI_NOK;
    }

    /* Wait until TXE is set */
    while (READ_BIT(spi->SR, SPI_SR_TXE) == 0)
    {
        if (--timeout == 0)
        {
            return SPI_TIMEOUT;
        }
    }

    /* Write data to data register */
    spi->DR = TxData;

    /* Wait until RXNE is set */
    timeout = 100000;
    while (READ_BIT(spi->SR, SPI_SR_RXNE) == 0)
    {
        if (--timeout == 0)
        {
            return SPI_TIMEOUT;
        }
    }

    /* Read received data */
    *RxData = (uint8)(spi->DR & 0xFF);

    return SPI_OK;
}

uint8 Spi_TransmitBuffer(uint8 SpiId, const uint8* Buffer, uint16 Length)
{
    uint16 i;

    if (Buffer == (void*)0)
    {
        return SPI_NOK;
    }

    for (i = 0; i < Length; i++)
    {
        if (Spi_TransmitByte(SpiId, Buffer[i]) != SPI_OK)
        {
            return SPI_NOK;
        }
    }

    return SPI_OK;
}

uint8 Spi_ReceiveBuffer(uint8 SpiId, uint8* Buffer, uint16 Length)
{
    uint16 i;

    if (Buffer == (void*)0)
    {
        return SPI_NOK;
    }

    for (i = 0; i < Length; i++)
    {
        if (Spi_ReceiveByte(SpiId, &Buffer[i]) != SPI_OK)
        {
            return SPI_NOK;
        }
    }

    return SPI_OK;
}

uint8 Spi_TransmitReceiveBuffer(uint8 SpiId, const uint8* TxBuffer, uint8* RxBuffer, uint16 Length)
{
    uint16 i;

    if (TxBuffer == (void*)0 || RxBuffer == (void*)0)
    {
        return SPI_NOK;
    }

    for (i = 0; i < Length; i++)
    {
        if (Spi_TransmitReceiveByte(SpiId, TxBuffer[i], &RxBuffer[i]) != SPI_OK)
        {
            return SPI_NOK;
        }
    }

    return SPI_OK;
}

uint8 Spi_IsBusy(uint8 SpiId)
{
    SPI_Type* spi = Spi_GetPeripheral(SpiId);

    if (spi == (void*)0)
    {
        return 0;
    }

    return READ_BIT(spi->SR, SPI_SR_BSY);
}

void Spi_NssHigh(uint8 SpiId)
{
    SPI_Type* spi = Spi_GetPeripheral(SpiId);

    if (spi != (void*)0)
    {
        SET_BIT(spi->CR1, SPI_CR1_SSI);
    }
}

void Spi_NssLow(uint8 SpiId)
{
    SPI_Type* spi = Spi_GetPeripheral(SpiId);

    if (spi != (void*)0)
    {
        CLEAR_BIT(spi->CR1, SPI_CR1_SSI);
    }
}

void Spi_Disable(uint8 SpiId)
{
    SPI_Type* spi = Spi_GetPeripheral(SpiId);

    if (spi != (void*)0)
    {
        /* Wait until not busy */
        while (READ_BIT(spi->SR, SPI_SR_BSY) != 0)
        {
            /* Wait */
        }

        /* Disable SPI */
        CLEAR_BIT(spi->CR1, SPI_CR1_SPE);
    }
}
