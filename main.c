#include "contact.h"
#include "stdio.h"
#include "set.h"
#include "stdlib.h"
#include <windows.h>
#include "TimeTest.h"
#include "math.h"

int main() {
    char answer;
    int on = 1;
    t_contact_list contactList = createContactList();
    LARGE_INTEGER InsertStart, InsertEnd, frequencyInsert;
    QueryPerformanceFrequency(&frequencyInsert);

    while (on) {
        do {
            system("cls");

            printf("A - Insert a contact\n");
            printf("B - Add an appointment\n");
            printf("C - Fill contact\n");
            printf("Your choice :");
            scanf(" %c", &answer);
        } while ((answer < 'A' || answer > 'F') && (answer < 'a' || answer > 'f'));

        // Call the function corresponding to the action
        switch (answer) {
            case 'A':
            case 'a':
                system("cls");
                printf("Surname :");
                char *sur = (char*) malloc(25*sizeof(char));
                scanf("%s", sur);
                system("cls");
                printf("Surname is %s\n", sur);
                printf("Firstname :");
                char *first = (char*) malloc(25*sizeof(char));
                scanf("%s", first);
                system("cls");
                printf("Surname is %s\n", sur);
                printf("Firstname is %s\n", first);
                QueryPerformanceCounter(&InsertStart);
                insertContact(&contactList, sur, first);
                QueryPerformanceCounter(&InsertEnd);
                printf("%f", (double)(InsertEnd.QuadPart - InsertStart.QuadPart) / frequencyInsert.QuadPart);
                system("pause");
                break;
            case 'B':
            case 'b':
                system("cls");
                printf("(Time) year :");
                int timeYear;
                scanf("%d", &timeYear);
                system("cls");
                printf("(Time) month :");
                int timeMonth;
                scanf("%d", &timeMonth);
                system("cls");
                printf("(Time) day :");
                int timeDay;
                scanf("%d", &timeDay);
                system("cls");
                printf("(Time) hour :");
                int timeHour;
                scanf("%d", &timeHour);
                system("cls");
                printf("(Time) Minute :");
                int timeMinute;
                scanf("%d", &timeMinute);
                system("cls");

                printf("(Duration) Hour :");
                int DurationHour;
                scanf("%d", &DurationHour);
                system("cls");
                printf("(Duration) Minute :");
                int DurationMinute;
                scanf("%d", &DurationMinute);
                system("cls");

                t_duration dur;
                dur.hour = DurationHour;
                dur.minute = DurationMinute;

                t_time time;
                time.year = timeYear;
                time.month = timeMonth;
                time.day = timeDay;
                time.hour = timeHour;
                time.minute = timeMinute;


                system("cls");
                printf("Purpose :");
                char *purpose = (char*) malloc(50*sizeof(char));
                scanf("%s", purpose);
                t_appointement *toAdd = createAppointement(dur, time, purpose);

                system("cls");
                printf("Add to which contact, Surname :");
                char *surAdd = (char*) malloc(25*sizeof(char));
                scanf("%s", surAdd);
                system("cls");
                printf("Surname is %s\n", surAdd);
                printf("Firstname :");
                char *firstAdd = (char*) malloc(25*sizeof(char));
                scanf("%s", firstAdd);

                t_contact *found = searchContact(&contactList, surAdd, firstAdd);
                if(found != NULL){
                    found->appointement[0] = toAdd;
                    found->appointementNumber++;
                }else{
                    printf("The contact doesn't exist sorry\n");
                }
                system("pause");
                break;
            case 'C':
            case 'c':
                fillContact();
                break;
            default:
                printf("Try again.\n");
                break;
        }
    }


}

