//
// Created by chalkim on 6/12/19.
// Modified by PJPalanas on 11/1/19.
//

#ifndef _RMS_H_
#define _RMS_H_

#include "Queues.h"

struct ACBuffRecord {
    Queue Buff;
    ElementType Tmp;
};

typedef struct ACBuffRecord *ACBuff;

ACBuff InitBuff(int MaxSize);
ElementType CalcRMS (ElementType X, ACBuff B);
ElementType CalcAVG (ElementType X, ACBuff B);
ElementType CalcVmax (ElementType X, ACBuff B);
ElementType CalcVmin (ElementType X, ACBuff B);

//Assisting Functions
ElementType getMax(ElementType *array, int size);
ElementType getMin(ElementType *array, int size);

#endif //_RMS_H_
