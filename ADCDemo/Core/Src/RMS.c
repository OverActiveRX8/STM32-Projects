//
// Created by chalkim on 6/12/19.
// Modified by PJPalanas on 11/1/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "RMS.h"

ACBuff InitBuff(int MaxSize) {
    ACBuff B;

    B = malloc(sizeof(struct ACBuffRecord));
    if(B == NULL){
        printf("Out of space!!!");
    } else {
        B->Buff = CreateQueue(MaxSize);
        B->Tmp = 0;
    }

    return B;
}

ElementType CalcRMS (ElementType X, ACBuff B) {
    Queue Q = B->Buff;

    if( IsFull(Q) ) {
        ElementType Last = FrontAndDequeue(Q);
        B->Tmp -= Last * Last;
        Enqueue(X, Q);
        B->Tmp += X * X;

        ElementType RMS =
                sqrt((double)
                (B->Tmp / B->Buff->Capacity));

        return RMS;
    } else {
        Enqueue(X, Q);
        B -> Tmp += X * X;

        return -1;
    }
}

ElementType CalcAVG (ElementType X, ACBuff B) {
    Queue Q = B->Buff;

    if( IsFull(Q) ) {
        ElementType Last = FrontAndDequeue(Q);
        B->Tmp -= Last;
			  Enqueue(X, Q);
        B->Tmp += X;
				ElementType AVG = (B->Tmp / (float)B->Buff->Capacity);
				return AVG;
    } else {
			  Enqueue(X, Q);
        B -> Tmp += X;
				return -1;
    }
}

ElementType getMax(ElementType *array, int size) {
	  ElementType tempValue = 0;
    for(int i=0; i<size; i++) {
        if(*(array+i) > tempValue)
            tempValue = *(array+i);
    }
    return tempValue;
}

ElementType getMin(ElementType *array, int size) {
	  ElementType tempValue = 0;
    for(int i=0; i<size; i++) {
        if(*(array+i) < tempValue)
            tempValue = *(array+i);
    }
    return tempValue;
}


