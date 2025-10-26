# Contact Manager in C

A simple command-line contact manager application written in C.  
Supports adding, editing, deleting, searching, and listing contacts. Designed to demonstrate proficiency in C, working with structs, arrays, and modular code organization.

---

## Features

- **Add Contact** – Add a new contact with name, phone number, and note.  
- **Edit Contact** – Edit existing contact fields (name, phone number, note).  
- **Delete Contact** – Mark a contact as deleted with confirmation.  
- **Search Contact** – Search for a contact by name.  
- **List Contacts** – Display all contacts currently stored.  

---

## Project Structure

/contact_manager_project
│
├── main.c # Entry point, menu and program loop
├── contact_manager.c # Implementation of contact functions and utilities
├── contact_manager.h # Structs, constants, and function prototypes
└── README.md # Project documentation

---

## Build Instructions

Compile the project using GCC:

```
gcc main.c contact_manager.c -o contact_manager.exe

./contact_manager.exe
```
## Usage

1. Run the Program
2. Follow the menu promts
3. Input is validated for numbers; text fields are trimmed automatically.

## Fututre Improvements

* Persistent storage – Save contacts to a file for long-term use.
* Full deletion – Remove contacts from memory instead of marking as deleted.
* Improved UI – Consider using ncurses or a GUI framework.
* Error handling & edge cases – Handle phone number format, duplicate names, etc.

## Notes
* Maximum of 10 contacts can be stored in this version. (can be easily edited)
* Designed for learning C programming practices.

## Demo
<img width="447" height="162" alt="2" src="https://github.com/user-attachments/assets/ab9ea8ad-2b1c-4d44-845d-426940899c9d" />
<img width="685" height="284" alt="3" src="https://github.com/user-attachments/assets/86bf5e08-f4e6-4356-bd9d-c6a38d7bdff5" />

  

