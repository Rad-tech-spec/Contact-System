#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
// +-------------------------------------------------+
// | NOTE:  Include additional header files...       |
// +-------------------------------------------------+
#include "contactHelpers.h"
#include "contacts.h"


// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        source code below...                     |
// +-------------------------------------------------+

// getName:
void getName(struct Name *name)
{
    char option;

    printf("Please enter the contact's first name: ");
    scanf("%30[^\n]", name->firstName);
	clearKeyboard();

    printf("Do you want to enter a middle initial(s)? (y or n): ");
    option = yes();
    if(option)
    {
        printf("Please enter the contact's middle initial(s): ");
        scanf("%6[^\n]", name->middleInitial);
        clearKeyboard();
    }
    else{
	strcpy(name->middleInitial, "\0");
	}

    printf("Please enter the contact's last name: ");
    scanf("%35[^\n]", name->lastName);
	clearKeyboard();
}

// getAddress:
void getAddress(struct Address *address)
{
    char option;
    int temp;
    printf("Please enter the contact's street number: ");
    temp = getInt();
    while (temp < 0 )
    {
        printf("*** INVALID STREET NUMBER *** <must be a positive number>: ");
        temp = getInt();
    }
    address->streetNumber = temp;

    printf("Please enter the contact's street name: ");
    scanf("%40[^\n]", address->street);
	clearKeyboard();
    

    printf("Do you want to enter an apartment number? (y or n): ");
    option = yes();
    if(option)
    {
        printf("Please enter the contact's apartment number: ");
        
        temp = getInt();
        while(temp < 0){
            printf("*** INVALID APARTMENT NUMBER *** <must be a positive number>: ");
            temp = getInt();
        }
        address->apartmentNumber = temp;
    }
    
    printf("Please enter the contact's postal code: ");
    scanf("%7[^\n]", address->postalCode);
	clearKeyboard();
    
    
    
    printf("Please enter the contact's city: ");
    scanf("%40[^\n]", address->city);
    clearKeyboard();
}

// getNumbers:
void getNumbers(struct Numbers *numbers)
{
    char option; 

    printf("Please enter the contact's cell phone number: ");
    getTenDigitPhone(numbers->cell);
    
    printf("Do you want to enter a home phone number? (y or n): ");
    option = yes();
    if (option == 1)
    {
        printf("Please enter the contact's home phone number: ");
        getTenDigitPhone(numbers->home);
    } 
    else{
	strcpy(numbers->home, "\0");
	}

    printf("Do you want to enter a business phone number? (y or n): ");
    option = yes();
    if (option == 1)
    {
        printf("Please enter the contact's business phone number: ");
        getTenDigitPhone(numbers->business);
    } 
    else{
	strcpy(numbers->business, "\0"); 
	}
}
// getContact:
void getContact(struct Contact *contact){

    getName(&contact->name);
    getAddress(&contact->address);
    getNumbers(&contact->numbers);
}
