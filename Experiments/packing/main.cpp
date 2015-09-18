// 
// main.cpp
// russWAM
//
// Created by Russell Wilhelm Bentley 9/17/15
// Distributed under the MIT license
//

#include "../stdafx.h"

using namespace std;

struct i1 {
  int n1;
};

struct i2 {
  int n1;
  int n2;
};

struct i3 {
  int n1;
  int n2;
  int n3;
};

struct i4 {
  int n1;
  int n2;
  int n3;
  int n4;
};

struct i5 {
  int n1;
  int n2;
  int n3;
  int n5;
};

struct i6 {
  int n1;
  int n2;
  int n3;
  int n4;
  int n5;
  int n6;
};

struct c1 {
  char n1;
};

struct c2 {
  char n1;
  char n2;
};

struct c3 {
  char n1;
  char n2;
  char n3;
};

struct c4 {
  char n1;
  char n2;
  char n3;
  char n4;
};

struct c5 {
  char n1;
  char n2;
  char n3;
  char n4;
  char n5;
};

struct c6 {
  char n1;
  char n2;
  char n3;
  char n4;
  char n5;
  char n6;
};

struct i1c1 {
  int n1;
  char c1;
};

struct c1i1 {
  char c1;
  int n1;
};

struct i1c1i1 {
  int n1;
  char c1;
  int n2;
};

struct c1i4 {
  char c1;
  i4 s;
};

struct c1i5 {
  char c1;
  i5 s;
}; 

int main () {
  cout << "i1:\t" << sizeof (i1) << endl;
  cout << "i2:\t" << sizeof (i2) << endl;
  cout << "i3:\t" << sizeof (i3) << endl;
  cout << "i4:\t" << sizeof (i4) << endl;
  cout << "i5:\t" << sizeof (i5) << endl;
  cout << "i6:\t" << sizeof (i6) << endl;

  cout << "c1:\t" << sizeof (c1) << endl;
  cout << "c2:\t" << sizeof (c2) << endl;
  cout << "c3:\t" << sizeof (c3) << endl;
  cout << "c4:\t" << sizeof (c4) << endl;
  cout << "c5:\t" << sizeof (c5) << endl;
  cout << "c6:\t" << sizeof (c6) << endl;
  
  cout << "i1c1:\t" << sizeof (i1c1) << endl;
  cout << "c1i1:\t" << sizeof (c1i1) << endl;
  cout << "i1c1i1:\t" << sizeof (i1c1i1) << endl;
  cout << "c1i4:\t" << sizeof (c1i4) << endl;
  cout << "c1i5:\t" << sizeof (c1i5) << endl;
  return 0;
}
