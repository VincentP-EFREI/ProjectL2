#include "TimeTest.h"
#include <windows.h>
#include "set.h"
#include <stdio.h>

void TimeTest(int maxLevel, int valNumber){
    LARGE_INTEGER InsertStart, InsertEnd, frequencyInsert;


    t_d_list testList = createEmptyList(maxLevel);
    for(int num = valNumber; num>0; num--){
        insert(&testList, num);
    }



    QueryPerformanceFrequency(&frequencyInsert);

    QueryPerformanceCounter(&InsertStart);
    for(int maxVal = ; maxVal<=10000; maxVal+=1){
        int randVal = rand();
        saveTimedSimpleSearch(testList, randVal);
        saveTimedLevelSearch(testList, randVal);
    QueryPerformanceCounter(&InsertEnd);
    printf("search time, %f s\n", (double)(InsertEnd.QuadPart - InsertStart.QuadPart) / frequencyInsert.QuadPart);
    printf("\n");
    }
}

void saveTimedSimpleSearch(t_d_list testList, int valNumber){
    FILE *fpt;
    char *buffer = (char *)calloc(32,sizeof(char));
    sprintf(buffer, "CSV/SimpleSearch%d_%d.csv", valNumber, testList.max_level);
    fpt = fopen(buffer, "w+");

    LARGE_INTEGER start, end, frequency, startAll, endAll;
    QueryPerformanceFrequency(&frequency);
    double elapsed;

    QueryPerformanceCounter(&startAll);
    for(int testVal = valNumber; testVal<=valNumber; testVal++){
        QueryPerformanceCounter(&start);
        simpleSearch(testList, testVal);
        QueryPerformanceCounter(&end);
        elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
        fprintf(fpt,"%f\n", 1000*elapsed);
    }
    QueryPerformanceCounter(&endAll);
//    printf("Simple Search for %d, %f s\n", valNumber, (double)(endAll.QuadPart - startAll.QuadPart) / frequency.QuadPart);
    printf("%f\n", (double)(endAll.QuadPart - startAll.QuadPart) / frequency.QuadPart);

    fclose(fpt);
}

void saveTimedLevelSearch(t_d_list testList, int valNumber){
    FILE *fpt;
    char *buffer = (char *)calloc(32,sizeof(char));
    sprintf(buffer, "CSV/LevelSearch%d_%d.csv", valNumber, testList.max_level);
    fpt = fopen(buffer, "w+");

    LARGE_INTEGER start, end, frequency, startAll, endAll;
    QueryPerformanceFrequency(&frequency);
    double elapsed;

    QueryPerformanceCounter(&startAll);
    for(int testVal = valNumber; testVal<=valNumber; testVal++){
        QueryPerformanceCounter(&start);
        levelSearch(testList, testVal);
        QueryPerformanceCounter(&end);
        elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
//        fprintf(fpt,"%f\n", 1000*elapsed);
    }
    QueryPerformanceCounter(&endAll);
    printf(" Level Search for %d, %f s\n", valNumber, (double)(endAll.QuadPart - startAll.QuadPart) / frequency.QuadPart);
//    printf("%f\n", (double)(endAll.QuadPart - startAll.QuadPart) / frequency.QuadPart);

    fclose(fpt);
}