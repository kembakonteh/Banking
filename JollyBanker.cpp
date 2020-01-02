//
//  JollyBanker.cpp
//  Assignment6
//
//  Created by Kemba Konteh on 12/1/19.
//  Copyright © 2019 Kemba Konteh. All rights reserved.
//

#include "JollyBanker.hpp"


#include <sstream>
#include <fstream>
#include <queue>
using namespace std;
#include "BSTree.hpp"


void showq(queue <string> sq)
{
    queue <string> q = sq;
    while (!q.empty())
    {
        cout << "\n   " << q.front();
        q.pop();
    }
    cout << endl;
}


int main(int argc, char* argv[])
{
    /* check if there are enough command-line arguments */
    if( argc <= 1 )
    {
        cout << "ERROR - Please specify the name of the input file as a command-line argument!\n";
        return 1;
    }
    
    /* read in transactions from input file and store them in a queue */
    queue <string> transactions;
    string line;
    ifstream ipFile( argv[1] );
    while( getline(ipFile, line) )
        transactions.push(line);
    ipFile.close();
    //cout << "The transactions stored in the queue are as follows --";
    //showq(transactions);
    
    /* read from the queue and process transactions in order */
    BSTree *acctBST = new BSTree();
    while ( !transactions.empty() )
    {
        istringstream iss( transactions.front() );
        char transactionType;
        iss >> transactionType;
        switch( transactionType )
        {
            case 'O':
                string firstName, lastName;
                int acctNumber;
                iss >> lastName;
                iss >> firstName;
                iss >> acctNumber;
                if( acctNumber > 999 && acctNumber <= 9999 )
                {
                    Account *acct;
                    if( acctBST->Retrieve(acctNumber, acct) == true )
                        cout << "ERROR: Account " << acctNumber << " is already open. Transaction refused.\n";
                    else
                    {
                        acct = new Account(firstName, lastName, acctNumber);
                        acctBST->Insert(acct);
                    }
                }
                else
                    cout << "ERROR: Invalid account number" << endl;
                break;
            
            case 'D':
                int acctNumber, accType, amount;
                Account *acct;
                iss >> acctNumber;
                iss >> amount;
                accType = acctNumber % 10;
                acctNumber = acctNumber / 10;
                if( acctNumber > 999 && acctNumber <= 9999 )
                {
                    if( acctBST->Retrieve(acctNumber, acct) == false )
                        cout << "ERROR: Account " << acctNumber << " not found. Deposit refused.\n";
                    else
                    {
                        acct->deposit(accType, amount);
                        acct->appendHistory(accType, transactions.front());
                    }
                }
                else
                    cout << "ERROR: Invalid account number" << endl;
                break;
                
            case 'W':
                int acctNumber, accType, amount;
                Account *acct;
                iss >> acctNumber;
                iss >> amount;
                accType = acctNumber % 10;
                acctNumber = acctNumber / 10;
                if( acctNumber > 999 && acctNumber <= 9999 )
                {
                    if( acctBST->Retrieve(acctNumber, acct) == false )
                        cout << "ERROR: Account " << acctNumber << " not found. Withdrawal refused.\n";
                    else
                    {
                        int balance = acct->getBalance(accType);
                        if( balance >= amount)
                        {
                            acct->withdraw(accType, amount);
                            acct->appendHistory(accType, transactions.front());
                        }
                        else
                        {
                            cout << "ERROR: Not enough funds to withdraw " << amount << " from ";
                            cout << acct->getFullName() << " " << Account::fundName[accType] << endl;
                            acct->appendHistory(accType, transactions.front()+" (Failed)");
                        }
                    }
                }
                else
                    cout << "ERROR: Invalid account number" << endl;
                break;
                
            case 'T':
                int acctNumber1, accType1, acctNumber2, accType2, amount;
                Account *acct1, *acct2;
                iss >> acctNumber1;
                accType1 = acctNumber1 % 10;
                acctNumber1 = acctNumber1 / 10;
                iss >> amount;
                iss >> acctNumber2;
                accType2 = acctNumber2 % 10;
                acctNumber2 = acctNumber2 / 10;
                if( acctNumber1 > 999 && acctNumber1 <= 9999 && acctNumber2 > 999 && acctNumber2 <= 9999 )
                {
                    if( acctBST->Retrieve(acctNumber1, acct1) == false )
                        cout << "ERROR: Account " << acctNumber1 << " not found. Transferal refused.\n";
                    else if( acctBST->Retrieve(acctNumber2, acct2) == false )
                        cout << "ERROR: Account " << acctNumber2 << " not found. Transferal refused.\n";
                    else
                    {
                        int balance = acct1->getBalance(accType1);
                        if( balance >= amount)
                        {
                            acct1->withdraw(accType1, amount);
                            acct1->appendHistory(accType1, transactions.front());
                            acct2->deposit(accType2, amount);
                            acct2->appendHistory(accType2, transactions.front());
                        }
                        else
                        {
                            cout << "ERROR: Not enough funds to transfer " << amount << " from ";
                            cout << acct1->getFullName() << " " << Account::fundName[accType1] << endl;
                            acct1->appendHistory(accType1, transactions.front()+" (Failed)");
                            acct2->appendHistory(accType2, transactions.front()+" (Failed)");
                        }
                    }
                }
                else
                    cout << "ERROR: Invalid account number" << endl;
                break;
            
            case 'H':
                int acctNumber;
                Account *acct;
                iss >> acctNumber;
                if( acctNumber > 999 && acctNumber <= 9999 )
                {
                    if( acctBST->Retrieve(acctNumber, acct) == false )
                        cout << "ERROR: Account " << acctNumber << " not found. Unable to display history.\n";
                    else
                    {
                        cout << "Transaction History for " << acct->getFullName() << " by fund." << endl;
                        for(int i = 0; i < 10; i++)
                        {
                            cout << Account::fundName[i] << ": $" << acct->getBalance(i) << endl;
                            cout << acct->getHistory(i);
                        }
                    }
                }
                else if( acctNumber > 9999 && acctNumber <= 99999 )
                {
                    int accType = acctNumber % 10;
                    acctNumber = acctNumber / 10;
                    if( acctBST->Retrieve(acctNumber, acct) == false )
                        cout << "ERROR: Account " << acctNumber << " not found. Unable to display history.\n";
                    else
                    {
                        cout << "Transaction History for " << acct->getFullName() << " ";
                        cout << Account::fundName[accType] << ": $" << acct->getBalance(accType) << endl;
                        cout << acct->getHistory(accType);
                    }
                }
                else
                    cout << "ERROR: Invalid account number" << endl;
                break;
                    
            default:
                cout << "ERROR: Invalid transaction type" << endl;
        }
        transactions.pop();
    }
            
    /* print out all open accounts and balances in those accounts */
    cout << "\nProcessing Done. Final Balances";
    acctBST->Display();

    return 0;
}
