#include "../include/ca_ctx.hpp"

CaCtx::CaCtx()
{
    std::cout << "Initilizing CaCtx...\n";
    ca_ctx_init(ctx);
}

CaCtx::~CaCtx()
{
    std::cout << "Destructing CaCtx...\n";
    ca_ctx_clear(ctx);
}

ca_ctx_t & CaCtx::unwrap()
{
    return ctx;
}