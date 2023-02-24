/*++

control_block.hpp

@author:
	Fisnik

Copyright (c) Fisnik. All rights reserved.
--*/
#pragma once

struct Control_Block{
    int m_refCount{0};
    int m_weakCount{0};
};