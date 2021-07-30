// Dante Paquin
// Spectrometer Capstone Team
// dpaquin@ucsc.edu
// UCSC ECE129
// Created 26 April 2021
// Last Updated 30 April 2021
//
// RN4678_H

#ifndef MICROCONTROLLER_LIBRARIES_RN4678_H
#define MICROCONTROLLER_LIBRARIES_RN4678_H

typedef enum {
    TEST = 0,
    ERR1,
    ETC         // Need to actually find all of the possible statuses
} moduleStatus;

/*----------------------------------------------------------------------------------------------------------------------
 *  PUBLIC FUNCTIONS
 *--------------------------------------------------------------------------------------------------------------------*/
int BluetoothInit(void);

int BluetoothSendCommand(char *command);

int BluetoothSendData(char *data);

/*----------------------------------------------------------------------------------------------------------------------
 *  PRIVATE FUNCTIONS
 *--------------------------------------------------------------------------------------------------------------------*/

static void PutChar(char ch);

static int BluetoothProcessMessage(char charIn, char* statusString);

static int BluetoothRunStateMachine(int moduleStatus);

static int BluetoothFirstBootInit(void);

#endif //MICROCONTROLLER_LIBRARIES_RN4678_H
