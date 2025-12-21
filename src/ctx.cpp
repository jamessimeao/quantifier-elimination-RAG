#include "../include/ctx.hpp"

CtxXX::CtxXX()
{
    printf("Initilizing CtxXX...\n");fflush(stdout);
    ca_ctx_init(ctx);
}

CtxXX::~CtxXX()
{
    printf("Destructing CtxXX...\n");fflush(stdout);
    ca_ctx_clear(ctx);
}

ca_ctx_t * CtxXX::_ctx_ptr()
{
    return &ctx;
}