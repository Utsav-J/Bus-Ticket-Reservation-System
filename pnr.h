#pragma once

#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

string generatePNR(int n)
{
    srand(time(0));
    string pnr;
    int randomNo = rand() % n;
    pnr = "PNR" + to_string(randomNo);
    return pnr;
}