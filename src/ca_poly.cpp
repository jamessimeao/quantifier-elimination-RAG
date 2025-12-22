#include "../include/ca_poly.hpp"

CaPolyXX::CaPolyXX(CaCtxXX & ctxXX)
{
    std::cout << "Initializing CaPolyXX...\n";
    ca_poly_init(poly, ctxXX.unwrap());
    ctxXX_ptr = &ctxXX;
}

CaPolyXX::CaPolyXX(CaPolyXX & P)
{
    ctxXX_ptr = P.ctxXX_ptr;
    ca_poly_set(poly, P.poly, ctx());
}
    
CaPolyXX::~CaPolyXX()
{
    std::cout << "Destructing CaPolyXX...\n";
    println();
    ca_poly_clear(poly, ctx());
}

ca_poly_t & CaPolyXX::unwrap()
{
    return poly;
}

void CaPolyXX::set_name(std::string_view new_name)
{
    name = new_name;
}

void CaPolyXX::println()
{
    std::cout << name << ":\n";
    ca_poly_print(poly, ctx());
}

ca_ctx_t & CaPolyXX::ctx()
{
    return ctxXX_ptr->unwrap();
}

void CaPolyXX::set_coeff_ca(slong n, CaXX & x)
{
    ca_poly_set_coeff_ca(poly, n, x.unwrap(), ctx());
}

void CaPolyXX::set_si(slong x)
{
    ca_poly_set_si(poly, x, ctx());
}

void CaPolyXX::set_to_neg()
{
    ca_poly_neg(poly,poly, ctx());
}

bool CaPolyXX::set_to_rem(CaPolyXX & A, CaPolyXX & B)
{
    int success = ca_poly_rem(poly, A.poly, B.poly, ctx());
    return success == 1;
}

truth_t CaPolyXX::check_is_zero()
{
    return ca_poly_check_is_zero(poly, ctx());
}