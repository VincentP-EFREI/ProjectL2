#include "set.h"
#include "stdio.h"
#include "stdlib.h"

t_d_cell* createEmptyCell(int value, int nLevels){
    t_d_cell* cell = (t_d_cell*)malloc(sizeof(t_d_cell));
    cell->value = value;
    cell->nexts = (t_d_cell**) calloc(nLevels, sizeof(t_d_cell*));
    return cell;
}

t_d_list createEmptyList(int max_level){
    t_d_list list;
    list.max_level = max_level;
    list.heads = (t_d_cell**)calloc(max_level, sizeof(t_d_cell*));

    int n = 1;
    for(int i = 0; i<max_level; i++) n*=2;
    list.nLevelArray = calloc(n-1, sizeof(int));
    for(int i = 0; i<n-1; i++){
        for(int j = 2; j<n/2+1; j += j){
            if((i+1)%j==0){
                list.nLevelArray[i] += 1;
            }
        }
    }
    list.n = n;
    printf("\n");
    return list;
}

//Insert a cell with levels at the beginning (head) of the list (be careful to take into account the number of levels in the cell)
void insertHead(t_d_list *list, t_d_cell *cell){
    cell->nexts[0] = list->heads[0];
    list->heads[0] = cell;
    if(list->nLevelArray[list->n-list->nElement] != 1){
        for(int i = 1; i < list->nLevelArray[list->n-list->nElement]; i++);
        
    }

}

void insert(t_d_list *list, int value){
    t_d_cell* ptr = createEmptyCell(value, list->max_level);
    t_d_cell* ptrNext = list->heads[0];
    t_d_cell* ptrBefore = ptrNext;
    list->nElement++;
    if(list->heads[0] == NULL){
        insertHead(list, ptr);
        return;
    }
    if(value < list->heads[0]->value){
        insertHead(list, ptr);
        return;
    }
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

void setLevel(t_d_list* list){
    t_d_cell * ptrArr[list->nElement];
    t_d_cell * ptr = list->heads[0];
    for(int i = 0; i < list->nElement; i++){
        ptrArr[i] = &*ptr;
        ptr = ptr->nexts[0];
    }
    int m = 2;
    for(int l = 1; l<list->max_level; l++){
        if(m < list->nElement) list->heads[l] = ptrArr[m];
        else list->heads[l] = ptrArr[list->nElement];
        for(int h = 1; h<list->nElement; h+=m){
            ptrArr[h-1]->nexts[l] = &*ptrArr[h-1+m];
        }
        m*=2;
    }
}