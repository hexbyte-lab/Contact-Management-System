#include <stdio.h>
#include <string.h>
#include <windows.h> // Used for the Sleep() function
#include "contact_manager.h" // Include your own header

// Initialize the global variables declared in the header file
int global_id = 0;

// to remove the new line at the end of the inputs.
void remove_newline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

// a progress bar
void progress_bar(int length)
{
    printf("Saving contact: [");
    for (int i = 0; i < length; i++)
    {
        printf("#");
        fflush(stdout); // force it to print immediately
        Sleep(2);       // wait 2 milliseconds per step
    }
    printf("] Done!\n");
}

// Main Menu
void menu()
{
    printf("\n--- CONTACT MANAGER ---\n");
    printf("1. Add Contact\n");
    printf("2. Edit Contact (TODO)\n");
    printf("3. Delete Contact (TODO)\n");
    printf("4. Search Contact\n");
    printf("5. List Contacts\n");
    printf("0. Exit\n");
}

// assign and ID for a contact automatically
void assignID(Contact *contact)
{
    contact->id = global_id;
    global_id += 1;
}

// Add Contact
void add_contact(Contact *new_contact)
{
    // large buffer for all temporary input reading
    char input_buffer[INPUT_BUFFER_SIZE];

    if (global_id >= MAX_CONTACTS)
    {
        printf("[-] ERROR, MAXIMUM %d CONTACTS\n", MAX_CONTACTS);
        return;
    }
    printf("[!] ADD A NEW CONTACT\n");
    int index = global_id;
    // assign the ID
    assignID(&new_contact[index]);

    // get the name
    printf("Name: ");
    fgets(input_buffer, sizeof(new_contact[index].name), stdin);

    remove_newline(input_buffer);

    strncpy(new_contact[index].name, input_buffer, sizeof(new_contact[index].name) - 1);
    new_contact[index].name[sizeof(new_contact[index].name) - 1] = '\0'; // ensuring

    // get the phone number
    printf("Phone Number: ");
    fgets(input_buffer, sizeof(new_contact[index].phone_number), stdin);
    remove_newline(input_buffer);

    strncpy(new_contact[index].phone_number, input_buffer, sizeof(new_contact[index].phone_number) - 1);
    new_contact[index].phone_number[sizeof(new_contact[index].phone_number) - 1] = '\0';

    // get the note
    printf("Note: ");
    fgets(input_buffer, sizeof(new_contact[index].note), stdin);

    remove_newline(input_buffer);

    strncpy(new_contact[index].note, input_buffer, sizeof(new_contact[index].note) - 1);
    new_contact[index].note[sizeof(new_contact[index].note) - 1] = '\0';

    // some delay just to make it look cool!
    progress_bar(50);
    // Success message!
    printf("[!] Success, Contact %s has been added!\n", new_contact[index].name);
}

// list Contact
void list_contact(Contact *contact)
{
    if (global_id == 0)
    {
        printf("[!] COTACT LIST IS EMPTY\n");
        return;
    }

    printf("[!] CONTACT LIST\n");
    for (int i = 0; i < global_id; i++)
    {
        printf("---------------------------------\n");
        printf("%d- %s | %s | Note: %s\n",
               i + 1, contact[i].name,
               contact[i].phone_number, contact[i].note);
        printf("---------------------------------\n");
    }
}

