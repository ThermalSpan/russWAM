//
//  rWAMparser.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/13/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#pragma once

#include "../stdafx.h"
#include "../WAM/types.h"

class rWAMparser {
public:
    rWAMparser ();
    
    ~rWAMparser ();

    void run (char* fileName = 0);

    void success () { m_status = true; }

    bool status () { return m_status; }

protected:
    bool m_status;
};
