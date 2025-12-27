#include "../include/gr_ctx.hpp"

#include <iostream>

GRCtx::~GRCtx()
{
    gr_ctx_clear(ctx);
}

gr_ctx_t & GRCtx::unwrap()
{
    return ctx;
}