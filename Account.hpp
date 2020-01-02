//
//  Account.hpp
//  Assignment6
//
//  Created by Kemba Konteh on 12/1/19.
//  Copyright © 2019 Kemba Konteh. All rights reserved.
//

#ifndef Account_hpp
#define Account_hpp

#include <stdio.h>

#include "Account.hpp"

string Account::fundName[10] = { "Money Market", "Prime Money Market",
                                 "Long-Term Bond", "Short-Term Bond",
                                 "500 Index Fund", "Capital Value Fund",
                                 "Growth Equity Fund", "Growth Index Fund",
                                 "Value Fund", "Value Stock Index" };


// constructor for Account class, which requires a name and an account number as parameters
Account::Account(string firstName, string lastName, int acctNumber)
{
    this->fName = firstName;
    this->lName = lastName;
    this->number = acctNumber;
    for(int i = 0; i < 10; i++)
    {
        balance[i] = 0;
        history[i] = "";
    }
}
        
        
// accessor methods
int Account::getNumber()
{
    return this->number;
}

string Account::getFullName()
{
    return (this->fName + " " + this->lName);
}

int Account::getBalance(int accType)
{
    return this->balance[accType];
}

string Account::getHistory(int accType)
{
    return this->history[accType];
}


// method to append a new transaction to history
void Account::appendHistory(int accType, string transaction)
{
    this->history[accType] += "  ";
    this->history[accType] += transaction;
    this->history[accType] += "\n";
}
        
        
// method to implement deposit
void Account::deposit(int accType, int amount)
{
    this->balance[accType] += amount;
}
        

// method to implement withdrawal
void Account::withdraw(int accType, int amount)
{
    this->balance[accType] -= amount;
}


// display all the account details to cout
void Account::display()
{
    cout << "\n" << getFullName() << " Account ID: " << number;
    for(int i = 0; i < 10; i++)
        cout << "\n    " << fundName[i] << ": $" << balance[i];
    cout << endl;
}

#endif /* Account_hpp */
