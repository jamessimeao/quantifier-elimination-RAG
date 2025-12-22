#include "../include/poly.hpp"

PolyXX::PolyXX(CtxXX & ctxXX)
{
    std::cout << "Initializing PolyXX...\n";
    ca_poly_init(poly, ctxXX.unwrap());
    ctxXX_ptr = &ctxXX;
}

PolyXX::PolyXX(PolyXX & P)
{
    ctxXX_ptr = P.ctxXX_ptr;
    ca_poly_set(poly, P.poly, ctx());
}
    
PolyXX::~PolyXX()
{
    std::cout << "Destructing PolyXX "<< name <<"...\n";
    println();
    ca_poly_clear(poly, ctx());
}

void PolyXX::set_name(std::string_view new_name)
{
    name = new_name;
}

void PolyXX::println()
{
    std::cout << name << ":\n";
    ca_poly_print(poly, ctx());
}

ca_ctx_t & PolyXX::ctx()
{
    return ctxXX_ptr->unwrap();
}

void PolyXX::set_coeff(slong n, CaXX & x)
{
    ca_poly_set_coeff_ca(poly,n, x.unwrap(), ctx());
}

void PolyXX::set_to_neg()
{
    ca_poly_neg(poly,poly, ctx());
}

bool PolyXX::set_to_rem(PolyXX & A, PolyXX & B)
{
    int success = ca_poly_rem(poly, A.poly, B.poly, ctx());
    return success == 1;
}

truth_t PolyXX::check_is_zero()
{
    return ca_poly_check_is_zero(poly, ctx());
}