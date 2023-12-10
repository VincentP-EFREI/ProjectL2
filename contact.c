#include "contact.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <windows.h>

void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char* scanString() {
    int bufferSize = 5;  // Initial size of the buffer
    char *buffer = (char*)malloc(bufferSize * sizeof(char));

    if (buffer == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    int index = 0;  // Index to keep track of the current position in the buffer
    char ch;

    flushInputBuffer();  // Clear the input buffer

    // Read characters until a newline is encountered
    while ((ch = getchar()) != '\n') {
        // If the buffer is full, double its size using realloc
        if (index == bufferSize - 1) {
            bufferSize *= 2;
            buffer = (char*)realloc(buffer, bufferSize * sizeof(char));

            // Check if realloc was successful
            if (buffer == NULL) {
                free(buffer);  // Free the original buffer before returning
                return NULL;   // Return NULL to indicate a memory allocation error
            }
        }

        // Store the current character in the buffer
        buffer[index++] = ch;
    }

    // Add a null-terminating character to mark the end of the string
    buffer[index] = '\0';

    // Return the dynamically allocated string
    return buffer;
}

// Function to create a new contact and initialize its fields
t_contact* createContact(char *surname, char *firstname) {
    // Allocate memory for a new contact structure
    t_contact* contact = (t_contact*)malloc(sizeof(t_contact));

    // Set the surname and firstname fields of the contact
    contact->surname = surname;
    contact->firstname = firstname;

    // Initialize the appointment number to 0
    contact->appointementNumber = 0;

    // Allocate memory for an array of pointers to the next contacts and initialize them to NULL
    contact->nexts = (t_contact**)calloc(4, sizeof(t_contact*));

    // Return a pointer to the created contact
    contact->appointement = (t_appointement **)calloc(5, sizeof(t_appointement*));
    return contact;
}

// Function to create a new contact list and initialize its fields
t_contact_list createContactList() {
    // Create a new contact list
    t_contact_list list;

    // Initialize the number of elements to 0
    list.nElement = 0;

    // Set the maximum level of the list to 4
    list.max_level = 4;

    // Allocate memory for an array of pointers to the heads of the list and initialize them to NULL
    list.heads = (t_contact **)calloc(4, sizeof(t_contact*));

    // Return the created contact list
    return list;
}

t_appointement* createAppointement(t_duration dur, t_time time, char* purpose) {
    t_appointement *appointement = (t_appointement*)malloc(sizeof(t_appointement));
    appointement->duration = dur;
    appointement->time = time;
    appointement->purpose = purpose;
    return appointement;
}

void rePointer2(t_contact_list *cList){
    int g = 0;
    t_contact *contact = cList->heads[0];
    t_contact *currentPtr = contact;
    cList->heads[1] = cList->heads[0];
    cList->heads[2] = cList->heads[0];
    cList->heads[3] = cList->heads[0];
    while(g<3){
        int val = strncmp(contact->surname, currentPtr->surname, 3-g);
        if(val < 0){
            contact->nexts[g+1] = currentPtr;
            contact = currentPtr;
//            printf("%s\n", contact->surname);
        }
        currentPtr = currentPtr->nexts[g];
        if(currentPtr == NULL){
            g++;
            currentPtr = cList->heads[0];
            contact = currentPtr;
        }
    }
}

void rePointerFrom(t_contact_list *cList, t_contact *Lvl3Ptr){
    int g = 0;
    t_contact *contact = Lvl3Ptr;
    t_contact *currentPtr = contact;
    while(g<3){ // Loop until g is less than 3, attempting to insert the contact in a sorted manner.
        int val = strncmp(contact->surname, currentPtr->surname, 3-g); // Compare the first three characters
                                                                       // of the surnames and store the result in val.
        if(val < 0){    // If the comparison is less than 0, adjust pointers to insert the contact.
            contact->nexts[g+1] = currentPtr;
            contact = currentPtr;
        }
        currentPtr = currentPtr->nexts[g];  // Move to the next level in the linked list.

        // Check for NULL or a match in the next level's surname; then increment g.
        if(currentPtr == NULL || (currentPtr->nexts[3] != NULL &&
                                                strncmp(currentPtr->nexts[3]->surname, Lvl3Ptr->surname,1) == 0)){
            g++;
            currentPtr = Lvl3Ptr;
            contact = currentPtr;
        }
    }
}


void rePointer(t_contact_list *cList, t_contact *verifPtr){

    //Check if verifPtr has a non NULL nexts[0] and nexts[0]->nexts[1] is NULL; return if true.
    if(verifPtr->nexts[0] != NULL && verifPtr->nexts[0]->nexts[1] == NULL) return;

    t_contact *ptrTravel = cList->heads[0]; // If verifPtr->nexts[0] is NULL, traverse to the end and insert verifPtr.
    if(verifPtr->nexts[0] == NULL){
        while(ptrTravel->nexts[3] != NULL){
            ptrTravel = ptrTravel->nexts[3];
        }
        rePointerFrom(cList, ptrTravel);
        return;
    }

    //Traverse the list to find the correct position and insert verifPtr.
    while(ptrTravel->nexts[3] != NULL && strcmp(ptrTravel->nexts[3]->surname, verifPtr->surname) < 0){
        ptrTravel = ptrTravel->nexts[3];
    }
    rePointerFrom(cList, ptrTravel);

}

// Function to assign pointers in the contact list
void assignPointer(t_contact_list *clist, t_contact *BeforePtr, t_contact *AfterPtr) {
    // Assign the next pointer of AfterPtr to be the same as the next pointer of BeforePtr
    AfterPtr->nexts[0] = BeforePtr->nexts[0];

    // Update the next pointer of BeforePtr to point to AfterPtr
    BeforePtr->nexts[0] = AfterPtr;

    // Reorganize pointers in the contact list
    rePointer(clist, AfterPtr);
}

// Function to insert a contact at the head of the contact list
void insertHeadContact(t_contact_list *contactList, t_contact *contact) {
    // Set the next pointer of the new contact to point to the current head of the list
    contact->nexts[0] = contactList->heads[0];

    // Update the head of the list to be the new contact
    contactList->heads[0] = contact;
    contactList->heads[1] = contactList->heads[0];
    contactList->heads[2] = contactList->heads[0];
    contactList->heads[3] = contactList->heads[0];
}

t_contact *searchContact(t_contact_list *contactList, char *surname, char *firstname){
    if(surname == NULL || firstname == NULL) return NULL;
    if (contactList->heads[0] == NULL) return NULL;
    int level = 3;
    // Initialize pointers for traversal
    t_contact *currentPtr = contactList->heads[0];
    t_contact *previousPtr = contactList->heads[0];
    while(level > -1)
    {
        // Traverse the list based on surname
        while (currentPtr != NULL && strcmp(surname, currentPtr->surname) > 0) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nexts[level];
            while(currentPtr == NULL){
                level--;
                if (level == -1) break;
                currentPtr = previousPtr->nexts[level];
            }
        }
        if(currentPtr != NULL && strcmp(surname, currentPtr->surname) < 0){
            currentPtr = previousPtr;
        }

        // If surnames are the same, traverse based on firstname
        while (currentPtr != NULL && currentPtr->surname == surname && strcmp(firstname, currentPtr->firstname) > 0) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nexts[0];
        }
        level--;
    }
    if(currentPtr != NULL && currentPtr->surname == surname && currentPtr->firstname) return currentPtr;
    return NULL;
}

