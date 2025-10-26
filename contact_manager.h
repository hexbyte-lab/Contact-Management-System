#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

#include <stdbool.h>

// Global constants and variables
extern int global_id;               // id for each contact, extern makes it a declaration
#define MAX_CONTACTS 10           // maximum numbers of contacts allowed!
#define INPUT_BUFFER_SIZE 100     // Buffer size for input

// Contact Struct
typedef struct
{
    int id;
    char name[50];
    char phone_number[15];
    char note[50];
} Contact;

// Function Prototypes

// Utility functions
void remove_newline(char *str);
void progress_bar(int length);
void menu();
void assignID(Contact *contact);

// Contact management functions
void add_contact(Contact *new_contact);
void list_contact(Contact *contact);
void edit_contact(Contact *contact);
void search_contact(Contact *contact);

#endif // CONTACT_MANAGER_H