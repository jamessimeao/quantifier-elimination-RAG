#pragma once

#include <iostream>
#include "ca_ctx.hpp"

// C++ wrapper for ca_t
class Ca
{
private:
    ca_t x;
    CaCtx * ctx_ptr;
    ca_ctx_t & ctxUnwrap();
public:
    Ca(CaCtx & ctx);
    ~Ca();
    ca_t & unwrap();
    void set_si(slong v);

    void println();
};