// edit
void edit_contact(Contact *contact)
{
    if (global_id == 0)
    {
        printf("[!] COTACT LIST IS EMPTY. Cannot edit.\n");
        return;
    }

    // first print the contact list for the user
    list_contact(contact);

    // asking for a name
    printf("Enter a name >>>: ");
    char input_buffer[INPUT_BUFFER_SIZE] = {'\0'};
    fgets(input_buffer, sizeof(input_buffer), stdin);
    remove_newline(input_buffer);

    bool found = false;
    int contact_index = -1;
    // seraching for contact
    // Note: The original loop condition `i <= global_id` was incorrect, it should be `i < global_id`
    for (int i = 0; i < global_id; i++)
    {
        if (strcmp(input_buffer, contact[i].name) == 0)
        {
            contact_index = contact[i].id; // Assuming contact[i].id is the correct index for editing
            found = true;
            break;
        }
    }
    if (found)
    {
        printf("Found: %s | %s | %s\n", contact[contact_index].name, contact[contact_index].phone_number, contact[contact_index].note);
        printf("Select field to edit: \n");
        printf("1. Name\n2. Phone\n3. Note\n0. Cancel \n");

        bool app_running = true;

        while(app_running){
            printf(">>>: ");
            fgets(input_buffer, sizeof(input_buffer), stdin);
            remove_newline(input_buffer);
            int user_input;

            if (sscanf(input_buffer, "%d", &user_input) != 1)
            {
                printf("[-] Invalid input! Please enter a number.\n");
                continue;
            }

            switch (user_input)
            {
            // edit name
            case 1:
                printf("Enter a new name: ");
                // Re-use input_buffer, ensure it's large enough for the name
                fgets(input_buffer, sizeof(contact[contact_index].name), stdin);
                remove_newline(input_buffer);
                // Use strncpy for safety
                strncpy(contact[contact_index].name, input_buffer, sizeof(contact[contact_index].name) - 1);
                contact[contact_index].name[sizeof(contact[contact_index].name) - 1] = '\0';
                
                // double check
                if(strcmp(contact[contact_index].name, input_buffer) == 0){
                    printf("Done %s | %s | %s\n", contact[contact_index].name, contact[contact_index].phone_number, contact[contact_index].note);
                    progress_bar(50);
                } else{
                    printf("There was a problem editing you your name\n");
                }
                app_running = false;
                break;
            case 2:
                // edit phone number
                printf("Enter a new phone number: ");
                fgets(input_buffer, sizeof(contact[contact_index].phone_number), stdin);
                remove_newline(input_buffer);
                strncpy(contact[contact_index].phone_number, input_buffer, sizeof(contact[contact_index].phone_number) - 1);
                contact[contact_index].phone_number[sizeof(contact[contact_index].phone_number) - 1] = '\0';

                progress_bar(50);
                printf("[!] Phone number updated for %s.\n", contact[contact_index].name);
                app_running = false;
                break;
            case 3:
                // edit note
                printf("Enter a new note: ");
                fgets(input_buffer, sizeof(contact[contact_index].note), stdin);
                remove_newline(input_buffer);
                strncpy(contact[contact_index].note, input_buffer, sizeof(contact[contact_index].note) - 1);
                contact[contact_index].note[sizeof(contact[contact_index].note) - 1] = '\0';

                progress_bar(50);
                printf("[!] Note updated for %s.\n", contact[contact_index].name);
                app_running = false;
                break;
            case 10:
                printf("[!] You've found a secret! nothing happens tho\n");
                break;
            case 0:
                app_running = false;
                printf("[!] Edit cancelled.\n");
                break;
            default:
                printf("[-] Invalid option. Please try again.\n");
                break;
            }
        }
    }
    else
    {
        printf("[!] Contact %s has not been found\n", input_buffer);
    }
}


// search
void search_contact(Contact *contact)
{
    if (global_id == 0)
    {
        printf("[!] COTACT LIST IS EMPTY\n");
        return;
    }
    char input_buffer[INPUT_BUFFER_SIZE] = {'\0'};

    int found_count = 0;
    
    printf("Enter a name to search >>>: ");
    fgets(input_buffer, sizeof(input_buffer), stdin);
    remove_newline(input_buffer);

    for (int i = 0; i < global_id; i++) // Corrected loop condition from i <= global_id to i < global_id
    {
        // 0 means two strings have zero difference
        if (strcmp(contact[i].name, input_buffer) == 0)
        {
            printf("---------------------------------\n");
            printf("%d- %s | %s | Note: %s\n",
                   i + 1, contact[i].name,
                   contact[i].phone_number, contact[i].note);
            printf("---------------------------------\n");
            found_count++;
            // Don't break here if you want to find all matches (though IDs should be unique)
            // If only searching for a perfect match of the primary name, breaking is fine.
            break; 
        }
    }
    
    if (found_count == 0)
    {
        printf("[!] Contact \"%s\" has not been found\n", input_buffer);
    }
}