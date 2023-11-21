#define BASE_DEBUG

#include <stdio.h>
#include <math/struct.h>

#include <memory.h>

int main()
{
    Mat4 _new;

    Float32* dataNew = (Float32*)_new.data;

    memset(dataOld, 0, 16 * sizeof(Float32));
    memset(dataNew, 0, 16 * sizeof(Float32)); 

    old[0][0] = 4;
    old[1][0] = 6;
    old[2][1] = 7;
    old[2][2] = 9;

    _new[0][0] = 4;
    _new[1][0] = 6;
    _new[2][1] = 7;
    _new[2][2] = 9;

    for(int i = 0; i < 16; i+=4)
    {
        printf("%f %f %f %f\n", dataOld[i], dataOld[i+1], dataOld[i+2], dataOld[i+3]);
    }

    printf("\n\n");

    for(int i = 0; i < 16; i+=4)
    {
        printf("%f %f %f %f\n", dataNew[i], dataNew[i+1], dataNew[i+2], dataNew[i+3]);
    }
/*
    for(int i = 0; i < 4; i++)
    {
        printf("%f %f %f %f\n", _new[i][0], _new[i][1], _new[i][2], _new[i][3]);
    }

*/    
    return 0;
}