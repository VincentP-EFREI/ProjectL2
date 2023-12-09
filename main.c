#include "contact.h"
#include "stdio.h"

int main() {

    t_contact_list cList = createContactList();
    char int_strSurname[5];
    char int_strFirstname[5];
    for(int surname = 0; surname<100; surname++){
        sprintf(int_strSurname, "%d", surname);
        insertContact(&cList, int_strSurname, int_strSurname);
//        for(int firstname = 0; firstname<10; firstname++){
//            sprintf(int_strFirstname, "%d", firstname);
//            insertContact(&cList, int_strSurname, int_strFirstname);
//        }
    }
    t_contact *ptr = cList.heads[0];
    while(ptr != NULL){
        printf("%s_%s\n", ptr->surname, ptr->firstname);
        ptr = ptr->nexts[0];
    }

//    t_d_list tentTestList = createEmptyList(6);
//    for(int num = 50; num>0; num--){
//        insert(&tentTestList, num);
//    }
//
//    for(int g = 0; g<tentTestList.max_level; g++){
//        t_d_cell* ptrTest = tentTestList.heads[g];
//        while(ptrTest != NULL){
//            printf("%d ", ptrTest->value);
//            ptrTest = ptrTest->nexts[g];
//        }
//        printf("\n\n");
//    }



//    TimeTest(22, 6553600);

//    printf("%d\n", simpleSearch(testList, -1));
//    displayTime();
//    t_d_list list = createEmptyList(8);
//    printf("n : %d \n", list.n);
//
//    FILE* nextN_File = fopen("level.txt", "w");
//
//    for(int g = 0; g<list.max_level; g++){
//        for (int i = 0; i < list.n; i++) {
//            if(g <= list.nLevelArray[i]) fprintf(nextN_File, "0  ");
//            else fprintf(nextN_File, "   ");
//        }
//        fprintf(nextN_File, "\n");
//    }
//    fclose(nextN_File);
//
//    FILE* output = fopen("output.txt", "w");
//    t_d_list list2 = createEmptyList(3);
//    for(int h = 0; h<5; h++){
//        int randomVal = rand();
//        insert(&list2, randomVal);
//        printf("%d\n", h);
//    }
//
//    setLevel(&list2);
//
//    char space[1024] = "  ";
//    t_d_cell* ptr = list2.heads[0];
//    for(int k = 0; k<list2.max_level; k++){
//        while (ptr != NULL){
//            fprintf(output,"%d ", ptr->value);
//            fprintf(output, "%s", space);
//            ptr = ptr->nexts[k];
//        }
//        ptr = list2.heads[k];
//        strcat(space, "  ");
//        fprintf(output,"\n");
//    }
//
//    fclose(output);
    return 0;
}

