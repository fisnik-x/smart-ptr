/*++
    control_block.hpp
    
    Author: Fisnik
    Copyright (C) Fisnik. All rights reserved.

    Abstract:

    

    This source code is licensed under the MIT license found in the
    LICENSE file in the root directory of this source tree. 
--*/
#pragma once

struct Control_Block{
    int m_refCount{0};
    int m_weakCount{0};
};