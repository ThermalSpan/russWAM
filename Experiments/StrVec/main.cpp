//
//  main.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/27/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "../../src/stdafx.h"

using namespace std;

typedef std::vector <string> StrVec;

class tclass {
public:
    tclass ();
    ~tclass () {};
    void addString (int i, string s);
    string getString (int i);
protected:
    StrVec vec;
};

tclass::tclass () {
    vec = StrVec (10);
}

void tclass::addString (int i, string s) {
    /* if (vec.at(i) == nullptr) {
        vec.at(i) = s;
    }
    else {
        vec.at (i).assign (s);
    }*/
    vec.at(i).assign(s);
}

string tclass::getString (int i) {
    return vec.at(i);
}

int main () {
    tclass t0;
    
    string s1 ("s1");
    string s2 ("s2");
    string s3 ("s3");

    t0.addString (0, s1);
    t0.addString (1, s2);
    t0.addString (2, s3);

    cout << "First round:" << endl;
    cout << "0:\t" << t0.getString (0) << endl;
    cout << "1:\t" << t0.getString (1) << endl;
    cout << "2:\t" << t0.getString (2) << endl;
    cout << "3:\t" << t0.getString (3) << endl;

    t0.addString (0, s3);

    cout << "Second round:" << endl;
    cout << "0:\t" << t0.getString (0) << endl;

    return 0;
}
