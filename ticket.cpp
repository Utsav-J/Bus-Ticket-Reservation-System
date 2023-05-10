#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "ticket.h"
#include "bus.h"
#include "pnr.h"
#include "reservation.h"

using namespace std;

class Passenger{
    private:
    int age;
    char name[20],address[20],gender[10];
    public:
    void generateTicket();
    void displayTicket();
    void bookTicket();
    void cancelTicket();
    void showTicketsbyPNR();
    void showTicketsbyName();
    void showTicketsByBus();
    void showAllTickets();
};


void Ticket::generateTicket(char *n, Bus b)
{
    strcpy(name, n);
    strcpy(pnrNo, generatePNR(99999).c_str());
    bus = b;
}

void Ticket::displayTicket()
{
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t Name:-> " << getName();
    cout << "\n\t\t\t\t\t\t\t\t\t\t PNR No:-> " << getPnrNo();
    cout << "\n\t\t\t\t\t\t\t\t\t\t Bus No:-> " << bus.getBusNo();
    cout << "\n\t\t\t\t\t\t\t\t\t\t From:-> " << bus.getSource();
    cout << "\n\t\t\t\t\t\t\t\t\t\t To:-> " << bus.getDestination();
    cout << fixed << setprecision(2);
    cout << "\n\t\t\t\t\t\t\t\t\t\t Bus Fare:-> " << bus.getBusFare() << endl;
    cout << "\n";
}

void Ticket::bookTicket()
{
    Reservation reservation;
    system("cls");

    char from[20], to[20];
    int chk = 0;

    Bus b;      //b is an object of class B which is used in our main program
    fstream busFileStream, ticketFileStream, tempFileStream;

    cout<<"\t\t\t\t\t\t\t\t\t\t\tTicket Booking"<<endl;

    busFileStream.open("buses.txt", ios::in | ios::app | ios::binary);  //here buses.txt is opened in input, append and binary mode
    if (busFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tFile couldn't open!!\n";
    }

    else
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
        cin.ignore();
        cin.getline(from, 20);
        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
        cin.getline(to, 20);

        system("cls");
        cout<<"\t\t\t\t\t\t\t\t\t\t\tBUSES AVAILABLE"<<endl;

        busFileStream.read((char *)&b, sizeof(b));      //from buses.txt file the available buses function is run
        while (!busFileStream.eof())
        {
            if (strcmpi(b.getSource(), from) == 0 && strcmpi(b.getDestination(), to) == 0)  //input string and data stored in buses.txt is compared using strcmpi
            {
                b.showBusDetails();
                chk = 1;
            }
            busFileStream.read((char *)&b, sizeof(b));
        }

        busFileStream.close();

        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Buses Found!!\n";
        }
        else
        {
            char bNo[10];
            int booked = 0;

            cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
            cin.getline(bNo, 10);

            busFileStream.open("buses.txt", ios::in | ios::app | ios::binary);
            tempFileStream.open("temp.txt", ios::out | ios::app | ios::binary);

            busFileStream.read((char *)&b, sizeof(b));
            while (!busFileStream.eof())
            {
                if (strcmpi(b.getSource(), from) == 0 && strcmpi(b.getDestination(), to) == 0 && strcmp(b.getBusNo(), bNo) == 0)
                {
                        system("cls");
                        cout<<"\t\t\t\t\t\t\t\t\t\t\tTicket Booking"<<endl;
                        char n[20];
                        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Customer Name :-> ";
                        cin.getline(n, 20);
                        b.setBookedSeats();
                        generateTicket(n, b);
                        ticketFileStream.open("tickets.txt", ios::out | ios::app | ios::binary);
                        ticketFileStream.write((char *)this, sizeof(*this));
                        ticketFileStream.close();
                        tempFileStream.write((char *)&b, sizeof(b));

                        booked = 1;
                        system("cls");
                        cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\tBooking Details"<<endl;
                        displayTicket();
                        cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Booked Successfully with reservation id "<<reservation.generateid(9999)<<endl;
                }
                else
                {
                    tempFileStream.write((char *)&b, sizeof(b));
                }
                busFileStream.read((char *)&b, sizeof(b));
            }

            if (booked == 1)
            {
                busFileStream.close();
                tempFileStream.close();
                remove("buses.txt");
                rename("temp.txt", "buses.txt");
            }
        }
        busFileStream.close();
    }
}

