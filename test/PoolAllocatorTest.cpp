//
//  PoolAllocatorTest.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/23/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include "../src/stdafx.h"
#include "../src/Memory/PoolAllocator.h"
#include "../src/WAM/types.h"

using namespace std;

int main () {
    int i;
    cout << "Pool Allocator Test:" << endl;
    
    PoolAllocator p (4096, 16, 0);

    cout << "start:\t" << p.getStart () << endl;
    cout << "end:\t" << p.getEnd () << endl;
    cout << "size:\t" << p.getSize () << endl;
    cout << "count:\t" << p.getAllocations () << endl;
    cout << "osize:\t" << p.getObjectSize () << endl << endl;
    
    cout << "Allocating 100 objects..." << endl;
    ValueCell* pArray[200];
    for (i = 0; i < 100; i++) {
        pArray[i] = (ValueCell*) p.allocate (16,0);
    }
    cout << "used:\t" << p.getMemUsed () << endl;
    cout << "count:\t" << p.getAllocations () << endl << endl;

    cout << "Deallocating 50 objects..." << endl;
    for (i = 0; i < 100; i += 2) {
        p.deallocate(pArray[i]);
    }
    cout << "used:\t" << p.getMemUsed () << endl;

    cout << "Allocating 150 objects..." << endl;
    for (i = 0; i < 100; i += 2) {
        pArray[i] = (ValueCell*) p.allocate (16,0); 
    }
    for (i = 100; i < 200; i++) {
        pArray[i] = (ValueCell*) p.allocate (16,0);
    }
    cout << "used:\t" << p.getMemUsed () << endl;
    cout << "count:\t" << p.getAllocations () << endl << endl;

    cout << "Deallocating all 200..." << endl;
    for (i = 0; i < 200; i++) {
        p.deallocate (pArray[i]);
    }
    cout << "used:\t" << p.getMemUsed () << endl;
    cout << "count:\t" << p.getAllocations () << endl << endl;


    

}
