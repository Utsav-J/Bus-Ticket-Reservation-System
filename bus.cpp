#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

//Header files used to separate interface and implementation
//header file named bus.h which is already created and programmed in the same location and its contents can be used by another cpp file
#include "bus.h"
#include "ticket.h"
#include "pnr.h"
#include "reservation.h"

using namespace std;

// ADD BUS
inline void Bus::addBus()
{
    fstream busFileStream;          //creates busFileStream instance of fstream class

    system("cls");
    //BUS DETAILS
    cout<<"\t\t\t\t\t\t\t\t\t\t\t\tAdd Bus"<<endl;

    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    cin.ignore();                   //clears input buffer
    cin.getline(busNo, 10);         //input taken
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
    cin.getline(source, 20);
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
    cin.getline(destination, 20);
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Fare:-> ";
    cin >> busFare;

    busFileStream.open("buses.txt", ios::out | ios::app | ios::binary);     // creates buses.txt file
    busFileStream.write((char *)this, sizeof(*this));                       // this pointer refers to object of bus, the contents stored in bus object is written to buses.txt by using this pointer till the size of pointer
    busFileStream.close();

    cout << "\n\t\t\t\t\t\t\t\t\t\tBus Added Successfully...!!!:-> \n";
}

// SHOW BUS DETAILS
inline void Bus::showBusDetails()
{
    cout << "\t\t\t\t\t\t\t\t\t\t Bus No:-> " << getBusNo();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Source:-> " << getSource();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Destination:-> " << getDestination();
    cout << fixed << setprecision(2);
    cout << "\n\t\t\t\t\t\t\t\t\t\t Bus Fare:-> " << getBusFare() << endl;
    cout << "\n";
}

// VIEW ALL BUSES INFORMATION
inline void Bus::showAllBus()
{
    system("cls");

    fstream busFileStream;

    busFileStream.open("buses.txt", ios::in | ios::app | ios::binary);  //uses buses.txt file
    if (!busFileStream)                                                 //verifes if buses.txt is opened
        cout << "\n\t\t\t\tFile Not Found...!!!";
    else
    {
        cout<<"\t\t\t\t\t\t\t\t\t\tBuses->"<<endl;

        busFileStream.read((char *)this, sizeof(*this));            //read opens the data file in read only mode so that output is obtained

        while (!busFileStream.eof())
        {
            showBusDetails();
            busFileStream.read((char *)this, sizeof(*this));        //displays bus details in appropriate format by calling showBusDetails function
        }
        busFileStream.close();                                      //closes the data file
    }
}

// DELETE BUS
inline void Bus::deleteBus()
{
    system("cls");

    char bNo[10];
    int chk = 0;
    fstream busFileStream, tempFileStream;                          //for storing previous data in temporary file tempFileStream is used

    cout<<"\t\t\t\t\t\t\t\t\t\t\t\tDelete Bus"<<endl;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus No:-> ";
    cin.ignore();
    cin.getline(bNo, 10);

    busFileStream.open("buses.txt", ios::in | ios::app | ios::binary);

    if (busFileStream.fail())
    {
        cout << "\n\\t\t\t\t\t\t\t\t\t\tCan't Open File...!!";
        system("pause");
    }

    else
    {
        tempFileStream.open("temp.txt", ios::out | ios::app | ios::binary);
        busFileStream.read((char *)this, sizeof(*this));
        while (!busFileStream.eof())
        {
            if (strcmp(getBusNo(), bNo) != 0)
            {
                tempFileStream.write((char *)this, sizeof(*this));      //if bus number does not match the previous data then stored in temp file
            }                               //using temporary file we store the data of buses whose bus number didn't match and finally delete buses.txt to obtain remaining buses only
            else
            {
                chk = 1;            //if bus number matches chk is set to 1
            }
            busFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Not Found...!!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tBus Deleted...!!\n";
        }

        busFileStream.close();
        tempFileStream.close();
        remove("buses.txt");                                            //buses.txt is deleted
        rename("temp.txt", "buses.txt");                                //renames temp.txt to buses.txt because data of buses.txt is already deleted
    }
}
