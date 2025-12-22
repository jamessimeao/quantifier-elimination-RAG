#include "../include/ctx.hpp"

CtxXX::CtxXX()
{
    std::cout << "Initilizing CtxXX...\n";
    ca_ctx_init(ctx);
}

CtxXX::~CtxXX()
{
    std::cout << "Destructing CtxXX...\n";
    ca_ctx_clear(ctx);
}

ca_ctx_t & CtxXX::unwrap()
{
    return ctx;
}