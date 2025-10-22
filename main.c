#include <stdio.h>
#include <string.h>
#include <windows.h>

int global_id = 0;     // id for each contact
#define MAX_CONTACTS 1 // maximum numbers of contacts allowed!
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
        Sleep(2);       // wait 100 milliseconds per step
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
    char name[50];
    printf("Name: ");
    fgets(name, sizeof(name), stdin);
    // scanf("%s", &name);
    remove_newline(new_contact[index].name);
    strcpy(new_contact[index].name, name);

    // get the phone number
    char phone_num[15];
    printf("Phone Number: ");
    fgets(phone_num, sizeof(phone_num), stdin);
    // scanf("%s", &phone_num);
    remove_newline(new_contact[index].phone_number);
    strcpy(new_contact[index].phone_number, phone_num);

    // get the note
    char note[50];
    printf("Note: ");
    fgets(note, sizeof(note), stdin);
    // scanf("%s", &note);
    remove_newline(new_contact[index].note);
    strcpy(new_contact[index].note, note);
    // some delay just to make it look cool!
    progress_bar(100);
    // Success message!
    printf("[!] Success, Contact %s has been added!\n", name);
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

int main()
{
    Contact contact_array[50];
    // assignID(&contact_array[0]);
    // // printf("GID: %d\n", global_id);
    // strcpy(contact_array[0].name, "James");
    // strcpy(contact_array[0].note, "James Charles the gay TikToker");
    // strcpy(contact_array[0].phone_number, "+1 123 321 123");
    // getchar();

    int app_running = 1;
    int user_input;

    while (app_running)
    {
        menu();
        printf("(select a number and hit enter) >>>: ");
        if (scanf("%d", &user_input) != 1)
        {
            printf("[-] Invalid input! Please enter a number.\n");
            while (getchar() != '\n')
                ; // clear invalid input
            continue;
        }
        getchar(); // clear newline
        switch (user_input)
        {
        case 1:
            // add contact
            add_contact(contact_array);
            break;

        case 5:
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
            printf("[-] Invalid option. Please try again.\n");
            break;
        }
    }
    // list_contact(contact_array);
    return 0;
}