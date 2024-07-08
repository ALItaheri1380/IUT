#include <iostream>
#include "List.h"

List::List()
{
    first = new Patient;
    this->first = NULL;
    elementCount = 0;
    capacity = MAX_SIZE;
}

int List::getElementCount() const { return elementCount; }

Patient *List::Creat_patient(string name, string address, string email, string carecode, string phone)
{
    Patient *copyNode = new Patient(carecode);

    copyNode->setPhone(phone);
    copyNode->setEmail(email);
    copyNode->setAddress(address);
    copyNode->setName(name);

    return copyNode;
}

bool List::insert(const Patient &newElement)
{
    bool check = false;
    if (elementCount >= capacity)
    {
        cout << "We do not have the capacity !!! " << endl;
        return check;
    }

    if (search(newElement) != NULL)
    {
        cout << "We have repeated element !!! " << endl;
        return check;
    }

    else
    {
        // copy node

        Patient *copypatient = Creat_patient(newElement.getName(),
                                             newElement.getAddress(),
                                             newElement.getEmail(),
                                             newElement.getCareCard(),
                                             newElement.getPhone());
        if (!first)
        {
            first = copypatient;
            check = true;
        }

        else if (copypatient->getCareCard() > first->getCareCard())
        {
            copypatient->set_next(first);
            first = copypatient;
            check = true;
        }

        else
        {
            Patient *current = first;
            Patient *previous = new Patient();

            for (int i = 0; i < elementCount; i++)
            {
                previous = current;
                current = current->get_next();

                if (!current)
                {
                    copypatient->set_next(current);
                    previous->set_next(copypatient);
                    check = true;
                    break;
                }

                else
                {
                    if (copypatient->getCareCard() > current->getCareCard())
                    {
                        copypatient->set_next(current);
                        previous->set_next(copypatient);
                        check = true;
                        break;
                    }
                }
            }
        }
    }

    elementCount++;
    return check;
}

bool List::remove(const Patient &toBeRemoved)
{
    bool check = false;

    if (elementCount == 0)
    {
        cout << "The memory is empty !!!\n";
        return check;
    }

    else
    {

        Patient *current = first;
        Patient *previous = new Patient();

        if (*first == toBeRemoved)
        {
            Patient *temp = first;
            first = temp->get_next();
            delete temp;
            check = true;
        }

        else
        {
            for (int i = 0; i < elementCount; i++)
            {
                previous = current;
                current = current->get_next();

                if (*current == toBeRemoved)
                {
                    previous->set_next(current->get_next());

                    delete current;

                    check = true;
                    break;
                }
            }
        }
    }

    if (check)
        elementCount--;
    return check;
}

void List::removeAll()
{
    Patient *temp;

    for (int i = 0; i < elementCount; ++i)
    {
        temp = first;
        first = first->get_next();
        delete temp;
    }
    elementCount = 0;
}

Patient *List::search(const Patient &target)
{
    Patient *temp = first;

    for (int i = 0; i < elementCount; ++i)
    {
        if (*temp == target)
            return temp;
        temp = temp->get_next();
    }
    return NULL;
}

void List::printList()
{
    Patient *temp = first;

    for (int i = 0; i < elementCount; i++)
    {
        cout << *temp;
        temp = temp->get_next();
    }
}

void List::Edit(string aCareCard)
{
    Patient *temp = first;
    string check, newName, newAddress,
        newPhone, newEmail;

    for (int i = 0; i < elementCount; ++i)
    {
        if (temp->getCareCard() == aCareCard)
        {
            cout << "current patient :\n"
                 << "Carecode = " << aCareCard << "\nName = "
                 << temp->getName() << "\nAddress = " << temp->getAddress()
                 << "\nPhone = " << temp->getPhone() << "\nEmail = " << temp->getEmail()
                 << endl;

            cout << "do you want chenge ? (y/n)\n";
            cin >> check;
            if (check[0] == 'y' || check[0] == 'Y')
            {

                cout << "new Name is \n";
                cin >> newName;

                cout << "new Address is \n";
                cin >> newAddress;

                cout << "new Phone is\n";
                cin >> newPhone;

                cout << "new Email is  \n";
                cin >> newEmail;

                temp->setName(newName);
                temp->setAddress(newAddress);
                temp->setEmail(newEmail);
                temp->setPhone(newPhone);
            }

            else
            {
                cout << "Ok !!!!!\n";
            }
            break;
        }
        else
            temp = temp->get_next();
    }
}