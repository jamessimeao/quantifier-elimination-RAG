#include "../include/ca_poly.hpp"

CaPoly::CaPoly(CaCtx & ctx)
{
    std::cout << "Initializing CaPoly...\n";
    ca_poly_init(poly, ctx.unwrap());
    ctx_ptr = &ctx;
}

CaPoly::CaPoly(CaPoly & P)
{
    copy(P);
}
    
CaPoly::~CaPoly()
{
    std::cout << "Destructing CaPoly...\n";
    println();
    ca_poly_clear(poly, ctxUnwrap());
}

ca_poly_t & CaPoly::unwrap()
{
    return poly;
}

void CaPoly::set_name(std::string_view new_name)
{
    name = new_name;
}

void CaPoly::println()
{
    std::cout << name << ":\n";
    ca_poly_print(poly, ctxUnwrap());
}

truth_t CaPoly::check_is_zero()
{
    return ca_poly_check_is_zero(poly, ctxUnwrap());
}

// returns true if successful
bool CaPoly::compute_degree()
{
    bool is_proper {ca_poly_is_proper(poly, ctxUnwrap()) == 1};
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
slong CaPoly::get_degree()
{
    return degree;
}

ca_ctx_t & CaPoly::ctxUnwrap()
{
    return ctx_ptr->unwrap();
}

// Copy ca_poly and ctx, but don't copy the name
void CaPoly::copy(CaPoly & A)
{
    ctx_ptr = A.ctx_ptr;
    ca_poly_set(poly, A.unwrap(), ctxUnwrap());
}

void CaPoly::set_coeff_ca(slong n, Ca & x)
{
    ca_poly_set_coeff_ca(poly, n, x.unwrap(), ctxUnwrap());
}

void CaPoly::set_si(slong x)
{
    ca_poly_set_si(poly, x, ctxUnwrap());
}

void CaPoly::set_to_neg()
{
    ca_poly_neg(poly,poly, ctxUnwrap());
}

bool CaPoly::set_to_rem(CaPoly & A, CaPoly & B)
{
    int success {ca_poly_rem(poly, A.unwrap(), B.unwrap(), ctxUnwrap())};
    return success == 1;
}

bool CaPoly::rem(CaPoly & R, CaPoly & A, CaPoly & B, CaCtx & ctx)
{
    int success {ca_poly_rem(R.unwrap(), A.unwrap(), B.unwrap(), ctx.unwrap())};
    return success == 1;
}

void CaPoly::neg(CaPoly & minusA, CaPoly & A, CaCtx & ctx)
{
    ca_poly_neg(minusA.unwrap(), A.unwrap(), ctx.unwrap());
}

void CaPoly::add(CaPoly & sum, CaPoly & A, CaPoly & B, CaCtx & ctx)
{
    ca_poly_add(sum.unwrap(), A.unwrap(), B.unwrap(), ctx.unwrap());
}

void CaPoly::sub(CaPoly & difference, CaPoly & A, CaPoly & B, CaCtx & ctx)
{
    ca_poly_sub(difference.unwrap(), A.unwrap(), B.unwrap(), ctx.unwrap());
}

void CaPoly::mul(CaPoly & product, CaPoly & A, CaPoly & B, CaCtx & ctx)
{
    ca_poly_mul(product.unwrap(), A.unwrap(), B.unwrap(), ctx.unwrap());
}

void CaPoly::pow(CaPoly & result, CaPoly & A, size_t n, CaCtx & ctx)
{
    result.set_si(1);
    for(size_t i {0}; i < n; i++)
    {
        CaPoly::mul(result, result, A, ctx);
    }
}

bool CaPoly::divrem(CaPoly & Q, CaPoly & R, CaPoly & A, CaPoly & B, CaCtx & ctx)
{
    int success {ca_poly_divrem(Q.unwrap() , R.unwrap(), A.unwrap(), B.unwrap(), ctx.unwrap())};
    return success == 1;
}

bool CaPoly::gcd(CaPoly & gcd, CaPoly & A, CaPoly & B, CaCtx & ctx)
{
    int success {ca_poly_gcd(gcd.unwrap(), A.unwrap(), B.unwrap(), ctx.unwrap())};
    return success == 1;
}

void CaPoly::mul_polys(CaPoly & product, std::list<CaPoly *> & polys, CaCtx & ctx)
{
    product.set_si(1);
    for(CaPoly * poly_ptr : polys)
    {
        CaPoly::mul(product, product, *poly_ptr, ctx);
    }
}

// Tries to compute the gcd of polys. Returns true if successful.
// It doesn't check if a polynomial is zero before computing the gcd.
// It may be necessary to first discard the zero polynomials from polys before calling this function.
bool CaPoly::compute_gcd_of_polys(CaPoly & gcd, std::list<CaPoly *> & polys, CaCtx & ctx)
{
    gcd.set_si(0);
    bool successful;
    for(CaPoly * poly_ptr : polys)
    {
        successful = CaPoly::gcd(gcd, gcd, *poly_ptr, ctx);
        if(!successful)
        {
            return false;
        }
    }
    return true;
}

// Signed pseudo remainder (why signed, if there is no sign?).
// It assumes that the degree of Q is know, and it is passed as an argument.
bool CaPoly::compute_prem(CaPoly & prem, CaPoly & P, CaPoly & Q, slong degQ, CaCtx & ctx)
{
    // Make a copy of P, so that we don't change P
    CaPoly P_multiple {P};
    // Multiply P_multiple by the leading coefficient of Q
    ca_poly_mul_ca(P_multiple.unwrap(), P_multiple.unwrap(), &P.unwrap()->coeffs[degQ], ctx.unwrap());
    // Set prem to the remainder of the division of P_multiple by Q
    bool success {CaPoly::rem(prem, P_multiple, Q, ctx)};
    return success;
}