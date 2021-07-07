/*--------------------------------------------------------------------------
 * Filename:        test_fsw.c
 * Author:          
 * Creation Date:   June 13, 2021
 * Version:
 *
 * Description:     Sample Test software used for AMP purposes.
 *
 * Revisions:
 *
 *
 * Copyright (C) 2021, by the California Institute of Technology. ALL RIGHTS
 * RESERVED. United States Government Sponsorship acknowledged. Any commercial
 * use must be negotiated with the Office of Technology Transfer at the
 * California Institute of Technology.
 *
 * This software may be subject to U.S. export control laws. By accepting this
 * software, the user agrees to comply with all applicable U.S. export laws and
 * regulations. User has the responsibility to obtain export licenses, or other
 * export authority as may be required before exporting such information to
 * foreign countries or providing access to foreign persons.
 *--------------------------------------------------------------------------*/


#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <stdarg.h> 
#include <bcc/bcc.h>
#include "test_fsw.h"
#include "leon3-uart.h"

#define PRINTF 1

void uartTxByte(uint32_t dataByte)
{
    leon3_uart_status_t uart_status;

    do{
        uart_status.word = *UART0_STATUS;
    } while (uart_status.reg.xmit_fifo_full);

    *UART0_DATA = dataByte;
}

void uartTxNts(char *cp)
{
    while (*cp) uartTxByte(*(cp++));
}

void uartTxHex(uint32_t val, uint32_t s)
{
    uint32_t n;

    for (n = 0; n < 8; n++, val <<= 4)
    {
        uint8_t c = '0' + ((val >> 28) & 0xf);
        if (c > '9') { c += ('a' - '9' - 1); }
    if ((uint32_t)n >= s) { uartTxByte(c); }
    }
}

void uart_printf(char* string, ...)
{
    #if(PRINTF)
        char *cursor = "\0";
        uint32_t integer_arg = 0;
        char * char_arg;
        va_list args;

        va_start(args, string);

        for(cursor = string; *cursor != '\0'; cursor++)
        {
            while(*cursor != '%' && *cursor != '\0')
            {
                uartTxByte(*cursor);
                cursor++;
            }

            if(*cursor == '\0')
            {
                break;
            }

            cursor++;

            switch(*cursor)
            {
                case 'd':
                    integer_arg = va_arg(args, int);
                    uartTxHex(integer_arg, 7);
                    break;

                case 'x':
                    integer_arg = va_arg(args, unsigned int);
                    uartTxHex(integer_arg, 0);
                    break;
                case 's':
                    char_arg = va_arg(args, char*);
                    uartTxNts(char_arg);
                    break;
            }
        }

        va_end(args);
    #endif
}

struct apbuart_regs {
        uint32_t data;      /* 0x0000 */
        uint32_t status;    /* 0x0004 */
        uint32_t ctrl;      /* 0x0008 */
        uint32_t scaler;    /* 0x000c */
        uint32_t debug;     /* 0x0010 */
};

/*
 *Override default console hardware
 */
extern uint32_t __bcc_con_handle;

/*
 * Override the default probing/initialization of
 * console
 */
extern int __bcc_con_init(void);

/*
 * Write a character on the console
 *
 * The function shall return 0 on success.
 */
extern int __bcc_con_outbyte(char c);

/*
 * Read the next character from console
 *
 * The returns the read character.
 */
extern char __bcc_con_inbyte(void);

/*
 * Parameters for activating GR712RC UART0. Assumes system clock frequency of
 * 50 MHz and target baud 38400.
 */
static void *UART0BASE = (void *) 0x80000100;

static volatile char user_input;

void* uart_interrupt_handler(void)
{
    user_input = __bcc_con_inbyte();
    return (void*)NULL;
}

/*
 * Redirect BCC console I/O to a specific APBUART.
 *
 * The paramters freq and baud are used to calculate UART scaler register
 * value.
 *
 * base: Base address of APBUART (for example 0x80100100 for GR712RC UART1)
 * freq: System frequency
 * baud: Target UART baud
 */
void uart_init(void *base, int freq, int baud)
{
    #if(PRINTF)
        volatile struct apbuart_regs *regs;

        regs = base;

        /*
         * Enable UART receiver and transmitter, and receiver interrupts.
         */
        regs->ctrl = APBUART_CTRL_RI | APBUART_CTRL_TE | APBUART_CTRL_RE;
        regs->scaler = freq/(baud * 8) - 1;
        regs->status = 0;

        bcc_int_unmask(UART0_IRQ_NUM);

        bcc_isr_register(UART0_IRQ_NUM, (void*) uart_interrupt_handler, NULL);

        /* Install the new UART. */
        __bcc_con_handle = (uint32_t) base;

        /* Set the global variable __bcc_con_handle */
        __bcc_con_init();
    #endif
}



int main(void)
{

    uart_init(UART0BASE, FREQ_40MHz, BAUD_115200);

    uart_printf("\r\n\r\n=======================================================\r\n\r\n");
    uart_printf("Welcome to Test Flight Software!\r\n\r\n");
    uart_printf("Compiled on %s at %s GMT\r\n\r\n", __DATE__, __TIME__);

    uart_printf("\r\nDARPA AMP\r\n");

    

    return 0;
}




