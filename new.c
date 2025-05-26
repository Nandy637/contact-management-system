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






//#include <stdio.h>
// Function to display the menu
/*void displayMenu() {
 printf("\nMenu:\n");
 printf("1. Addition\n");
 printf("2. Subtraction\n");
 printf("3. Multiplication\n");
 printf("4. Division\n");
 printf("5. Exit\n");
 printf("Enter your choice: ");
}
int main() {
 int choice;
 float num1, num2, result;
 // Infinite loop to allow repeated menu access
 while (1) {
 displayMenu();
 scanf("%d", &choice); // Read user's menu choice
 // Exit condition
 if (choice == 5) {
 printf("Exiting the program. Goodbye!\n");
 break;
 }
 // Prompt for two numbers
 printf("Enter two numbers: ");
 scanf("%f %f", &num1, &num2);
 // Perform operations based on the user's choice
 switch (choice) {
 case 1:
 result = num1 + num2;
 printf("Result (Addition): %.2f\n", result);
 break;
 case 2:
 result = num1 - num2;
 printf("Result (Subtraction): %.2f\n", result);
 break;
 case 3:
 result = num1 * num2;
 printf("Result (Multiplication): %.2f\n", result);
 break;
case 4:
 // Division operation with /0 handling
 if (num2 == 0) {
 printf("Error: Division by zero is not allowed.\n");
 } else {
 result = num1 / num2;
 printf("Result (Division): %.2f\n", result);
 }
 break;
 default:
 printf("Invalid choice. Please try again.\n");
 }
 }
 return 0;
}


void main ()
{}
1. if-else
2. switch-case
3. Nested if-else
4. Ternary operator (? :)*/
/*
#include <stdio.h>
void main()
{
    int a,b;
    printf("enter a and b");
    scanf("%d%d",&a,&b);
    if (a>b)
    {
        printf("a>b");
    }
    else
    {
        printf("b>a");
    }
   int ch;
   int a,b,c;
   scanf("%d",&ch);
   switch (ch)
   {
    case 1:
    printf("option 1 add");
    scanf("%d%d",&a,&b);
    c=a+b;
    printf("the sum is %d",c);
    break;
    
    case 2:
    printf("option 2 sub");
    int a,b,c;
    scanf("%d%d",&a,&b);
    c=a-b;
    printf("the sub is %d",c);
    break;

    case 3:
    printf("option 2 mul");
    scanf("%d%d",&a,&b);
    c=a*b;
    printf("the mul is %d",c);
    break;
    
    case 4:
    printf("option 2 quo, rem");
   
    float d;
    scanf("%d%d",&a,&b);
    c=a%b;
    d=a/b;
    printf("the quo is %d",d);
    printf("the rem is %d",c);
    break;

    
    default:
    printf("invalid responce");
    
   }
}


#include<stdio.h>
void main()
{
    int a=10, b=20;
    int max=(a>b)?a:b;
    printf("maxim is %d",max);
}


#include<stdio.h>
void main()
{
    int a;
    printf("enter a");
    scanf("%d",&a);
    if(a>=0)
    {
        printf("the dig is + ");
        if(a<10)
        {
            printf("a single dig");
        }
        else
        {
            if(a<100)
            {
                printf("has 2 dig");
                }
            else 
            {
                printf("has more than 2 dig");
            }
        }
    }
    else
    {
        printf("is negative");

    }
}

#include<stdio.h>
int main(){
    int i,j;
    for (i=1;i<5;i++)
        for (j=1;j<i;j++)
            printf("%d \n",j);

    return 0;
}

#include<stdio.h>

int main()
{
    //let's assume the maximum array size as 100.
    //initialize sum as 0. Otherwise, it will take some garbage value.
    int arr[100], size, i, sum = 0;
    
    //Get size input from user
    printf("Enter array size\n");
    scanf("%d",&size);
    
    //Get all elements using for loop and store it in array
    for(i = 0; i < size; i++)
        {  
            arr[i]=i+1;
        } 
    //add all elements to the variable sum.
    for(i = 0; i < size; i++)
        {sum = sum + arr[i]; // same as sum += arr[i];
    
    //print the result
    printf("Sum of the array = %d\n",sum);
    
    return 0;
}
    */