#include "../include/poly.hpp"

PolyXX::PolyXX(CtxXX & ctxXX)
{
    printf("Initializing PolyXX...\n");fflush(stdout);
    ca_poly_init(poly, *ctxXX._ctx_ptr());
    ctxXX_ptr = &ctxXX;
}
    
PolyXX::~PolyXX()
{
    printf("Destructing PolyXX...\n");fflush(stdout);
    ca_poly_clear(poly, *ctx_ptr());
}

void PolyXX::println()
{
    ca_poly_print(poly, *ctx_ptr());
}

ca_ctx_t * PolyXX::ctx_ptr()
{
    return ctxXX_ptr->_ctx_ptr();
}

void PolyXX::set_coeff(slong n, CaXX & x)
{
    ca_poly_set_coeff_ca(poly,n,*x._ca_ptr(),*ctx_ptr());
}