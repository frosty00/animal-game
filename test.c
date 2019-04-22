//
// Created by Carlo Revelli on 2019-04-18.
//

#include <stdio.h>
#include <string.h>
#include "animal.h"

int *decToBinary(int, int *);
int getOffset(int, int);

int main(int argc, char* argv[]){
    int buffer[10];
    memset(buffer, 0, 10 * sizeof(int));
    int x = getOffset(5, 10);
    printf("%i", x);
}


int *decToBinary(int n, int *buffer) {
    if (n > 1) {
        *(buffer+2) = -1;
        decToBinary(n >> 1, buffer+1);
    }
    *buffer = n & 1;
    return buffer;
}


int getOffset(int n, int size) {
    int binary[size];
    decToBinary(n, binary);
    bool began = 0;
    int offset = 0;
    int depth = 0;
    for (int i = size - 1; i > -1; i--) {
        if (binary[i] == -1) {
            began = 1;
            i--;
            continue;
        }
        if (!began) {
            continue;
        }
        depth++;
        if (binary[i]) {
            // no
            offset += (int) (MAXNUMQS / pow(2, depth));
        } else {
            offset++;
        }
    }
    return offset;
}
