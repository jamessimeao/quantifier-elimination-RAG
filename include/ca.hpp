#pragma once

#include <iostream>
#include "ctx.hpp"

// C++ wrapper for ca_t
class CaXX
{
private:
    ca_t x;
    CtxXX * ctxXX_ptr;
    ca_ctx_t * ctx_ptr();
public:
    CaXX(CtxXX & ctxXX);
    ~CaXX();
    ca_t * _ca_ptr();
    void set_si(slong v);

    void println();
};

