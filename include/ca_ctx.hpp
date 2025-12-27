#pragma once

#include <iostream>
#include "flint/ca.h"

// C++ wrapper for ca_ctx_t.
class CaCtx
{
private:
    ca_ctx_t ctx;
public:
    CaCtx();
    ~CaCtx();
    ca_ctx_t & unwrap();
};