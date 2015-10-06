//
//  Driver.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/6/2015
//  Copyright (c) 2015 Russell Wilhelm Bentley
//  Distributed under the MIT License
//

#pragma once

#include "../stdafx.h"
#include "types.h"
#include "Engine.h"

class Driver {
public:
    Driver (WamWord* code, WamWord* start, int size);

    ~Driver ();

    void run ();
 
protected:
    int m_size;

    WAM* m_wam;

    WamWord* m_Code;

    WamWord* m_Preg;
};
