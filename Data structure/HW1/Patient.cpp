/*
 * Patient.cpp
 *
 * Class Description: Models a walk-in clinic patient.
 * Class Invariant: Each patient has a unique care card number.
 *                  This care card number must have 10 digits.
 *                  This care card number cannot be modified.
 *
 * Author: (For you to fill)
 * Date: (For you to fill)
 */

// You can add #include statements if you wish.
#include "Patient.h"

// Default Constructor
// Description: Create a patient with a care card number of "0000000000".
// Postcondition: All data members set to "To be entered",
//                except the care card number which is set to "0000000000".
Patient::Patient()
{
    this->CareCard = "0000000000";
    this->Email = "To Be entered";
    this->Phone = "To Be entered";
    this->Name = "To Be entered";
    this->Address = "To Be entered";

    this->next = NULL;
}

// Parameterized Constructor
// Description: Create a patient with the given care card number.
// Postcondition: If aCareCard does not have 10 digits, then care card is set to "0000000000".
//                All other data members set to "To be entered".
Patient::Patient(string aCareCard)
{
    if (aCareCard.size() > 10 || aCareCard.size() < 10)
        CareCard = "0000000000";

    else
        this->CareCard = aCareCard;

    next = NULL;
}

// All other parameterized constructors -> You need to implement these methods.
Patient::Patient(const Patient &Sample)
{
    this->CareCard = Sample.CareCard;
    this->Phone = Sample.Phone;
    this->Address = Sample.Address;
    this->Name = Sample.Name;
    this->Email = Sample.Email;

    this->next = NULL;
}

Patient::Patient(string aCareCard, string aname)
{
    if (aCareCard.size() > 10 || aCareCard.size() < 10)
        CareCard = "0000000000";

    else
        this->CareCard = aCareCard;

    this->Name = aname;

    this->Email = "To Be entered";
    this->Phone = "To Be entered";
    this->Address = "To Be entered";

    this->next = NULL;
}

Patient::Patient(string aCareCard, string aname, string anaddress)
{
    if (aCareCard.size() > 10 || aCareCard.size() < 10)
        CareCard = "0000000000";

    else
        this->CareCard = aCareCard;

    this->Name = aname;
    this->Address = anaddress;

    this->Email = "To Be entered";
    this->Phone = "To Be entered";

    this->next = NULL;
}

Patient::Patient(string aCareCard, string aname, string anaddress, string aphone)
{
    if (aCareCard.size() > 10 || aCareCard.size() < 10)
        CareCard = "0000000000";

    else
        this->CareCard = aCareCard;

    this->Name = aname;
    this->Address = anaddress;
    this->Phone = aphone;

    this->Email = "To Be entered";

    this->next = NULL;
}

Patient::Patient(string aName, string anAddress, string aPhone, string anEmail, string aCareCard)
{
    if (aCareCard.size() > 10 || aCareCard.size() < 10)
        CareCard = "0000000000";

    else
        this->CareCard = aCareCard;

    Name = aName;
    Address = anAddress;
    Phone = aPhone;
    Email = anEmail;

    next = NULL;
}

// Overloaded Operators
// Description: Comparison operator. Compares "this" Patient object with "rhs" Patient object.
//              Returns true if both Patient objects have the same care card number.
bool Patient::operator==(const Patient &rhs) { return this->CareCard == rhs.getCareCard(); }

// Description: Greater than operator. Compares "this" Patient object with "rhs" Patient object.
//              Returns true if the care card number of "this" Patient object is > the care card
//              number of "rhs" Patient object
bool Patient::operator>(const Patient &rhs) { return this->CareCard > rhs.getCareCard(); }

// Description: Less than operator. Compares "this" Patient object with "rhs" Patient object.
//              Returns true if the care card number of "this" Patient object is < the care card
//              number of "rhs" Patient object.
bool Patient::operator<(const Patient &rhs) { return this->CareCard < rhs.getCareCard(); }

// For testing purposes!
// Description: Prints the content of "this".
ostream &operator<<(ostream &os, const Patient &p)
{

    os << p.CareCard << " - Patient: " << p.Name << ", "
       << p.Address << ", " << p.Phone << ", " << p.Email << endl;

    return os;
}
// end of Patient.cpp