#ifndef _BOARDARCH_H
#define _BOARDARCH_H

#include <Arduino.h>
#include "../DataModules/ModBackend/ModBackend.h"
/*******
 *
 * Pinout of the Microcontroller ATMETGA644
 *
 */

/***
 * Module MUX BID ( 74HC4067 && 74HC595 )
 */

#define NUM_595_MODLLAMADAS 6
#define NUM_4067_MODLLAMADAS 3

/* Module 74HC4067 */
#if defined(__AVR_ATmega644A__)

    #define MUX_PIN_S0 PIN_PB0
    #define MUX_PIN_S1 PIN_PB1
    #define MUX_PIN_S2 PIN_PB2
    #define MUX_PIN_S3 PIN_PB3
    /* Module 74HC595 */
    #define MUX_DATAPIN_595 PIN_PD5
    #define MUX_CLKPIN_595 PIN_PD6
    #define MUX_LATCHPIN_595 PIN_PD7

    /* MUX 1 BID (LLAMADAS)(74HC4067) */
    #define MUX_PIN_ENA1 PIN_PB4
    #define MUX_PIN_OUT1 PIN_PA0

    /* MUX 2 BID  (LLAMADAS)(74HC4067) */
    #define MUX_PIN_ENA2 PIN_PB5
    #define MUX_PIN_OUT2 PIN_PA1

    /* MUX 3 BID (LLAMADAS)(74HC4067) */
    #define MUX_PIN_ENA3 PIN_PB6
    #define MUX_PIN_OUT3 PIN_PA2

    /***
     * Module MUX INP ( 74HC4067 )
     */
    #define NUM_4067_MODINP 1

    /* MUX INP 1  (SEGURIDADES, BANDERAS Y ALERTAS)(74HC4067) */
    #define MUX_PIN_ENA4 PIN_PB7
    #define MUX_PIN_OUT4 PIN_PA3

    /***
     * Module RELES (74HC595 )
     */
    #define NUM_595_MODRELES 2
    /* Module 74HC595 */
    #define MUX_DATAPIN_RELE PIN_PD2
    #define MUX_CLKPIN_RELE PIN_PD3
    #define MUX_LATCHPIN_RELE PIN_PD4

    /**
     * Module Software Serial
     */

    /*  */

    /* Module DEBUG */
    #define ALLOW_DEBUG

    #define DEBUG_RX PIN_PA6
    #define DEBUG_TX PIN_PA7

    /* Module GSM */
    #define GSM_RX PIN_PA4
    #define GSM_TX PIN_PA5

    /* Module PROGRAM FIRMWARE */
    #define PROGRAM_RX PIN_PD0
    #define PROGRAM_TX PIN_PD1

    /* Module BLE */
    #define BLE_RX PIN_PC2
    #define BLE_TX PIN_PC3

    /**
     * Module I2C
     */

    /* Module OLED */
    /* Module AT24C1024 */
    #define SCL_PIN PIN_PC0
    #define SDA_PIN PIN_PC1

#elif defined(__AVR_ATmega2560__)

    #define MUX_PIN_S0 22
    #define MUX_PIN_S1 23
    #define MUX_PIN_S2 24
    #define MUX_PIN_S3 25
    
    /***
     * Module MUX INP ( 74HC4067 )
     */
    #define NUM_4067_MODINP 1
    
    /* MUX INP 1  (SEGURIDADES, BANDERAS Y ALERTAS)(74HC4067) */
    #define MUX_PIN_ENA 26
    #define MUX_PIN_OUT 27
    
    /***
     * Module RELES (74HC595 )
     */
    #define NUM_595_MOD 3
    /* Module 74HC595 */
    #define MUX_DATAPIN 39
    #define MUX_CLKPIN 38
    #define MUX_LATCHPIN 37
    
    /**
     * Module Software Serial
     */
    
    /*  */
    
    /* Module DEBUG */
    #define ALLOW_DEBUG
    
    #define DEBUG_RX 11
    #define DEBUG_TX 10
    
    /* Module GSM */
    #define GSM_RX 13
    #define GSM_TX 12
    
    /* Module PROGRAM FIRMWARE */
    #define PROGRAM_RX 0
    #define PROGRAM_TX 1
    
    /* Module BLE */
    #define BLE_RX A8
    #define BLE_TX A9
    
    /**
     * Module I2C
     */
    
    /* Module OLED */
    /* Module AT24C1024 */
    #define SCL_PIN 21
    #define SDA_PIN 20
    
