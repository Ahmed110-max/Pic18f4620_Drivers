/* 
 * File:   EUSART.h
 * Author: AHMED AKRAM
 *
 * Created on June 27, 2024, 2:48 AM
 */

#ifndef EUSART_H
#define	EUSART_H
/*-------------------------------includes-------------------------- : */
#include "../GPIO/hal_gpio.h"
#include "../proc/pic18f46k20.h"
#include"../../MCAL_layer/interrupt/mcal_internal_interrupt.h"
/* ----------------- Macro Declarations -----------------*/    
/* Enable / Disable EUSART Module */
#define EUSART_MODULE_ENABLE   1
#define EUSART_MODULE_DISABLE  0 
/* Selecting EUSART Working Mode */
#define EUSART_SYNCHRONOUS_MODE  		1
#define EUSART_ASYNCHRONOUS_MODE 		0
/* Baud Rate Generator Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED  1
#define EUSART_ASYNCHRONOUS_LOW_SPEED  	0
/* Baud Rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN  		1
#define EUSART_08BIT_BAUDRATE_GEN  		0
/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_TX_DISABLE  0
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE  0
/* EUSART 9-Bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE  0


/* ----------------- Data Type Declarations -----------------*/
typedef enum{
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_lOW_SPEED,   
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}baudrate_gen_t;

#if usart_tx_INTERRUPT_MODE 
typedef enum
{
    usart_tx_interrupt_priority_low,
    usart_tx_interrupt_priority_high        
}usart_tx_interrupt_priority;
#endif

#if usart_rx_INTERRUPT_MODE 
typedef enum
{
    usart_rx_interrupt_priority_low,
    usart_rx_interrupt_priority_high        
}usart_rx_interrupt_priority;
#endif

typedef struct{
    #if usart_tx_INTERRUPT_MODE
    usart_tx_interrupt_priority usart_tx_int_priority;
    #endif
	uint8 usart_tx_enable : 1;
	uint8 usart_tx_interrupt_enable : 1;
	uint8 usart_tx_9bit_enable : 1;
    uint8 usart_tx_reserved : 5;
}usart_tx_cfg_t;

typedef struct{
    #if usart_rx_INTERRUPT_MODE
    usart_rx_interrupt_priority usart_rx_int_priority;
    #endif
	uint8 usart_rx_enable : 1;
	uint8 usart_rx_interrupt_enable : 1;
	uint8 usart_rx_9bit_enable : 1;
    uint8 usart_rx_reserved : 5;
}usart_rx_cfg_t;

typedef struct{
    uint32 baudrate;
    baudrate_gen_t baudrate_gen_gonfig;
    usart_tx_cfg_t usart_tx_cfg;
	usart_rx_cfg_t usart_rx_cfg;
	//usart_error_status_t error_status;
	void (*EUSART_TxDefaultInterruptHandler)(void);
    void (*EUSART_RxDefaultInterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverrunErrorHandler)(void);
}usart_t;

#endif	/* EUSART_H */

