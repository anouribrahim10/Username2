//Anour Ibrahim
//aibrahim23
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Name.h"
#include "ID.h"
#include "Final.h"
#include "FinalWithNumber.h"

using namespace std;

int main()
{
    vector<Final*> names; //vector to store the date
    
    //It stores a collection of key-value pairs where each key is unique
    unordered_map<string, int> uCount;
    
    //asks the user for the amount of stundents they want to enter
    int count;
    cout << "How many students do you want to enter? (Enter at least 1): ";
    cin >> count;
    cin.ignore(); 
    
    //the user enters the name names of the students
    cout << "Enter the name of the students (lastname, firstname):" << endl;
    
    for (int i = 0; i < count; i++) 
    {
        string line;
        cout << "Enter name " << (i + 1) << ": ";
        getline(cin, line);
        Name n(line); //creates a n object

        Final* x = nullptr;
        //constructs the username
        string username = n.getFirstName().substr(0, 1) + n.getLastName();
        //it used to find if a username alredy exists
        if (uCount.find(username) != uCount.end()) 
        {
            //calls the derived class when a username is similar
            x = new FinalWithNumber(n); 
        } 
        else 
        {
            //calls the parent class if the the usernames are unique
            x = new Final(n);
        }
        names.emplace_back(x); //x pointer to names, growing dynamically
        uCount[username]++;
    }
    
    //opens the file and the content of the vector is read into the file
    ofstream outputFile("data.txt");
    if (outputFile.is_open()) 
    {
        for (const auto y : names) 
        {
            outputFile << *y << "\n";
        }
        outputFile.close();
    } 
    else 
    {
        //cerr is an output stream in C++ that is used for error messages.
        cerr << "File is not opening." << endl;
        for (const auto y : names) 
        {
            delete y;
        }
        return 1;
    }

    //reads from the file
    ifstream inputFile("data.txt");
    if (inputFile.is_open()) 
    {
        cout << "Here is the list of students you entered:\n";

        Final obj;
        while (inputFile >> obj) 
        {
            cout << obj << "\n";
        }
        inputFile.close();
    } 
    else 
    {
        //cerr is an output stream in C++ that is used for error messages.
        cerr << "File can not be read." << endl;
        for (const auto y : names) 
        {
            delete y;
        }
        return 1;
    }
    
    //the info gets outputted
    cout<<endl;
    cout << "Name" << "\t\t\t" << "ID" << "\t\t\t" << "Username" << endl;
    cout<<endl;
    for (auto y : names) 
    {
        //points to the member functions
        cout << y->getName().getFirstName() <<" "<< y->getName().getLastName();
        cout << "\t\t" << "ID: " << y->getID().getId() << "\t\t";
        y->printUsername();
        cout << endl;
    }
    
    //delocates the memory
    for (const auto y : names) 
    {
        delete y;
    }

    return 0;
}
