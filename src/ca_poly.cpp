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
    ca_poly_set(poly, P.unwrap(), ctx());
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

truth_t CaPolyXX::check_is_zero()
{
    return ca_poly_check_is_zero(poly, ctx());
}

// returns true if successful
bool CaPolyXX::compute_degree()
{
    bool is_proper {ca_poly_is_proper(poly, ctx()) == 1};
    if(is_proper)
    {
        degree = poly->length-1;
    }
    else
    {
        std::cout << "Failed to compute degree, because polynomial isn't proper.\n";
    }
    return is_proper;
}

// Should only be called after a call to compute_degree which returned true
slong CaPolyXX::get_degree()
{
    return degree;
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
    int success {ca_poly_rem(poly, A.unwrap(), B.unwrap(), ctx())};
    return success == 1;
}

bool CaPolyXX::rem(CaPolyXX & R, CaPolyXX & A, CaPolyXX & B, CaCtxXX & ctxXX)
{
    int success {ca_poly_rem(R.unwrap(), A.unwrap(), B.unwrap(), ctxXX.unwrap())};
    return success == 1;
}

void CaPolyXX::neg(CaPolyXX & minusA, CaPolyXX & A, CaCtxXX & ctxXX)
{
    ca_poly_neg(minusA.unwrap(), A.unwrap(), ctxXX.unwrap());
}

void CaPolyXX::add(CaPolyXX & sum, CaPolyXX & A, CaPolyXX & B, CaCtxXX & ctxXX)
{
    ca_poly_add(sum.unwrap(), A.unwrap(), B.unwrap(), ctxXX.unwrap());
}

void CaPolyXX::sub(CaPolyXX & difference, CaPolyXX & A, CaPolyXX & B, CaCtxXX & ctxXX)
{
    ca_poly_sub(difference.unwrap(), A.unwrap(), B.unwrap(), ctxXX.unwrap());
}

void CaPolyXX::mul(CaPolyXX & product, CaPolyXX & A, CaPolyXX & B, CaCtxXX & ctxXX)
{
    ca_poly_mul(product.unwrap(), A.unwrap(), B.unwrap(), ctxXX.unwrap());
}

void CaPolyXX::pow(CaPolyXX & result, CaPolyXX & A, size_t n, CaCtxXX & ctxXX)
{
    result.set_si(1);
    for(size_t i {0}; i < n; i++)
    {
        CaPolyXX::mul(result, result, A, ctxXX);
    }
}

bool CaPolyXX::divrem(CaPolyXX & Q, CaPolyXX & R, CaPolyXX & A, CaPolyXX & B, CaCtxXX & ctxXX)
{
    int success {ca_poly_divrem(Q.unwrap() , R.unwrap(), A.unwrap(), B.unwrap(), ctxXX.unwrap())};
    return success == 1;
}

bool CaPolyXX::gcd(CaPolyXX & gcd, CaPolyXX & A, CaPolyXX & B, CaCtxXX & ctxXX)
{
    int success {ca_poly_gcd(gcd.unwrap(), A.unwrap(), B.unwrap(), ctxXX.unwrap())};
    return success == 1;
}

void CaPolyXX::mul_polys(CaPolyXX & product, std::list<CaPolyXX *> & polys, CaCtxXX & ctxXX)
{
    product.set_si(1);
    for(CaPolyXX * poly_ptr : polys)
    {
        CaPolyXX::mul(product, product, *poly_ptr, ctxXX);
    }
}

// Tries to compute the gcd of polys. Returns true if successful.
// It doesn't check if a polynomial is zero before computing the gcd.
// It may be necessary to first discard the zero polynomials before calling this function.
bool CaPolyXX::compute_gcd_of_polys(CaPolyXX & gcd, std::list<CaPolyXX *> & polys, CaCtxXX & ctxXX)
{
    gcd.set_si(0);
    bool successful;
    for(CaPolyXX * poly_ptr : polys)
    {
        successful = CaPolyXX::gcd(gcd, gcd, *poly_ptr, ctxXX);
        if(!successful)
        {
            return false;
        }
    }
    return true;
}