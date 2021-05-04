#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// This source file needs to "know about" the SYSTEM string library functions.
#include <string.h>
// -------------------------------
//ContactHelpers header file on the next line:
#include "contactHelpers.h"
// -------------------------------
// define MAXCONTACTS for sizing contacts array (5):
#define MAXCONTACTS 5
 
//--------------------------------
// Function Definitions
//--------------------------------

// clearKeyboard
void clearKeyboard(void)
{
    while (getchar() != '\n')   ; // empty execution code block on purpose
}


// pause:
void pause(void)
{
    printf("(Press Enter to Continue)");
    clearKeyboard();
}

// getInt:
int getInt(void)
{
    int value;
    char NL = 'x';

    while( NL != '\n'){

        scanf("%d%c", &value, &NL);
        
        if (NL != '\n')
        {
        clearKeyboard();
        printf("*** INVALID INTEGER *** <Please enter an integer>: ");
        }
    } 
 return value;
}

// getIntInRange:
int getIntInRange(int min, int max)
{
    int range , rangecheck = 0; 

    while (rangecheck == 0)
    {
        range = getInt();

        if(range < min || range > max )
        {
            printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
        }
        else {
            rangecheck = 1;
        }

    }
    return range;
}

// yes:
int yes(void)
{
    char NL = 'x';
    char confirm = 'x';
    int yes;

    while (NL != '\n')
    {

        scanf("%c%c", &confirm, &NL);
        if(NL != '\n')
        {
            clearKeyboard();
            printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
        }
        else if (confirm == 'y' || confirm == 'Y')
        {
            yes = 1;
        }
        else if (confirm == 'n' || confirm == 'N')
        {
            yes = 0;
        }
        else
        {
            NL = 'x';
        }  
    }
 return yes;
}
// menu:
int menu(void)
{
    int choice = 0;

	printf("Contact Management System\n");
	printf("-------------------------\n");
	printf("1. Display contacts\n");
	printf("2. Add a contact\n");
	printf("3. Update a contact\n");
	printf("4. Delete a contact\n");
	printf("5. Search contacts by cell phone number\n");
	printf("6. Sort contacts by cell phone number\n");
	printf("0. Exit\n");
	printf("\n");
	printf("Select an option:> ");

	choice = getIntInRange(0, 6);

	return choice;
}

