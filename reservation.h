#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

class Reservation {
public:
    string id;
    string generateid(int n) {
        srand(time(0));
        int randomNo = rand() % n;
        id = to_string(randomNo);
        return id;
    }
};