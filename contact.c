#include "contact.h"
#include "set.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "string.h"

char *scanString(){
    int bufferSize = 5;
    char *buffer = (char*)malloc(bufferSize * sizeof(char));

    int index = 0;
    char ch;
    while ((ch = getchar()) != '\n') {
        if (index == bufferSize - 1) {
            bufferSize *= 2;
            buffer = (char*)realloc(buffer, bufferSize * sizeof(char));
            if (buffer == NULL) {
                return "error";
            }
        }
        buffer[index++] = ch;
    }
    buffer[index] = '\0';
    return buffer;
}

t_contact* createContact(char *surname, char *firstname){
    t_contact* contact = (t_contact*)malloc(sizeof(t_contact));
    contact->surname = surname;
    contact->firstname = firstname;
    contact->appointementNumber = 0;
    contact->nexts = (t_contact**) calloc(4, sizeof(t_contact*));

    return contact;
}

t_contact_list createContactList(){
    t_contact_list list;
    list.nElement = 0;
    list.max_level = 4;
    list.heads = (t_contact **)calloc(4, sizeof(t_contact*));
    return list;
}

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

void insertHeadContact(t_contact_list *contactList, t_contact *contact){
    contact->nexts[0] = contactList->heads[0];
    contactList->heads[0] = contact;
    int level = 0;
    t_contact *currentPtr = contact;
//    while(level < 3 && currentPtr != NULL){
//        int val = strncmp(contact->surname, currentPtr->surname, 3);
//        if(val < 0){
//            contact->nexts[1] = currentPtr;
//            level++;
//        }
//        val = strncmp(contact->surname, currentPtr->surname, 2);
//        if(val < 0){
//            contact->nexts[2] = currentPtr;
//            level++;
//        }
//        val = strncmp(contact->surname, currentPtr->surname, 1);
//        if(val < 0){
//            contact->nexts[3] = currentPtr;
//            level++;
//        }
//        currentPtr = currentPtr->nexts[0];
//    }
}

void insertContact(t_contact_list *contactList, char *surname, char *firstname){
    contactList->nElement++;
    t_contact* ptr = createContact(surname, firstname);

    if(contactList->heads[0] == NULL){
        insertHeadContact(contactList, ptr);

        printf("test1 %s\n", ptr->surname);
        return;
    }

    int cmpVal = strcmp(surname, contactList->heads[0]->surname);
    if(cmpVal < 0){
        insertHeadContact(contactList, ptr);

        printf("test2 %s\n", ptr->surname);
        return;
    }
    else if(cmpVal == 0) {
        cmpVal = strcmp(firstname, contactList->heads[0]->firstname);
        if(cmpVal < 0) insertHeadContact(contactList, ptr);

        printf("test3 %s\n", ptr->surname);
        return;
    }

    t_contact *currentPtr = contactList->heads[0];
    t_contact *previousPtr = NULL;
    t_contact *savedPtrLvl2 = NULL;
    t_contact *savedPtrLvl3 = NULL;
    while(currentPtr != NULL){
        if(currentPtr->nexts[2] != NULL){
            savedPtrLvl2 = currentPtr;
            if(currentPtr->nexts[3] != NULL){
                savedPtrLvl3 = currentPtr;
            }
        }

        cmpVal = strcmp(surname, currentPtr->surname);
        if(cmpVal > 0){
            previousPtr = currentPtr;
            currentPtr = currentPtr->nexts[0];
        }
        else if(cmpVal < 0){
            ptr->nexts[0] = previousPtr->nexts[0];
            previousPtr->nexts[0] = ptr;

            printf("test4 %s\n", ptr->surname);
            return;
        } else
        {
            while(currentPtr->surname == surname){
                cmpVal = strcmp(firstname, currentPtr->firstname);
                if(cmpVal > 0){
                    previousPtr = currentPtr;
                    currentPtr = currentPtr->nexts[0];
                }
                else{
                    ptr->nexts[0] = previousPtr->nexts[0];
                    previousPtr->nexts[0] = ptr;

                    printf("test5 %s\n", ptr->surname);
                    return;
                }
            }
        }
    }

    previousPtr->nexts[0] = ptr;
}