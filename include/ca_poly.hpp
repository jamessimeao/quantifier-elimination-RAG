#pragma once

#include "flint/ca_poly.h"
#include "../include/ca.hpp"
#include <list>

// C++ wrapper for ca_poly_t
class CaPoly
{
private:
    ca_poly_t poly;

    CaCtx * ctx_ptr;
    ca_ctx_t & ctxUnwrap();

    std::string name;

    slong degree;
public:
    CaPoly(CaCtx & ctx);
    CaPoly(CaPoly & P);
    ~CaPoly();
    ca_poly_t & unwrap();

    void set_name(std::string_view new_name);
    void println();

    truth_t check_is_zero();

    bool compute_degree();
    slong get_degree(); 

    void copy(CaPoly & A);
    void set_coeff_ca(slong n, Ca& x);
    void set_si(slong x);
    void set_to_neg();
    bool set_to_rem(CaPoly & A, CaPoly & B);

    static void neg(CaPoly & minusA, CaPoly & A, CaCtx & ctx);
    static void add(CaPoly & sum, CaPoly & A, CaPoly & B, CaCtx & ctx);
    static void sub(CaPoly & difference, CaPoly & A, CaPoly & B, CaCtx & ctx);
    static void mul(CaPoly & product, CaPoly & A, CaPoly & B, CaCtx & ctx);
    static void pow(CaPoly & result, CaPoly & A, size_t n, CaCtx & ctx);
    static bool rem(CaPoly & R, CaPoly & A, CaPoly & B, CaCtx & ctx);
    static bool divrem(CaPoly & Q, CaPoly & R, CaPoly & A, CaPoly & B, CaCtx & ctx);
    static bool gcd(CaPoly & gcd, CaPoly & A, CaPoly & B, CaCtx & ctx);

    static void mul_polys(CaPoly & product, std::list<CaPoly *> & polys, CaCtx & ctx);
    static bool compute_gcd_of_polys(CaPoly & gcd, std::list<CaPoly *> & polys, CaCtx & ctx);

    // Signed pseudo remainder (why signed, if there is no sign?)
    static bool compute_prem(CaPoly & prem, CaPoly & P, CaPoly & Q, slong degQ, CaCtx & ctx);
};