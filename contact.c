////
//// Created by macke on 03/12/2023.
////
//
//#include "contact.h"
//#include "set.h"
//#include "stdlib.h"
//#include "stdio.h"
//#include "math.h"
//
//char *scanString(){
//    int bufferSize = 5;
//    char *buffer = (char*)malloc(bufferSize * sizeof(char));
//
//    int index = 0;
//    char ch;
//    while ((ch = getchar()) != '\n') {
//        if (index == bufferSize - 1) {
//            bufferSize *= 2;
//            buffer = (char*)realloc(buffer, bufferSize * sizeof(char));
//            if (buffer == NULL) {
//                return "error";
//            }
//        }
//        buffer[index++] = ch;
//    }
//    return buffer;
//}
//
//void setPointer(t_contact *pContact, t_contact_list *pList, int i) {
//    if(i == 0) return;
//    t_contact *destinationPtr = pContact;
//    for(int h = 1; h <= pList->max_level; h++){
//        destinationPtr = pContact;
//        int nTravel = (int)pow(2,h);
//        if(i % nTravel*1.5 == 0){
//            for(int g = 0; g < nTravel; g++){
//                if(destinationPtr == NULL) break;
//                destinationPtr = destinationPtr->nexts[0];
//            }
//            pContact->nexts[h] = destinationPtr;
//            pList->heads[h] = pContact;
//        }else return;
//    }
//}
//
//void insertHeadContact(t_contact_list *contactList, t_contact *cell){
//    cell->nexts[0] = contactList->heads[0];
//    contactList->heads[0] = cell;
//
//    setPointer(cell, contactList, contactList->nElement-1);
//
//}
//
//void insertContact(t_contact_list *contactList, int value){
//    contactList->nElement++;
//    t_contact* ptr = createEmptyCell(value, contactList->max_level);
//    if(contactList->heads[0] == NULL){
//        insertHeadContact(contactList, ptr);
//        return;
//    }
//    if(value < contactList->heads[0]->value){
//        insertHeadContact(contactList, ptr);
//        return;
//    }
//
//    t_contact* ptrNext = contactList->heads[0];
//    t_contact* ptrBefore = ptrNext;
//    while(value > ptrNext->value && ptrNext->nexts[0] != NULL){
//        ptrBefore = ptrNext;
//        ptrNext = ptrNext->nexts[0];
//    }
//    if(value > ptrNext->value){
//        ptr->nexts[0] = NULL;
//        ptrNext->nexts[0] = ptr;
//        return;
//    }
//    ptr->nexts[0] = ptrBefore->nexts[0];
//    ptrBefore->nexts[0] = ptr;
//}
