#pragma once

#include <iostream>
#include "flint/ca.h"

// C++ wrapper for ca_ctx_t.
class CaCtxXX
{
private:
    ca_ctx_t ctx;
public:
    CaCtxXX();
    ~CaCtxXX();
    ca_ctx_t & unwrap();
};