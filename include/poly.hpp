#pragma once

#include "flint/ca_poly.h"
#include "../include/ctx.hpp"
#include "../include/ca.hpp"

// C++ wrapper for ca_poly_t
class PolyXX
{
private:
    ca_poly_t poly;
    CtxXX * ctxXX_ptr;
    ca_ctx_t * ctx_ptr();
public:
    PolyXX(CtxXX & ctxXX);
    ~PolyXX();
    void println();
    void set_coeff(slong n, CaXX& x);
};