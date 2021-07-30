// Dante Paquin
// Spectrometer Capstone Team
// dpaquin@ucsc.edu
// UCSC ECE129
// Created 26 April 2021
// Last Updated 27 April 2021
//
// CIRCULARBUFFER_H

#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#define BUFF_LEN 128
#define EMPTY 0
#define FULL 1

#define ERROR 0
#define SUCCESS 1

typedef struct{
    unsigned int size;
    unsigned int head;
    unsigned int tail;
    unsigned char data[BUFF_LEN];
} buffer;

int BufferInit(buffer *newBuffer);

int AddToBuffer(char data, buffer *buffer);

char RemoveFromBuffer(buffer *buffer);

int TestIfEmpty(buffer *buffer);

int TestIfFull(buffer *buffer);

int CountBufferItems(buffer *buffer);

#endif