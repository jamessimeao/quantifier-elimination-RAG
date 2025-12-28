#pragma once

#include "flint/gr_mpoly.h"
#include "gr_ctx.hpp"

// Wrapper class for gr_mpoly_ctx_t, which represents a ring of polynomials,
// but with complex coefficients as implemented by Calcium. That is,
// gr_mpoly_ctx_t is constructed from a ca_ctx_t.

class ComplexMPolyCtx : public GRCtx
{
private:
    GRCtx * ctx_ptr;
    gr_mpoly_ctx_t mpoly_ctx;
    slong _nvars;

public:
    ComplexMPolyCtx(GRCtx & ctx, const slong nvars);
    ~ComplexMPolyCtx();
    gr_mpoly_ctx_t & unwrap();

    gr_ctx_t & unwrap_gr() override;
};