#include <stdio.h>
#include "set.h"
#include "stdlib.h"
#include "string.h"

int main() {

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

    FILE* output = fopen("output.txt", "w");
    t_d_list list2 = createEmptyList(3);
    for(int h = 0; h<5; h++){
        int randomVal = rand();
        insert(&list2, randomVal);
        printf("%d\n", h);
    }

    setLevel(&list2);

    char space[1024] = "  ";
    t_d_cell* ptr = list2.heads[0];
    for(int k = 0; k<list2.max_level; k++){
        while (ptr != NULL){
            fprintf(output,"%d ", ptr->value);
            fprintf(output, "%s", space);
            ptr = ptr->nexts[k];
        }
        ptr = list2.heads[k];
        strcat(space, "  ");
        fprintf(output,"\n");
    }

    fclose(output);



    return 0;
}
