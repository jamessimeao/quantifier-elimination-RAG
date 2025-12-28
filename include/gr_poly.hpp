#pragma once

#include <iostream>
#include "flint/gr_poly.h"
#include "gr_ctx.hpp"
#include "gr.hpp"

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

    bool println();

    bool set_coeff_si(slong exp, slong x);
    bool set_coeff_scalar(slong exp, GR & x);

    static bool neg(GRPoly & minusPoly, GRPoly & poly, GRCtx & ctx);
    static bool add(GRPoly & sum, GRPoly & poly1, GRPoly & poly2, GRCtx & ctx);
    static bool sub(GRPoly & difference, GRPoly & poly1, GRPoly & poly2, GRCtx & ctx);
    static bool mul(GRPoly & product, GRPoly & poly1, GRPoly & poly2, GRCtx & ctx);
};