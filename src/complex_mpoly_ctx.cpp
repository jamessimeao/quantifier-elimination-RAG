#include "../include/complex_mpoly_ctx.hpp"

ComplexMPolyCtx::ComplexMPolyCtx(GRCtx & ctx, const slong nvars)
{
    ctx_ptr = &ctx;
    _nvars = nvars;
    gr_mpoly_ctx_init(mpoly_ctx, ctx.unwrap(), nvars, ORD_DEGLEX);
}

ComplexMPolyCtx::~ComplexMPolyCtx()
{
    gr_mpoly_ctx_clear(mpoly_ctx);
}

gr_mpoly_ctx_t & ComplexMPolyCtx::unwrap()
{
    return mpoly_ctx;
}