#pragma once

#include <iostream>
#include <string>

using namespace std;

class Bus;
class Bus1
{
    private:
    void deleteBus();
    friend class Bus;                   // friend class
    protected:
    int bookedSeats;
    double busFare;
    char busNo[10], source[20], destination[20];
    public:
    virtual void addBus()=0;            // Pure virtual functions
};
class Bus:public Bus1{                  //Single Inheritance
public:
    Bus()                               //Constructor
    {
        strcpy(busNo, "");
        bookedSeats = 0;
        busFare = 0.0;
        strcpy(source, "");
        strcpy(destination, "");
    }

    void addBus();
    void showAllBus();
    void showBusDetails();
    void viewBusDetails();
    void deleteBus();
    void editBus();
    /* "*" is used in character pointer variable to indicate
    that the given parameter is a pointer variable */
    char *getBusNo()
    {
        return busNo;
        // it will get single character at a time and reset the pointer
    }

    char *getSource()
    {
        return source;
    }

    char *getDestination()
    {
        return destination;
    }

    double getBusFare()
    {
        return busFare;
    }

    void setBookedSeats()
    {
        bookedSeats++;
    }

    void setCancelTicket()
    {
        bookedSeats--;
    }

    void setSource(char *s)
    {
        if (s && s[0]) strcpy(source, s);
    }

    void setDestination(char *d)
    {
        if (d && d[0]) strcpy(destination, d);
    }

    void setBusFare(double f)
    {
        if (f) busFare = f;
    }
};
