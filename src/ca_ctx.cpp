#include "../include/ca_ctx.hpp"

CaCtxXX::CaCtxXX()
{
    std::cout << "Initilizing CaCtxXX...\n";
    ca_ctx_init(ctx);
}

CaCtxXX::~CaCtxXX()
{
    std::cout << "Destructing CaCtxXX...\n";
    ca_ctx_clear(ctx);
}

ca_ctx_t & CaCtxXX::unwrap()
{
    return ctx;
}