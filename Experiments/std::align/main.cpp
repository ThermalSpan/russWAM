// Created by Russell Bentley
// Copyright 2015
// Distributed under the MIT License

#include "../stdafx.h"

// TEST - std::align
// void* align( std::size_t alignment,
//              std::size_t size,
//              void*& ptr,
//              std::size_t& space );
//

#define M_BUFFER_SIZE 256
#define M_SIZE_MAX 8
#define M_ALIGNMENT_MAX 8
#define M_SPACE_MAX 8
#define M_START_OFFSET_MAX 16

using namespace std;

int main () {
  void* start = malloc (M_BUFFER_SIZE);
  assert (start != nullptr);

  cout << "Start is \t " << start << endl;
  size_t trial, offset, alignment, size, space;
  void* pointer = start;
  trial = 0;
  for(        offset    = 0; offset    <= M_START_OFFSET_MAX; offset++    ) {
    for (     alignment = 0; alignment <= M_ALIGNMENT_MAX;    alignment++ ) {
      for (   size      = 0; size      <= M_SIZE_MAX;         size++      ) {
        for ( space     = 0; space     <= M_SPACE_MAX;        space++     ) {

          size_t T_size      = size;
          size_t T_space     = space;
          size_t T_alignment = alignment;
          void*  T_pointer   = pointer;

          pointer = static_cast <void*> (static_cast <char *> (start) + offset);

          align(T_alignment, T_size, T_pointer, T_space);

          bool B_size      = size     != T_size;
          bool B_space     = space    != T_space;
          bool B_alignment = alignment != T_alignment;
          bool B_pointer   = pointer  != T_pointer;

          cout << "==================================================================" << endl;
          cout << "==  TRIAL: " << trial++ << "\t| Before\t\t| After\t\t| Change?" << endl;
          cout << "==================================================================" << endl;
          cout << "alignment:\t| "  << alignment << "\t\t\t| " << T_alignment << "\t\t\t| " << B_alignment << endl;
          cout << "size:\t\t| "     << size      << "\t\t\t| " << T_size      << "\t\t\t| " << B_size      << endl;
          cout << "pointer:\t| "    << pointer   << "| "       << T_pointer   << "| "       << B_pointer   << endl;
          cout << "space:\t\t| "    << space     << "\t\t\t| " << T_space     << "\t\t\t| " << B_space     << endl;
          cout << "==================================================================" << endl;
          cout << endl << endl;
        }
      }
    }
  }

  return 0;
}
