#pragma once

#include <iostream>
#include "flint/gr_poly.h"
#include "gr_ctx.hpp"

// Wrapper class for gr_poly_t

class GRPoly
{
private:
    GRCtx * ctx_ptr;
    gr_poly_t poly;

public:
    GRPoly(GRCtx & ctx);
    ~GRPoly();
    gr_poly_t & unwrap();

    void println();

    bool set_coeff(slong exp, slong x);
};