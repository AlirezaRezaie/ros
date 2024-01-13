#include "math.h"


int pow(int num,int power){
    int output = 1;
    for (int i = 0; i < power; i++)
    {
        output *= num;
    }
    return output;
}