//
//  main.cpp
//  russWAM
//
//  Russell Wilhelm Bentley
//  Distributed under the MIT License
//

#include "../stdafx.h"

using namespace std;

int main () {
    
    char* p1 = (char*) malloc (200 * sizeof(char));
    char* p2 = &p1[100];

    cout << "p1:\t" << p1 << endl;
    cout << "p2:\t" << p2 << endl;

    long dif = p2 - p1;

    cout << "dif:\t" << dif << endl;

    return 0;
}
