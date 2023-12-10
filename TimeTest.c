#include "TimeTest.h"
#include <windows.h>
#include "set.h"
#include <stdio.h>

double TimeTest(int maxLevel, int valNumber, int repeat, int randmult){
    LARGE_INTEGER InsertStart, InsertEnd, frequencyInsert;

    t_d_list testList = createEmptyList(maxLevel);
    for(int num = valNumber; num>0; num--){
        insert(&testList, num);
    }

    QueryPerformanceFrequency(&frequencyInsert);
    QueryPerformanceCounter(&InsertStart);
    for(int try = 0; try<repeat; try++)
    {
        for (int maxVal = 0; maxVal <= 100000; maxVal += 1) {
            int randVal = randmult * rand();
//            saveTimedSimpleSearch(testList, randVal);
            saveTimedLevelSearch(testList, randVal);
        }
    }
    QueryPerformanceCounter(&InsertEnd);
    double val = (double)(InsertEnd.QuadPart - InsertStart.QuadPart) / frequencyInsert.QuadPart;
    return val;
}

void saveTimedSimpleSearch(t_d_list testList, int valNumber){
    simpleSearch(testList, valNumber);
}

void saveTimedLevelSearch(t_d_list testList, int valNumber){
    levelSearch(testList, valNumber);
}