void Ticket::cancelTicket()
{
    system("cls");

    char pnr[10];
    int chk = 0;

    fstream busFileStream, ticketFileStream, tempFileStream, busTempFileStream;

    cout << "\n\t\t\t\t\t\t\t\t\t\t\tCancel Ticket"<<endl;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr, 10);

    ticketFileStream.open("tickets.txt", ios::in | ios::app | ios::binary);
    tempFileStream.open("temp.txt", ios::out | ios::app | ios::binary);

    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tFile couldn't open!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (strcmp(getPnrNo(), pnr) != 0)
            {
                tempFileStream.write((char *)this, sizeof(*this));
            }
            else
            {
                Bus b;
                busFileStream.open("buses.txt", ios::in | ios::app | ios::binary);
                busTempFileStream.open("bustemp.txt", ios::out | ios::app | ios::binary);

                busFileStream.read((char *)&b, sizeof(b));
                while (!busFileStream.eof())
                {
                    if (strcmp(b.getBusNo(), bus.getBusNo()) == 0)
                    {
                        b.setCancelTicket();
                        busTempFileStream.write((char *)&b, sizeof(b));
                    }
                    else
                    {
                        busTempFileStream.write((char *)&b, sizeof(b));
                    }
                    busFileStream.read((char *)&b, sizeof(b));
                }
                busFileStream.close();
                busTempFileStream.close();
                remove("buses.txt");
                rename("bustemp.txt", "buses.txt");
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            ticketFileStream.close();
            tempFileStream.close();
            cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Not Found!!\n";
        }
        else
        {
            ticketFileStream.close();
            tempFileStream.close();
            remove("tickets.txt");
            rename("temp.txt", "tickets.txt");
            cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Cancelled!!\n";
        }
    }
}

void Ticket::showTicketsByPNR()
{
    system("cls");

    char pnr[10];
    int chk = 0;
    fstream ticketFileStream;

    cout<<"\t\t\t\t\t\t\t\t\t\t\tShow tickets by PNR"<<endl;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr, 10);

    system("cls");

    ticketFileStream.open("tickets.txt", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tFile couldn't open!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (strcmp(getPnrNo(), pnr) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings!!\n";
        }
        ticketFileStream.close();
    }
}

void Ticket::showTicketsByName()
{
    system("cls");

    char n[20];
    int chk = 0;
    fstream ticketFileStream;

    cout<<"\t\t\t\t\t\t\t\t\t\t\t\tShow bookings by Name->"<<endl;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Passenger Name:-> ";
    cin.ignore();
    cin.getline(n, 20);

    system("cls");

    cout<<"\t\t\t\t\t\t\t\t\t\t\t\tBookings"<<endl;

    ticketFileStream.open("tickets.txt", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tFile couldn't open!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (strcmpi(getName(), n) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings!!\n";
        }
        ticketFileStream.close();
    }
}

void Ticket::showTicketsByBus()
{
    system("cls");

    char bNo[10];
    int chk = 0;
    fstream ticketFileStream;

    cout<<"\t\t\t\t\t\t\t\t\t\t\t\tSHOW BOOKINGS BY NAME"<<endl;
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    cin.ignore();
    cin.getline(bNo, 10);

    system("cls");

    cout<<"\t\t\t\t\t\t\t\t\t\t\t\tBOOKINGS"<<endl;

    ticketFileStream.open("tickets.txt", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tFile couldn't open!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (strcmp(bus.getBusNo(), bNo) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings!!\n";
        }
        ticketFileStream.close();
    }
}

void Ticket::showAllTickets()
{
    system("cls");

    fstream ticketFileStream;

    system("cls");

    cout<<"\t\t\t\t\t\t\t\t\t\t\t\tBookings"<<endl;

    ticketFileStream.open("tickets.txt", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\tFile couldn't open!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            displayTicket();
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        ticketFileStream.close();
    }
}