#pragma once

#include <iostream>
#include "ca_ctx.hpp"

// C++ wrapper for ca_t
class CaXX
{
private:
    ca_t x;
    CaCtxXX * ctxXX_ptr;
    ca_ctx_t & ctx();
public:
    CaXX(CaCtxXX & ctxXX);
    ~CaXX();
    ca_t & unwrap();
    void set_si(slong v);

    void println();
};

