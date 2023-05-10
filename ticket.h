#pragma once

#include <iostream>

#include "bus.h"
#include "reservation.h"

// CLASS TICKET
class Ticket
{
private:
    char name[20], pnrNo[10];
    Bus bus;

public:
    void generateTicket(char *, Bus);
    void displayTicket();
    void bookTicket();
    void cancelTicket();
    void editTicket();
    void showTicketsByPNR();
    void showTicketsByName();
    void showTicketsByBus();
    void showAllTickets();

    // GETTERS
    char *getName()
    {
        return name;
    }

    char *getPnrNo()
    {
        return pnrNo;
    }

    // SETTERS
    void setName(char *n)
    {
        if (n && n[0])
            strcpy(name, n);
    }
};