// contactManagerSystem:
void contactManagerSystem(void)
{
    int option;
    int done = 0;

    struct Contact contacts[MAXCONTACTS] = {
		{
			{ "Rick",{ '\0' }, "Grimes" },
			{ 11, "Trailer Park", 0, "A7A 2J2", "King City" },
			{ "4161112222", "4162223333", "4163334444" } },
			{
				{ "Maggie", "R.", "Greene" },
				{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
				{ "9051112222", "9052223333", "9053334444" } },
				{
					{ "Morgan", "A.", "Jones" },
					{ 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
					{ "7051112222", "7052223333", "7053334444" } },
					{
						{ "Sasha",{ '\0' }, "Williams" },
						{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
						{ "9052223333", "9052223333", "9054445555" } },
	};
    
    while ( done == 0)
    {
        option = menu();
        printf("\n");

        switch(option){

            case 1: 
                displayContacts (contacts, MAXCONTACTS);
		pause();
		break;
		printf("\n");

            case 2:
                addContact(contacts, MAXCONTACTS);
		pause();
		break;
		printf("\n");

            case 3:
                updateContact(contacts, MAXCONTACTS);
		pause();
		break;
		printf("\n");

            case 4:
                deleteContact(contacts, MAXCONTACTS);
		pause();	
		break;
		printf("\n");

            case 5:
                searchContacts(contacts, MAXCONTACTS);
		pause();	
		break;
		printf("\n");

            case 6:
                
		sortContacts(contacts, MAXCONTACTS);
		pause();
		break;
		printf("\n");
            case 0:
            printf("Exit the program? (Y)es/(N)o: ");
            done = yes();
            break;

            default :
            break;
            
        }

     printf("\n");

    }
 printf("Contact Management System: terminated\n");   
}

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        empty function definitions below...      |
// +-------------------------------------------------+

// getTenDigitPhone:
void getTenDigitPhone(char telNum[])
{
    int needInput = 1;

    while (needInput == 1) {
        scanf("%10[0-9]", telNum);
        clearKeyboard();

        // (String Length Function: validate entry of 10 characters)
        if (strlen(telNum) == 10)
          needInput = 0;
        else
            printf("Enter a 10-digit phone number: ");
    }
}

// findContactIndex:
int findContactIndex(const struct Contact contacts[], int size, const char cellNum[])
{
    int j;
	int i = 0;
	int index = -1;
	do {
		j = strcmp(contacts[i].numbers.cell, cellNum);
		if (j == 0) {
			index = i;
		}
		i++;
	} while (i < size);

	return index;
}

// displayContactHeader
void displayContactHeader(void){
	printf("+-----------------------------------------------------------------------------+\n");
	printf("|                              Contacts Listing                               |\n");
	printf("+-----------------------------------------------------------------------------+\n");
}

// displayContactFooter
void displayContactFooter(int count){
    printf("+-----------------------------------------------------------------------------+\n");
	printf("Total contacts: %d\n\n", count);
}

// displayContact:
void displayContact(const struct Contact *contact){
    if (strcmp((*contact).name.middleInitial, "") == 0)
    {
		printf(" %s %s\n", (*contact).name.firstName, (*contact).name.lastName);
    }else
    {
		printf(" %s %s %s\n", (*contact).name.firstName, (*contact).name.middleInitial, (*contact).name.lastName);
    }
	printf("    C: %-10s   H: %-10s   B: %-10s\n", (*contact).numbers.cell, (*contact).numbers.home, (*contact).numbers.business);

	if ((*contact).address.apartmentNumber > 0)
		printf("       %d %s, Apt# %d, %s, %s\n", (*contact).address.streetNumber, (*contact).address.street, (*contact).address.apartmentNumber, (*contact).address.city, (*contact).address.postalCode);
	else
		printf("       %d %s, %s, %s\n", (*contact).address.streetNumber, (*contact).address.street, (*contact).address.city, (*contact).address.postalCode);

}

// displayContacts:
void displayContacts(const struct Contact contacts[], int size){
    int i = 0, j = 0;
	int lenght;
	displayContactHeader();

	for (i = 0; i < size; i++) {
		lenght = strlen(contacts[i].numbers.cell);
		if (lenght > 0) {
			displayContact(&(contacts[i]));
			j++;
		}
	}displayContactFooter(j);
}

// searchContacts:
void searchContacts(const struct Contact contacts[], int size){
int i;
	char cellNum[11];

	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(cellNum);
		
	
	i = findContactIndex(contacts, size, cellNum);

	if (i >= 0 && i < size) {
		printf("\n");
		displayContact(&(contacts[i]));
	}
	else printf("*** Contact NOT FOUND ***\n");
	printf("\n");
	
}

// addContact:
void addContact(struct Contact contacts[], int size){
int i, available = -1;

	for (i = 0; i<size; i++)
	{
		if (strlen(contacts[i].numbers.cell) == 0)
		{
			available = i;
			break;
		}
	}
	if (available > -1)
	{
		getContact(&contacts[available]);
		printf("--- New contact added! ---\n");
		printf("\n");
		
	}
	else
	{
		printf("*** ERROR: The contact list is full! ***\n");
		printf("\n");
		
	}
}



// updateContact:
void updateContact(struct Contact contacts[], int size){
int myIndex;
	char cellNum[11];

	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(cellNum);

	myIndex = findContactIndex(contacts, size, cellNum);
	if (myIndex == -1) {
		printf("*** Contact NOT FOUND ***\n");
		printf("\n");
		
	}
	else {
		printf("\nContact found:\n");
		displayContact(&(contacts[myIndex]));
		printf("\n");

		printf("Do you want to update the name? (y or n): ");
		if (yes() == 1) {
			getName(&(contacts[myIndex].name));
		}
		printf("Do you want to update the address? (y or n): ");
		if (yes() == 1) {
			getAddress(&(contacts[myIndex].address));
		}
		printf("Do you want to update the numbers? (y or n): ");
		if (yes() == 1) {
			getNumbers(&(contacts[myIndex].numbers));
		}
		printf("--- Contact Updated! ---\n");
		printf("\n");
		
	}
}

// deleteContact:
void deleteContact(struct Contact contacts[], int size){
int myIndex;
	char cellNum[11];
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(cellNum);
	//searchContacts(contact, size, cellNum);
	myIndex = findContactIndex(contacts, size, cellNum);

	if (myIndex == -1) {
		printf("*** Contact NOT FOUND ***\n");
		printf("\n");
		
	}
	else printf("\nContact found:\n");
	displayContact(&(contacts[myIndex]));
	printf("\n");
	printf("CONFIRM: Delete this contact? (y or n): ");
		
	if (yes() == 1) {
		strcpy(contacts[myIndex].numbers.cell, "\0");
		printf("--- Contact deleted! ---\n");
		
		
	}
	printf("\n");
}

// sortContacts:
void sortContacts(struct Contact contacts[], int size)
{
int i, j;
    struct Contact temp;
    
    for (i = size - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (strcmp(contacts[j].numbers.cell, contacts[j+1].numbers.cell) > 0) {
                temp = contacts[j];
                contacts[j] = contacts[j+1];
                contacts[j+1] = temp;
            }
        }
    
  }
 printf("--- Contacts sorted! ---\n\n");
}
