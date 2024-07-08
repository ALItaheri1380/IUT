/*
 * Patient.h
 *
 * Class Description: Models a walk-in clinic patient.
 * Class Invariant: Each patient has a unique care card number.
 *                  This care card number must have 10 digits.
 *                  This care card number cannot be modified.
 *
 * Author: (Ali Taheri) => 40012323
 * Author: (AmirHossein Zendevani) => 40009973
 * Date: (1401/09/23)
 */

#pragma once

// You can add #include statements if you wish.
#include <string>
#include <iostream>

using namespace std;

class Patient
{

private:
	// For you to fill: There are plenty of hints in the provided files to help you complete this section.

	string Name, Address, Phone, Email, CareCard;
	Patient *next;

public:
	// Default Constructor
	// Description: Create a patient with a care card number of "0000000000".
	// Postcondition: All data members set to "To be entered",
	//                except the care card number which is set to "0000000000".
	Patient();

	// Parameterized Constructor
	// Description: Create a patient with the given care card number.
	// Postcondition: If aCareCard does not have 10 digits, then care card is set to "0000000000".
	//                All other data members set to "To be entered".
	Patient(string aCareCard);

	// Add more parameterized constructors here!
	Patient(const Patient &Sample);
	Patient(string aCareCard, string name);
	Patient(string aCareCard, string name, string address);
	Patient(string aCareCard, string name, string address, string phone);
	Patient(string aName, string anAddress, string aPhone, string anEmail, string aCareCard);

	// Getters and setters

	// Description: Returns patient's next address.
	Patient *get_next() { return next; }

	// Description: Returns patient's name.
	string getName() const { return this->Name; }

	// Description: Returns patient's address.
	string getAddress() const { return this->Address; }

	// Description: Returns patient's phone.
	string getPhone() const { return this->Phone; }

	// Description: Returns patient's email.
	string getEmail() const { return this->Email; }

	// Description: Returns patient's care card.
	string getCareCard() const { return this->CareCard; }

	// Description: Sets the patient's name.
	void setName(const string aName) { this->Name = aName; }

	// Description: Sets the patient's next address.
	void set_next(Patient *node) { next = node; }

	// Description: Sets the patient's address.
	void setAddress(const string anAddress) { this->Address = anAddress; }

	// Description: Sets the patient's phone.
	void setPhone(const string aPhone) { this->Phone = aPhone; }

	// Description: Sets the patient's email.
	void setEmail(const string anEmail) { this->Email = anEmail; }

	// Overloaded Operators

	// Description: Comparison operator. Compares "this" Patient object with "rhs" Patient object.
	//              Returns true if both Patient objects have the same care card number.
	bool operator==(const Patient &rhs);

	// Description: Greater than operator. Compares "this" Patient object with "rhs" Patient object.
	//              Returns true if the care card number of "this" Patient object is > the care card
	//              number of "rhs" Patient object.
	bool operator>(const Patient &rhs);

	// Description: Less than operator. Compares "this" Patient object with "rhs" Patient object.
	//              Returns true if the care card number of "this" Patient object is < the care card
	//              number of "rhs" Patient object.
	bool operator<(const Patient &rhs);

	// For testing purposes!
	// Description: Prints the content of "this".
	friend ostream &operator<<(ostream &os, const Patient &p);
};

// end of Patient.h