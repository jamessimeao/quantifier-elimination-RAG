#include "../include/ca.hpp"

Ca::Ca(CaCtx & ctx)
{
    std::cout << "Initilizing Ca...\n";
    ca_init(x, ctx.unwrap());
    ctx_ptr = &ctx;
}

Ca::~Ca()
{
    std::cout << "Destructing Ca...\n";
    ca_clear(x, ctxUnwrap());
}

void Ca::println()
{
    ca_print(x, ctxUnwrap());
    std::cout << "\n";
}

ca_ctx_t & Ca::ctxUnwrap()
{
    return ctx_ptr->unwrap();
}

ca_t & Ca::unwrap()
{
    return x;
}

void Ca::set_si(slong v)
{
    ca_set_si(x, v, ctx_ptr->unwrap());
}