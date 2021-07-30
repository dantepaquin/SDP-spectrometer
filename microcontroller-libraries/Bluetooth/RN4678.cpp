// Dante Paquin
// Spectrometer Capstone Team
// dpaquin@ucsc.edu
// UCSC ECE129
// Created 26 April 2021
// Last Updated 6 May 2021
//
// RN4678_Cpp
// This file is .cpp, though only to leverage the arduino codebase. Aside from the arduino, it is mainly C

#include "RN4678.h"

#include "CircularBuffer.h"
#include "RN4678_Command.h"

#include <stdint.h>
#include <string.h>

// Arduino IDE includes:
#include <avr/interrupt.h>
#include <avr/io.h>

#define STATUS_LEN 128
#define BAUD_RATE 115200

// This will create a circular buffer to handle transmission, and an array to handle receives
// It will have two ISRs, one that handles the transmit and one that handles receive

/*----------------------------------------------------------------------------------------------------------------------
 *  Globals and type setup
 *--------------------------------------------------------------------------------------------------------------------*/
buffer *txBuffer;   // This circular buffer takes inputs from putchar() and is where the TX ISR takes data from

volatile static rxChar;                 // Char to store the current byte in the UART1_RX register/ISR
static char moduleStatus[STATUS_LEN];   // This is a private pointer to the status string of the module

typedef enum{       // Currently only two states seem necessary, though more may be needed
    RX_IDLE = 0,
    RX_ACTIVE
} rxState;

typedef enum{
    BT_INIT = 0,
    BT_IDLE,
    BT_DATA,
    BT_PAIR
} bluetoothState;

static rxState dataState = RX_IDLE;
static bluetoothState currentState = BT_INIT;


/*----------------------------------------------------------------------------------------------------------------------
 *  PUBLIC FUNCTIONS
 *--------------------------------------------------------------------------------------------------------------------*/

int BluetoothInit(void){
    int initStatus = 0;
    // Set up UART, baud, ISRs necessary for this module
    // Set up of UART peripheral, see sec. 40.3.1 in FRM
    uint8_t uartUpper = 0x00;
    uint8_t uartLower = 0x00;
    int uartBaudDivisor = 0;

    // UART baud rate equals BUSCLK/(16*BR)
    // 115200 = F_BUS / (16*BR)
    // BR must be stored in the lower 13 bits of UARTx_BDH/UARTx_BDL
    uartBaudDivisor = F_BUS / (16 * BAUD_RATE);

    uartUpper = (uartBaudDivisor >> 8) & 0x1F;  // mask upper 5 bytes into lower 5 bytes of control register
    uartLower = uartBaudDivisor & 0xFF;

    UART1_BDH = uartUpper;
    UART1_BDL = uartLower;

    // Configure UART properties
    // TODO: Currently, the default 0x00 for both registers is all that is necessary, though this may change
    UART1_C1 = 0x00;
    UART1_C2 = 0x00;

    // Interrupt initialization:
    UCSR1B |= (1<<RXCIE1);  // Enable UART RX available interrupt
    UCSR1b |= (1<<UDRIE1);  // Enable UART TX ready interrupt

    // Run module configuration
    initStatus = BluetoothFirstBootInit();

    return initStatus;
}

int BluetoothSendCommand(char *command, char *argList) {
    // Takes in a command string pointer and places each char in the TX UART buffer
    char payload[BUFF_LEN] = {0};
    int payloadLen = 0;
    int payloadIter = 0;

    strcat(payload, command);       // Concatenate the command and the argument list into the payload
    strcat(payload, argList);       // This can be improved later, letting the function be used with unlimited arguments

    payloadLen = strlen(payload);   // Get length of payload

    if payloadLen == 0){
        return ERROR;               // If the payload is zero length, error out
    }

    for (payloadIter = 0; payloadIter < payloadLen; payloadIter++){
        // Iterate through the payload and use putchar to put every char into the TX buffer
        PutChar(payload[payloadIter]);
    }

    return SUCCESS;
}

int BluetoothSendData(char *data){
    // This function takes a pointer to a string and inserts each char iteratively into the TX circular buffer
    int dataIter = 0;
    int dataLen = strlen(data);

    for (dataIter = 0; dataIter < dataLen; dataIter++){
        PutChar(data[dataIter]);
    }

//    return SUCCESS; // need to properly define return functionality here
}

/*----------------------------------------------------------------------------------------------------------------------
 *  PRIVATE FUNCTIONS
 *--------------------------------------------------------------------------------------------------------------------*/

static void PutChar(char ch) {
    // Place individual chars in TX buffer, acts just as a wrapper so that txBuffer is less accessible
    AddToBuffer(ch, txBuffer)
}

static int BluetoothProcessMessage(char charIn, char* statusString){
    // Take input char from UART and process into strings, output through reference in statusString
    // return an enum'd value corresponding to various responses, such as AOK or %ERR#%
    // TODO: Figure out conditions to trigger End of Message
    // This could check against all potential status strings when updated

    // typical terminations: "%", newlines, "CMD>", "Trying", etc. It's a mess.

    //moduleStatus bluetoothStatus;

    strcat(statusString, charIn);

    // Run detection here:
        // if statusString matches possibleStatus
        // set bluetoothStatus = moduleStatus
        // clear statusString

    BluetoothRunStateMachine(bluetoothStatus)

    return bluetoothStatus;
}

static int BluetoothRunStateMachine(int moduleStatus){

}

static int BluetoothFirstBootInit(void){
    // See the bluetooth state machine diagram for the exact Calls here
    // TODO: Need to find a better way to parse individual returns from the module rather than rapid firing commands
    BluetoothSendCommand(BT_ENTE    R_CMD);     // Enter Command Mode, required for all further commands to be sent

    BluetoothSendCommand(BT_GET_SET_VAL,"DR");  // Get the current software version stored on the module
        // Right now, no check is in place, and the device will proceed with the rest of the configuration.
        // To implement, method of parsing response such that the following may be skipped if it had previously run

    BluetoothSendCommand(BT_SET_DEVICE_MODEL,"Spectrometer");
    BluetoothSendCommand(BT_SET_AUTH,2);

}


/*----------------------------------------------------------------------------------------------------------------------
 *  INTERRUPT SERVICE ROUTINES
 *--------------------------------------------------------------------------------------------------------------------*/

//TX ISR: If data exists in the buffer && if last TX is complete
//  clear flag, take char from TX buffer, move buffer head
// The UART data register as accessed in software actually controls both the physical TX and RX registers
// The peripheral automatically detects reads/writes to this register and directs them appropriately

ISR(USART1_UDRE_vect){
    // TX flag is controlled by the peripheral, no manual setting here
    rxChar = UART1_D;
    BluetoothProcessMessage(rxChar, moduleStatus);
}

//RX ISR: Take input char and send it into BluetoothProcessInput}
ISR(USART1_RX_vect){
    // RX flag is controlled by the peripheral, no manual setting here
    if (TestIfFull(txBuffer) != FULL){
        RemoveFromBuffer(txBuffer);
    }
}