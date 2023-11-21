#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 50
#define PHONE_NUMBER_LENGTH 15

struct PhoneDirectoryEntry {
    char name[MAX_NAME_LENGTH];
    char phoneNumber[PHONE_NUMBER_LENGTH];
    struct PhoneDirectoryEntry* next;
};

struct PhoneDirectoryEntry* head = NULL;

struct PhoneDirectoryEntry* createEntry(char* name, char* phoneNumber) {
    struct PhoneDirectoryEntry* newEntry = (struct PhoneDirectoryEntry*)malloc(sizeof(struct PhoneDirectoryEntry));
    if (newEntry != NULL) {
        strcpy(newEntry->name, name);
        strcpy(newEntry->phoneNumber, phoneNumber);
        newEntry->next = NULL;
    }
    return newEntry;
}

void addEntry(char* name, char* phoneNumber) {
    if (strlen(phoneNumber) != 10) {
        printf("Invalid phone number. Please enter a 10-digit mobile number.\n");
        return;
    }

    struct PhoneDirectoryEntry* newEntry = createEntry(name, phoneNumber);
    if (newEntry == NULL) {
        printf("Memory allocation failed. Unable to add entry.\n");
        return;
    }

    if (head == NULL) {
        head = newEntry;
    } else {
        struct PhoneDirectoryEntry* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newEntry;
    }
}

void deleteEntry(char* phoneNumber) {
    struct PhoneDirectoryEntry* current = head;
    struct PhoneDirectoryEntry* prev = NULL;

    while (current != NULL && strcmp(current->phoneNumber, phoneNumber) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Phone number not found.\n");
        return;
    }

    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
}

struct PhoneDirectoryEntry* searchEntry(char* phoneNumber) {
    struct PhoneDirectoryEntry* current = head;
    while (current != NULL) {
        if (strcmp(current->phoneNumber, phoneNumber) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void displayPhoneDirectory() {
    struct PhoneDirectoryEntry* current = head;
    printf("Phone Directory:\n");
    while (current != NULL) {
        printf("Name: %s, Phone Number: %s\n", current->name, current->phoneNumber);
        current = current->next;
    }
}

void freePhoneDirectory() {
    struct PhoneDirectoryEntry* current = head;
    while (current != NULL) {
        struct PhoneDirectoryEntry* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}

int main() {
    char choice;
    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Add a phone number\n");
        printf("2. Remove a phone number\n");
        printf("3. Search for a phone number\n");
        printf("4. Display phone directory\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1': {
                char name[MAX_NAME_LENGTH];
                char phoneNumber[PHONE_NUMBER_LENGTH];
                printf("Enter name: ");
                scanf(" %s", name);
                printf("Enter a 10-digit phone number: ");
                scanf(" %s", phoneNumber);

                if (strlen(phoneNumber) != 10) {
                    printf("Invalid phone number. Please enter a 10-digit mobile number.\n");
                    break;
                }

                addEntry(name, phoneNumber);
                break;
            }

            case '2': {
                char phoneNumber[PHONE_NUMBER_LENGTH];
                printf("Enter the phone number to remove: ");
                scanf(" %s", phoneNumber);
                deleteEntry(phoneNumber);
                break;
            }

            case '3': {
                char phoneNumber[PHONE_NUMBER_LENGTH];
                printf("Enter the phone number to search for: ");
                scanf(" %s", phoneNumber);
                struct PhoneDirectoryEntry* entry = searchEntry(phoneNumber);
                if (entry) {
                    printf("Name: %s, Phone Number: %s\n", entry->name, entry->phoneNumber);
                } else {
                    printf("Phone number not found.\n");
                }
                break;
            }

            case '4':
                displayPhoneDirectory();
                break;

            case '5':
                freePhoneDirectory();
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
