#include "math.h"


int pow(int num,int power){
    int output = 1;
    for (int i = 0; i < power; i++)
    {
        output *= num;
    }
    return output;
}

int abs(int num){
    if (num < 0){
        return -num;
    }else{
        return num;
    }
}