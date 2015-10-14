//
//  main.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/14/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "../stdafx.h"

using namespace std;

int main () {
    string s1 ("String One");
    string s2 ("String Two");
    int x = 256;

    cout << s1 + s2 << endl;

    cout << s1 + " " + s2 << endl;

    cout << s1 + " " + s2 + " " + to_string(x) << endl;

    return 0;
}
