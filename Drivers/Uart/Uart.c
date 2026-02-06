#include "Uart.h"
#include "Uart_Private.h"
#include "Bit_Operations.h"

static USART_Type* Uart_GetPeripheral(uint8 UartId)
{
    USART_Type* usart = (USART_Type*)0;

    switch (UartId)
    {
    case UART_1:
        usart = USART1;
        break;
    case UART_2:
        usart = USART2;
        break;
    case UART_6:
        usart = USART6;
        break;
    default:
        break;
    }

    return usart;
}

uint8 Uart_Init(const Uart_ConfigType* Config)
{
    USART_Type* usart;

    if (Config == (void*)0)
    {
        return UART_NOK;
    }

    usart = Uart_GetPeripheral(Config->UartId);

    if (usart == (void*)0)
    {
        return UART_NOK;
    }

    /* Disable USART before configuration */
    CLEAR_BIT(usart->CR1, USART_CR1_UE);

    /* Configure word length */
    if (Config->WordLength == UART_WORD_9BIT)
    {
        SET_BIT(usart->CR1, USART_CR1_M);
    }
    else
    {
        CLEAR_BIT(usart->CR1, USART_CR1_M);
    }

    /* Configure parity */
    switch (Config->Parity)
    {
    case UART_PARITY_EVEN:
        SET_BIT(usart->CR1, USART_CR1_PCE);
        CLEAR_BIT(usart->CR1, USART_CR1_PS);
        break;
    case UART_PARITY_ODD:
        SET_BIT(usart->CR1, USART_CR1_PCE);
        SET_BIT(usart->CR1, USART_CR1_PS);
        break;
    case UART_PARITY_DISABLE:
    default:
        CLEAR_BIT(usart->CR1, USART_CR1_PCE);
        break;
    }

    /* Configure stop bits */
    usart->CR2 &= ~(0x03 << USART_CR2_STOP);
    usart->CR2 |= (Config->StopBits << USART_CR2_STOP);

    /* Configure oversampling */
    if (Config->Oversampling == UART_OVERSAMPLING_8)
    {
        SET_BIT(usart->CR1, USART_CR1_OVER8);
    }
    else
    {
        CLEAR_BIT(usart->CR1, USART_CR1_OVER8);
    }

    /* Set baud rate */
    usart->BRR = Config->BaudRate;

    /* Enable transmitter and receiver */
    SET_BIT(usart->CR1, USART_CR1_TE);
    SET_BIT(usart->CR1, USART_CR1_RE);

    /* Enable USART */
    SET_BIT(usart->CR1, USART_CR1_UE);

    return UART_OK;
}

uint8 Uart_TransmitByte(uint8 UartId, uint8 Data)
{
    USART_Type* usart = Uart_GetPeripheral(UartId);

    if (usart == (void*)0)
    {
        return UART_NOK;
    }

    /* Wait until transmit data register is empty */
    while (READ_BIT(usart->SR, USART_SR_TXE) == 0)
    {
        /* Wait */
    }

    /* Write data to data register */
    usart->DR = Data;

    /* Wait until transmission is complete */
    while (READ_BIT(usart->SR, USART_SR_TC) == 0)
    {
        /* Wait */
    }

    return UART_OK;
}

uint8 Uart_ReceiveByte(uint8 UartId, uint8* Data)
{
    USART_Type* usart = Uart_GetPeripheral(UartId);

    if (usart == (void*)0 || Data == (void*)0)
    {
        return UART_NOK;
    }

    /* Wait until data is received */
    while (READ_BIT(usart->SR, USART_SR_RXNE) == 0)
    {
        /* Wait */
    }

    /* Read data from data register */
    *Data = (uint8)(usart->DR & 0xFF);

    return UART_OK;
}

uint8 Uart_TransmitString(uint8 UartId, const uint8* String)
{
    if (String == (void*)0)
    {
        return UART_NOK;
    }

    while (*String != '\0')
    {
        if (Uart_TransmitByte(UartId, *String) != UART_OK)
        {
            return UART_NOK;
        }
        String++;
    }

    return UART_OK;
}

uint8 Uart_TransmitBuffer(uint8 UartId, const uint8* Buffer, uint16 Length)
{
    uint16 i;

    if (Buffer == (void*)0)
    {
        return UART_NOK;
    }

    for (i = 0; i < Length; i++)
    {
        if (Uart_TransmitByte(UartId, Buffer[i]) != UART_OK)
        {
            return UART_NOK;
        }
    }

    return UART_OK;
}

uint8 Uart_ReceiveBuffer(uint8 UartId, uint8* Buffer, uint16 Length)
{
    uint16 i;

    if (Buffer == (void*)0)
    {
        return UART_NOK;
    }

    for (i = 0; i < Length; i++)
    {
        if (Uart_ReceiveByte(UartId, &Buffer[i]) != UART_OK)
        {
            return UART_NOK;
        }
    }

    return UART_OK;
}

uint8 Uart_DataAvailable(uint8 UartId)
{
    USART_Type* usart = Uart_GetPeripheral(UartId);

    if (usart == (void*)0)
    {
        return 0;
    }

    return READ_BIT(usart->SR, USART_SR_RXNE);
}

void Uart_Disable(uint8 UartId)
{
    USART_Type* usart = Uart_GetPeripheral(UartId);

    if (usart != (void*)0)
    {
        /* Disable transmitter and receiver */
        CLEAR_BIT(usart->CR1, USART_CR1_TE);
        CLEAR_BIT(usart->CR1, USART_CR1_RE);

        /* Disable USART */
        CLEAR_BIT(usart->CR1, USART_CR1_UE);
    }
}
