// Dante Paquin
// Spectrometer Capstone Team
// dpaquin@ucsc.edu
// UCSC ECE129
// Created 26 April 2021
// Last Updated 27 April 2021
//
// CIRCULARBUFFER_H

#include "CircularBuffer.h"

int BufferInit(buffer *newBuffer){
    int i;

    if(!newBuffer){
        return ERROR;
    }

    buffer->size = BUFF_LEN;
    buffer->head = 0;
    buffer->tail = 0;

    for(i = 0; i < BUFF_LEN; i++){
        buffer->data[i] = 0;
    }

    return SUCCESS;
}

int AddToBuffer(char data, buffer *targetBuffer){
    if(TestIfFull(targetBuffer) != FULL){

        targetBuffer->data[buffer->tail] = data;

        targetBuffer->tail = (targetBuffer->tail + 1) % targetBuffer->size;

        return SUCCESS;
    }

    else{
        return ERROR;
    }
}

char RemoveFromBuffer(buffer *targetBuffer){
    char removedChar;

    if (TestIfEmpty(targetBuffer)){
        removedChar = targetBuffer->data[targetBuffer->head];
        targetBuffer->head = (targetBuffer->head + 1) % targetBuffer->size;
    }

    return removedChar;
}

int TestIfEmpty(buffer *targetBuffer){
    if(targetBuffer->tail == targetBuffer->head){
        return EMPTY;
    }
    else{
        return !EMPTY;
    }
}

int TestIfFull(buffer *targetBuffer){
    if(targetBuffer->tail == targetBuffer->head - 1){
        return FULL;
    }
    else{
        return !FULL;
    }
}

int CountBufferItems(buffer *targetBuffer){
    if (targetBuffer->tail < targetBuffer->head){
        return BUFF_LEN - targetBuffer->head + targetBuffer->tail;
    }
    else {
        return targetBuffer->tail - targetBuffer->head;
    }
}