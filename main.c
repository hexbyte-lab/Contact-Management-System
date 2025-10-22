#include <stdio.h>
#include <string.h>

int global_id = 0;
// Contact Struct
typedef struct {
    int id;
    char name[50];
    char phone_number[15];
    char note[50];
} Contact;

// to remove the new line at the end of the inputs.
void remove_newline(char *str){
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n'){
        str[len - 1] = '\0';
    }
}
// Main Menu
void menu(){
    printf("1. Add\n");
    printf("2. Edit\n");
    printf("3. Delete\n");
    printf("4. Search\n");
    printf("5. List\n");
}

// assign and ID for a contact automatically
void assignID(Contact *contact){
    contact->id = global_id;
    global_id += 1;
}

// Add Contact
void add_contact(Contact *new_contact){
    printf("xxx ADD A NEW CONTACT xxx\n");
    int index = global_id;
    // assign the ID
    assignID(&new_contact[index]);

    // get the name
    char name[50];
    printf("Name: \n" );
    fgets(name, sizeof(name), stdin);
    remove_newline(name);
    strcpy(new_contact[index].name, name);

    // get the phone number
    char phone_num[50];
    printf("Phone Number: \n" );
    fgets(phone_num, sizeof( phone_num), stdin);
    remove_newline(phone_num);
    strcpy(new_contact[index].phone_number,  phone_num);

    // get the note
    char note[50];
    printf("Note: \n");
    fgets(note, sizeof(note), stdin);
    remove_newline(note);
    strcpy(new_contact[index].note, note);

    // Success message!
    printf("Success, Contact %s has been added!\n", name);
}

//list Contact
void list_contact(Contact *contact) {
    printf("xxx CONTACT LIST xxx\n");
    for (int i = 0; i < global_id; i++) {
        printf("%d - ID: %d | Name: %s | Phone: %s | Note: %s\n",
               i + 1, contact[i].id, contact[i].name,
               contact[i].phone_number, contact[i].note);
    }
}


int main(){
    Contact contact_array[50];
    assignID(&contact_array[0]);
    // printf("GID: %d\n", global_id);
    strcpy(contact_array[0].name, "James");
    strcpy(contact_array[0].note, "James Charles the gay TikToker");
    strcpy(contact_array[0].phone_number, "+1 123 321 123");
    // menu();
    list_contact(contact_array);
    return 0;
}