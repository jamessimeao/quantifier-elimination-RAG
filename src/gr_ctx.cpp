#include "../include/gr_ctx.hpp"

#include <iostream>

GRCtx::~GRCtx()
{
    // Don't implement the destructor,
    // because it can conflict with the child class destructor.
    //gr_ctx_clear(ctx);
}

gr_ctx_t & GRCtx::unwrap_gr()
{
    return ctx;
}