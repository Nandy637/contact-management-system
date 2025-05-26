#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "contacts.dat"

typedef struct {
    char name[50];
    char phone[15];
    char email[50];
} Contact;

void addContact();
void viewContacts();
void searchContact();
void deleteContact();
void clearBuffer();

int main() {
    int choice;
    
    while (1) {
        printf("\n===== Contact Management System =====\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer();  // Clear input buffer

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

void addContact() {
    FILE *file = fopen(FILE_NAME, "ab");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    Contact contact;
    printf("Enter Name: ");
    fgets(contact.name, sizeof(contact.name), stdin);
    contact.name[strcspn(contact.name, "\n")] = 0;  // Remove newline

    printf("Enter Phone: ");
    fgets(contact.phone, sizeof(contact.phone), stdin);
    contact.phone[strcspn(contact.phone, "\n")] = 0;

    printf("Enter Email: ");
    fgets(contact.email, sizeof(contact.email), stdin);
    contact.email[strcspn(contact.email, "\n")] = 0;

    fwrite(&contact, sizeof(Contact), 1, file);
    fclose(file);

    printf("Contact added successfully!\n");
}

void viewContacts() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("No contacts found.\n");
        return;
    }

    Contact contact;
    printf("\n===== Contact List =====\n");
    while (fread(&contact, sizeof(Contact), 1, file)) {
        printf("Name: %s\nPhone: %s\nEmail: %s\n", contact.name, contact.phone, contact.email);
        printf("-----------------------\n");
    }
    
    fclose(file);
}

void searchContact() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("No contacts found.\n");
        return;
    }

    char searchName[50];
    printf("Enter Name to Search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    Contact contact;
    int found = 0;
    while (fread(&contact, sizeof(Contact), 1, file)) {
        if (strcasecmp(contact.name, searchName) == 0) {
            printf("\nContact Found!\n");
            printf("Name: %s\nPhone: %s\nEmail: %s\n", contact.name, contact.phone, contact.email);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No contact found with name: %s\n", searchName);
    }

    fclose(file);
}

void deleteContact() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("No contacts found.\n");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (!tempFile) {
        printf("Error opening temp file!\n");
        fclose(file);
        return;
    }

    char deleteName[50];
    printf("Enter Name to Delete: ");
    fgets(deleteName, sizeof(deleteName), stdin);
    deleteName[strcspn(deleteName, "\n")] = 0;

    Contact contact;
    int deleted = 0;
    while (fread(&contact, sizeof(Contact), 1, file)) {
        if (strcasecmp(contact.name, deleteName) != 0) {
            fwrite(&contact, sizeof(Contact), 1, tempFile);
        } else {
            deleted = 1;
        }
    }

    fclose(file);
    fclose(tempFile);
    
    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (deleted) {
        printf("Contact deleted successfully!\n");
    } else {
        printf("No contact found with name: %s\n", deleteName);
    }
}

void clearBuffer() {
    while (getchar() != '\n');
}





