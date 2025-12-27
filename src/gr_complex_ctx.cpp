#include "../include/gr_complex_ctx.hpp"

GRComplexCtx::GRComplexCtx()
{
    gr_ctx_init_complex_ca(ctx);
}

GRComplexCtx::~GRComplexCtx()
{
}