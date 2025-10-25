#include <stdio.h>
#include <string.h>
#include <windows.h> // Used for the Sleep() function in progress_bar

// Global constants and variables
int global_id = 0;            // id for each contact
#define MAX_CONTACTS 10       // maximum numbers of contacts allowed!
#define INPUT_BUFFER_SIZE 100 // Buffer size for robust input

// Contact Struct
typedef struct
{
    int id;
    char name[50];
    char phone_number[15];
    char note[50];
} Contact;

// to remove the new line at the end of the inputs.
void remove_newline(char *str)
{
    // printf("Remove line fun has just been called for: ");
    size_t len = strlen(str);
    // printf("%d is the thing", len);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
        // if(str[len - 1] == '\0'){
        //     printf("done"); // BUG: This line is redundant and prints "done" unexpectedly.
        // }
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
    printf("4. Search Contact (TODO)\n");
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
void edit_contact(Contact *contact, int count)
{
    // first print the contact list for the user
    // list_contact()

    char input_buffer[INPUT_BUFFER_SIZE];
    char search_name[50];
    int contact_index = -1;

    printf("[!] EDIT A CONTACT\n");
    printf("[!] Enter the name of the contact you wish to eidt: >>>: ");

    // if(fgets(search_name, sizeof(search_name), stdin) == NULL){
    //     printf("[-] Input error.\n");
    //     return;
    // }
    while(fgets(search_name, sizeof(search_name), stdin) == NULL){
        printf("[-] Invalid Input. try again\n");
        // no I want them to try again.
    }
    while(search(search_name, sizeof(search_name), stdin) == -1){
        printf("[-] Error! Contact '%s' not found\n");
        // I guess we need to clear the search_name to get a new one??
    }
    remove_line(search_name);
    // search for the contact
    contact_index = search_contact_by_name(contact, count, search_name);

    if(contact_index == -1){
        
    }
}
int main()
{

    Contact contact_array[MAX_CONTACTS];
    char input_buffer[INPUT_BUFFER_SIZE];
    int user_input;

    // assignID(&contact_array[0]);
    // // printf("GID: %d\n", global_id);
    // strcpy(contact_array[0].name, "James");
    // strcpy(contact_array[0].note, "James Charles the gay TikToker");
    // strcpy(contact_array[0].phone_number, "+1 123 321 123");
    // getchar();

    int app_running = 1;

    while (app_running)
    {
        menu();
        printf("(select a number and hit enter) >>>: ");

        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
        {
            printf("[-] Input error \n");
            app_running = 0;
            continue;
        }

        if (sscanf(input_buffer, "%d", &user_input) != 1)
        {
            printf("[-] Invalid input! Please enter a number.\n");
            continue;
        }

        switch (user_input)
        {
        case 1:
            // add contact
            add_contact(contact_array);
            break;
        case 2:
            // edit contact
            edit_contact(contact_array, global_id); // passing thte global_id for sake of a clean code
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
    // list_contact(contact_array);
    return 0;
}
