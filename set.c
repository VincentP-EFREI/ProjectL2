#include "set.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

t_d_cell* createEmptyCell(int value, int nLevels){
    t_d_cell* cell = (t_d_cell*)malloc(sizeof(t_d_cell));
    cell->value = value;
    cell->nexts = (t_d_cell**) calloc(nLevels, sizeof(t_d_cell*));
    return cell;
}

t_d_list createEmptyList(int max_level){
    t_d_list list;
    list.nElement = 0;
    list.max_level = max_level;
    list.heads = (t_d_cell**)calloc(max_level, sizeof(t_d_cell*));
    return list;
}

void setPointer(t_d_cell *pCell, t_d_list *pList, int i) {
    if(i == 0) return;
    t_d_cell *destinationPtr;
    for(int h = 1; h <= pList->max_level; h++){
        destinationPtr = pCell;
        int nTravel = (int)pow(2,h);
        if(i % nTravel == 0){
            for(int g = 0; g < nTravel; g++){
                if(destinationPtr == NULL) break;
                destinationPtr = destinationPtr->nexts[0];
            }
            pCell->nexts[h] = destinationPtr;
            pList->heads[h] = pCell;
        }else return;
    }
}

//Insert a cell with levels at the beginning (head) of the list (be careful to take into account the number of levels in the cell)
void insertHead(t_d_list *list, t_d_cell *cell){
    cell->nexts[0] = list->heads[0];
    list->heads[0] = cell;

    setPointer(cell, list, list->nElement-1);

}



void insert(t_d_list *list, int value){
    list->nElement++;
    t_d_cell* ptr = createEmptyCell(value, list->max_level);
    if(list->heads[0] == NULL){
        insertHead(list, ptr);
        return;
    }
    if(value < list->heads[0]->value){
        insertHead(list, ptr);
        return;
    }

    t_d_cell* ptrNext = list->heads[0];
    t_d_cell* ptrBefore = ptrNext;
    while(value > ptrNext->value && ptrNext->nexts[0] != NULL){
        ptrBefore = ptrNext;
        ptrNext = ptrNext->nexts[0];
    }
    if(value > ptrNext->value){
        ptr->nexts[0] = NULL;
        ptrNext->nexts[0] = ptr;
        return;
    }
    ptr->nexts[0] = ptrBefore->nexts[0];
    ptrBefore->nexts[0] = ptr;
}

int simpleSearch(t_d_list list, int val){
    t_d_cell* currentPtr = list.heads[0];
    int n = 0;
    while(n<list.nElement){
        if(currentPtr == NULL) break;
        if(currentPtr->value == val) return n;
        if(currentPtr->value > val) return -1;
        currentPtr = currentPtr->nexts[0];
        n++;
    }
    return -1;
}

int levelSearch(t_d_list list, int val){
    if(list.heads[0] == NULL) return -1;
    if(val<list.heads[0]->value) return -1;

    int searchLvl = list.max_level-1;
    t_d_cell *searchCursor = list.heads[searchLvl];
    t_d_cell *precedentCursor = NULL;
    for(int i = searchLvl; i>=0; i--){
        if(val<searchCursor->value){
            searchCursor = list.heads[--searchLvl];
        }
    }
    while(val>searchCursor->value){
        if(searchCursor->nexts[searchLvl] != NULL) {
            precedentCursor = searchCursor;
            searchCursor = searchCursor->nexts[searchLvl];
        }
        else{
            while(searchCursor->nexts[searchLvl] == NULL){
                searchLvl--;
                if(searchLvl == -1) return -1;
            }
            searchCursor = searchCursor->nexts[searchLvl];
        }

        while(val<searchCursor->value){
            searchLvl--;
            if(searchLvl == -1) return -1;
            searchCursor = precedentCursor->nexts[searchLvl];
            }
    }
    if(searchCursor->value == val) return 1;
    return -1;
}

void displayList(t_d_list list){
        for(int g = 0; g<list.max_level; g++){
            t_d_cell* ptrTest = list.heads[g];
            printf("[list head_%d @-]", g);
            while(ptrTest != NULL){
                printf("-->[ %d|@-]", ptrTest->value);
                if(ptrTest->nexts[g] != NULL){
                    for(int space = 0; space<2*g-1; space++){
                        printf("----------");
                    }
                }
                ptrTest = ptrTest->nexts[g];
            }
            printf("-->NULL");
            printf("\n");
    }
}
