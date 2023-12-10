#ifndef PROJECTL2_CONTACT_H
#define PROJECTL2_CONTACT_H

typedef struct s_time
{
    int year, month, day, hour, minute;
}t_time;

typedef struct s_duration
{
    int hour, minute;
}t_duration;

typedef struct s_appointment
{
    char *purpose;
    t_time time;
    t_duration duration;
}t_appointement;

typedef struct s_contact
{
    char *surname;
    char *firstname;
    t_appointement **appointement;
    int appointementNumber;
    struct s_contact **nexts;
} t_contact;

typedef struct s_contact_list
{
    t_contact **heads;
    int max_level;
    int nElement;
}t_contact_list;

t_appointement* createAppointement(t_duration dur, t_time time, char* purpose);
t_contact* createContact(char *surname, char *firstname);
t_contact_list createContactList();
void insertContact(t_contact_list *contactList, char *surname, char *firstname);
void rePointer(t_contact_list *cList, t_contact *verifPtr);
t_contact *searchContact(t_contact_list *contactList, char *surname, char *firstname);
int fillContact();

#endif //PROJECTL2_CONTACT_H