// Function to insert a contact in a sorted manner into the contact list
void insertContact(t_contact_list *contactList, char *surname, char *firstname) {
    if(surname == NULL || firstname == NULL) return;
    // Increment the number of elements in the contact list
    contactList->nElement++;

    // Create a new contact with the provided surname and firstname
    t_contact* ptr = createContact(surname, firstname);

    // If the list is empty, insert the new contact at the head and return
    if (contactList->heads[0] == NULL) {
        insertHeadContact(contactList, ptr);
        return;
    }
    int level = 3;
    // Initialize pointers for traversal
    t_contact *currentPtr = contactList->heads[0];
    t_contact *previousPtr = contactList->heads[0];
    while(level > -1)
    {
        // Traverse the list based on surname
        while (currentPtr != NULL && strcmp(surname, currentPtr->surname) > 0) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nexts[level];
            while(currentPtr == NULL){
                level--;
                if (level == -1) break;
                currentPtr = previousPtr->nexts[level];
            }
        }
        if(currentPtr != NULL && strcmp(surname, currentPtr->surname) < 0){
            currentPtr = previousPtr;
        }

        // If surnames are the same, traverse based on firstname
        while (currentPtr != NULL && currentPtr->surname == surname && strcmp(firstname, currentPtr->firstname) > 0) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nexts[0];
        }
        level--;
    }

    // Assign pointers to insert the new contact in the sorted order
    assignPointer(contactList, previousPtr, ptr);
}

int fillContact(){
    LARGE_INTEGER InsertStart, InsertEnd, frequencyInsert;
    QueryPerformanceFrequency(&frequencyInsert);

    QueryPerformanceCounter(&InsertStart);
    FILE *name;
    char *bufferName = (char*)calloc(32, sizeof(char));
    sprintf(bufferName, "CSV/nat2021.csv");
    name = fopen(bufferName, "r");
    if (name == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;  // Return an error code
    }

    char *bufferString = NULL;
    char *bufferString2 = NULL;
    int bufferSize = 50;
    t_contact_list cList = createContactList();
    char *strFirstname, *strSurname = NULL;
    for(int i = 0; i<15000; i++) {
        bufferString = (char *) malloc(bufferSize * sizeof(char));
        if (fgets(bufferString, bufferSize, name) != NULL) {
            bufferString[strcspn(bufferString, "\n")] = '\0';
            strSurname = (char *) calloc(50, sizeof(char));
            strcpy(strSurname, bufferString);
        }
        bufferString2 = (char *) malloc(bufferSize * sizeof(char));
        if (fgets(bufferString2, bufferSize, name) != NULL) {
            bufferString2[strcspn(bufferString2, "\n")] = '\0';
            strFirstname = (char*)calloc(50, sizeof(char));
            strcpy(strFirstname, bufferString2);
        }
        insertContact(&cList, strSurname, strFirstname);
    }
    fclose(name);



    QueryPerformanceCounter(&InsertEnd);
    printf("search time, %f s\n", (double)(InsertEnd.QuadPart - InsertStart.QuadPart) / frequencyInsert.QuadPart);
}