#elif defined( ARDUINO_BLUEPILL_F103C8 )
    #define MUX_PIN_S0 PB12
    #define MUX_PIN_S1 PB13
    #define MUX_PIN_S2 PB14
    #define MUX_PIN_S3 PB15
    /* Module 74HC595 */
    #define MUX_DATAPIN_595 PC13
    #define MUX_CLKPIN_595 PC14
    #define MUX_LATCHPIN_595 PC15
    
    /* MUX 1 BID (LLAMADAS)(74HC4067) */
    #define MUX_PIN_ENA1 PA11
    #define MUX_PIN_OUT1 PA6
    
    /* MUX 2 BID  (LLAMADAS)(74HC4067) */
    #define MUX_PIN_ENA2 PA12
    #define MUX_PIN_OUT2 PA7
    
    /* MUX 3 BID (LLAMADAS)(74HC4067) */
    #define MUX_PIN_ENA3 PA15
    #define MUX_PIN_OUT3 PB0
    
    /***
     * Module MUX INP ( 74HC4067 )
     */
    #define NUM_4067_MODINP 1
    
    /* MUX INP 1  (SEGURIDADES, BANDERAS Y ALERTAS)(74HC4067) */
    #define MUX_PIN_ENA4 PB3
    #define MUX_PIN_OUT4 PB1
    
    /***
     * Module RELES (74HC595 )
     */
    #define NUM_595_MODRELES 2
    /* Module 74HC595 */
    #define MUX_DATAPIN_RELE PB4
    #define MUX_CLKPIN_RELE PB5
    #define MUX_LATCHPIN_RELE PA0
    
    /**
     * Module Software Serial
     */
    
    /*  */
    #define ALLOW_DEBUG
    /* Module DEBUG 
    
    
    #define DEBUG_RX PB11
    #define DEBUG_TX PB10*/
    
    /* Module GSM 
    #define GSM_RX 13
    #define GSM_TX 12*/
    
    /* Module PROGRAM FIRMWARE 
    #define PROGRAM_RX 0
    #define PROGRAM_TX 1*/
    
    /* Module BLE 
    #define BLE_RX A8
    #define BLE_TX A9*/
    
    /**
     * Module I2C
     */
    
    /* Module OLED */
    /* Module AT24C1024 */
    #define SCL_PIN 21
    #define SDA_PIN 20

#elif defined( ESP8266 )

    #define MUX_PINA 15
    #define MUX_PINB 13
    #define MUX_PINC 12
    #define MUX_PIND 14
    #define MUX_PINE 16
    #define MUX_PINX 16

    #define MUX_PIN_S0 PB12
    #define MUX_PIN_S1 PB13
    #define MUX_PIN_S2 PB14
    #define MUX_PIN_S3 PB15
    /* Module 74HC595 */
    #define MUX_DATAPIN_595 PC13
    #define MUX_CLKPIN_595 PC14
    #define MUX_LATCHPIN_595 PC15
    
    /* MUX 1 BID (LLAMADAS)(74HC4067) */
    #define MUX_PIN_ENA1 PA11
    #define MUX_PIN_OUT1 PA6

#endif

/*******
 *
 * Pinout of the Microcontroller ATMETGA644
 *
 */

/***
 * Module LLAMADAS Y LECTURAS
 * 1) Las Lecturas y llamdas pueden ser cofingurables en cualquier modulo MUX (BID o INP)
 * 2) Se debe identificar el tipo de modulo de cada MUX, qu puede variar de acuerdo al tipo de entrada
 */

#define NUM_DEVICES 2
enum tipeDevices
{
    MUXBID_MOD,
    MUXINP_MOD,
    RELE595_MOD
};

#define TOTAL_POSITION_BOARD 80
enum positionDevices
{
    MUX_MOD_LLAMADAS_POS = 0,
    MUX_MOD_INP_POS = 48,
    RELE595_MOD_POS = 64
};

#endif

void Board_InitModules();

void Board_setMultipleOutputDevice( struct data_PinBackend *confg, uint8_t elements);
void Board_setOneOutputDevice(  struct data_PinBackend *confg );

void Board_getOneInputDevice(struct data_PinBackend *confg);
void Board_getMultipleInputDevice(struct data_PinBackend *confg, uint8_t elements);

void Board_ConfigModules();

void Board_getInputSetOutputDevice(struct data_PinBackend *confg, uint8_t elements);