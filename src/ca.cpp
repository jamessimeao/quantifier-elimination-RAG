#include "../include/ca.hpp"

CaXX::CaXX(CaCtxXX & ctxXX)
{
    std::cout << "Initilizing CaXX...\n";
    ca_init(x, ctxXX.unwrap());
    ctxXX_ptr = &ctxXX;
}

CaXX::~CaXX()
{
    std::cout << "Destructing CaXX...\n";
    ca_clear(x, ctx());
}

void CaXX::println()
{
    ca_print(x, ctx());
    std::cout << "\n";
}

ca_ctx_t & CaXX::ctx()
{
    return ctxXX_ptr->unwrap();
}

ca_t & CaXX::unwrap()
{
    return x;
}

void CaXX::set_si(slong v)
{
    ca_set_si(x, v, ctxXX_ptr->unwrap());
}