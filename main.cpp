#include <iostream>
#include <string.h>

#include "bus.cpp"
#include "ticket.cpp"
#include "pnr.h"
#include "reservation.h"

using namespace std;

class MainClass:public Ticket, public Bus{ // Multiple Inheritance
    public:
        void welcomeScreen(){
        system("cls");
        cout<<"\t\t\t\t\t\t\t\t\tWELCOME TO BUS TICKET RESERVATION SYSTEM"<<endl;
        system("pause");
        mainMenu();    // Calls the mainMenu function without creating its object in main function
        }

    void mainMenu()
    {
        int choice;

        while (1)
        {
            try{    // Exception Handling
                system("cls");

                cout<<"\t\t\t\t\t\t\t\t\t\tChoose an option"<<endl;
                cout << "\t\t\t\t\t\t\t 1. User Menu                                    \n";
                cout << "\t\t\t\t\t\t\t 2. Admin Menu                                   \n";
                cout << "\t\t\t\t\t\t\t 3. EXIT                                         \n";
                cout << "\n\t\t\t\t\t\t\tEnter your choice:-> ";

                cin >> choice;

                if (choice < 1 || choice > 3) {
                        throw "Invalid choice. Please enter a value between 1 and 3.";
                    }

                switch (choice)
                {
                case 1:
                    userLogin();
                    break;

                case 2:
                    adminLogin();
                    break;

                case 3:
                    system("cls");
                    cout << "\n\n\n\n\t\t\t\t\t\t\t\t\t\t  Thanks for using !! \t\t\t\n";
                    exit(0);
                    }
                }
            catch (const char* msg) {
                cerr << msg << endl;
                system("pause");
            }
        }
    }

    //USER LOGIN
    void userLogin(){
        string userName, userPass;

        system("cls");

        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter UserId:-> ";
        cin >> userName;
        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Password:-> ";
        cin >> userPass;

        if (userName == "user" && userPass == "pass")
        {
            userMenu();
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tUsername or Password is wrong...!!! ";
            system("pause");
            userLogin();
        }
    }

    // ADMIN LOGIN
    void adminLogin()
    {
        string adminUname, adminPass;

        system("cls");

        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter AdminID:-> ";
        cin >> adminUname;
        cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Password:-> ";
        cin >> adminPass;

        if (adminUname == "admin" && adminPass == "pass")
        {
            adminMenu();
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\t\t\t\tUsername or Password is wrong...!!! ";
            system("pause");
            adminLogin();
        }
    }

    // USER MENU
    void userMenu()
    {

        int choice;

        while (1)
        {
            system("cls");

            Ticket t;
            cout << "\t\t\t\t\t\t\t\t\t\t 1. Book Ticket\n";
            cout << "\t\t\t\t\t\t\t\t\t\t 2. View Ticket\n";
            cout << "\t\t\t\t\t\t\t\t\t\t 3. Cancel Ticket\n";
            cout << "\t\t\t\t\t\t\t\t\t\t 4. BACK\n";

            cout << "\n\t\t\t\t\t\t\t\t\t\tEnter your choice:-> ";

            cin >> choice;

            switch (choice)
            {
            case 1:
                t.bookTicket();
                system("pause");
                break;

            case 2:
                t.showTicketsByPNR();
                system("pause");
                break;

            case 3:
                t.cancelTicket();
                system("pause");
                break;

            case 4:
                system("cls");
                mainMenu();
                break;

            default:
                cout << "\n\t\t\t\t\t  Choose valid option!!! \t\t\t\n";
                system("pause");
                break;
                userMenu();
            }
        }
    }
    void adminMenu()
    {
        Bus b;          // object of Bus class
        Ticket t;       // object of Ticket class

        int choice;

        while (1)
        {
            system("cls");
            cout<<"\t\t\t\t\t\t\t\t\t\t\t\tAdmin Portal"<<endl;

            cout << "\t\t\t\t\t\t\t\t\t\t 1. Add Bus"<<endl;
            cout << "\t\t\t\t\t\t\t\t\t\t 2. View Buses"<<endl;
            cout << "\t\t\t\t\t\t\t\t\t\t 3. Book Ticket"<<endl;
            cout << "\t\t\t\t\t\t\t\t\t\t 4. Cancel Ticket"<<endl;
            cout << "\t\t\t\t\t\t\t\t\t\t 5. View Bookings"<<endl;
            cout << "\t\t\t\t\t\t\t\t\t\t 6. Delete Bus"<<endl;
            cout << "\t\t\t\t\t\t\t\t\t\t 7. BACK"<<endl;
            cout << "\n\t\t\t\t\t\t\t\t\t\tEnter your choice:-> "<<endl;

            cin >> choice;

            switch (choice)
            {
            case 1:
                b.addBus();
                system("pause");
                break;

            case 2:
                b.showAllBus();
                system("pause");
                break;

            case 3:
                t.bookTicket();
                system("pause");
                break;

            case 4:
                t.cancelTicket();
                system("pause");
                break;

            case 5:
                viewBookingsMenu();
                break;

            case 6:
                b.deleteBus();
                system("pause");

            case 7:
                system("cls");
                mainMenu();
                break;

            default:
                cout << "\n\t\t\t\t\t  Choose valid option!!! \t\t\t\n";
                system("pause");
                adminMenu();
            }
        }
    }

    void viewBookingsMenu()
    {
        Ticket t;
        int choice;

        while (1)
        {
            system("cls");
            cout<<"\t\t\t\t\t\t\t\t\t\t\t\tView Bookings"<<endl;
            cout << "\t\t\t\t\t\t\t\t\t\t 1. By PNR"<<endl;
            cout << "\t\t\t\t\t\t\t\t\t\t 2. By Name"<<endl;
            cout << "\t\t\t\t\t\t\t\t\t\t 3. By Bus"<<endl;
            cout << "\t\t\t\t\t\t\t\t\t\t 4. All Bookings"<<endl;
            cout << "\t\t\t\t\t\t\t\t\t\t 5. BACK"<<endl;

            cout << "\n\t\t\t\t\t\t\t\t\t\tEnter your choice:-> "<<endl;
            cin >> choice;

            switch (choice)
            {
            case 1:
                t.showTicketsByPNR();
                system("pause");
                break;

            case 2:
                t.showTicketsByName();
                system("pause");
                break;

            case 3:
                t.showTicketsByBus();
                system("pause");
                break;

            case 4:
                t.showAllTickets();
                system("pause");
                break;

            case 5:
                system("cls");
                adminMenu();
                break;

            default:
                cout << "\n\t\t\t\t\t  Invalid option \t\t\t\n";
                system("pause");
                viewBookingsMenu();
            }
        }
    }
};

int main()
{
    MainClass obj;
    system("cls");
    obj.welcomeScreen();
    return 0;
}
