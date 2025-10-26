#include "contact_manager.h" // my header
#include <stdio.h>
#include <string.h>

int main()
{

    Contact contact_array[MAX_CONTACTS];
    char input_buffer[INPUT_BUFFER_SIZE];
    int user_input;

    int app_running = 1;

    while (app_running) {
        menu();
        printf("(select a number and hit enter) >>>: ");

        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            printf("[-] Input error \n");
            app_running = 0;
            continue;
        }

        if (sscanf(input_buffer, "%d", &user_input) != 1) {
            printf("[-] Invalid input! Please enter a number.\n");
            continue;
        }

        switch (user_input) {
        case 1:
            // add contact
            add_contact(contact_array);
            break;
        case 2:
            // edit contact
            edit_contact(contact_array);
            break;
        case 3:
            // delete contact
            delete_contact(contact_array);
            break;
        case 4:
            // search contact
            search_contact(contact_array);
            break;
        case 5:
            // contact list
            list_contact(contact_array);
            break;
        case 10:
            printf("[!] You've found a secret! nothing happens tho\n");
            break;
        case 0:
            printf("[!] Exiting program. Goodbye!\n");
            app_running = 0;
            break;
        default:
            printf("[-] Invalid option. please try again\n");
            break;
        }
    }
    return 0;
}