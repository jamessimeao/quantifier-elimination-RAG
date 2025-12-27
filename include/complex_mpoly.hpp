#pragma once

#include <iostream>
#include "flint/gr_mpoly.h"
#include "complex_mpoly_ctx.hpp"

// Class that represents a multivariable polynomial over complex numbers.
// It is a wrapper class for gr_mpoly_t with a ca_t context instead of a general gr_ctx_t.
class ComplexMPoly
{
private:
    ComplexMPolyCtx * ctx_ptr;
    gr_mpoly_t poly;
public:
    ComplexMPoly(ComplexMPolyCtx & ctx);
    ~ComplexMPoly();
    gr_mpoly_t &  unwrap();

    void println();

    bool set_coeff_si(slong c, ulong * exp);
};