#include "../stdafx.h"
#include "../../src/WAM/types.h"

using namespace std;

int main() {
  cout << "size of:"       << endl;
  cout << "int\t\t"        << sizeof (int)         << endl;
  cout << "size_t\t\t"     << sizeof (size_t)      << endl;
  cout << "char\t\t"       << sizeof (char)        << endl;
  cout << "char*\t\t"      << sizeof (char *)      << endl;
  cout << "void*\t\t"      << sizeof (char *)      << endl;
  cout << "Value Cell\t"   << sizeof (ValueCell)   << endl;
  cout << "Functor Cell\t" << sizeof (FunctorCell) << endl;
  cout << "testCell\t"    << sizeof (DataCell)    << endl;
  return 0;
}