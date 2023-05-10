#include <bits/stdc++.h>
using namespace std;
int main(){
    fstream f;
    f.open("test.txt", ios::in | ios::out | ios::binary);
    f.write((char *)this, sizeof(*this));
    f.close();
    return 0;
}


