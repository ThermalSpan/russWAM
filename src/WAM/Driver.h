//
//  Driver.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/6/2015
//  Copyright (c) 2015 Russell Wilhelm Bentley
//  Distributed under the MIT License
//

#pragma once

#include "../stdafx.h"
#include "types.h"
#include "WAMdebug.h"

class Driver {
public:
    Driver (WAMword* code, int size);

    ~Driver ();

    void run ();
 
protected:
    int m_size;

    WAMdebug* m_wam;

    WAMword* m_Code;

    WAMword* m_Preg;
};
