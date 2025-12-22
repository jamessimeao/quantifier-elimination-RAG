#pragma once

#include <iostream>
#include "flint/ca.h"

// C++ wrapper for ca_ctx_t.
class CtxXX
{
private:
    ca_ctx_t ctx;
public:
    CtxXX();
    ~CtxXX();
    ca_ctx_t * _ctx_ptr();
};