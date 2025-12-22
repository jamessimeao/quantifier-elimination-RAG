#include "../include/ca.hpp"

CaXX::CaXX(CtxXX & ctxXX)
{
    std::cout << "Initilizing CaXX...\n";
    ca_init(x, *ctxXX._ctx_ptr());
    ctxXX_ptr = &ctxXX;
}

CaXX::~CaXX()
{
    std::cout << "Destructing CaXX...\n";
    ca_clear(x,*ctx_ptr());
}

void CaXX::println()
{
    ca_print(x, *ctx_ptr());
    std::cout << "\n";
}

ca_ctx_t * CaXX::ctx_ptr()
{
    return ctxXX_ptr->_ctx_ptr();
}

ca_t * CaXX::_ca_ptr()
{
    return &x;
}

void CaXX::set_si(slong v)
{
    ca_set_si(x, v, *ctxXX_ptr->_ctx_ptr());
}