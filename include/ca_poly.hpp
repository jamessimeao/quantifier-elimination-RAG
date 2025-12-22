#pragma once

#include "flint/ca_poly.h"
#include "../include/ca.hpp"

// C++ wrapper for ca_poly_t
class CaPolyXX
{
private:
    ca_poly_t poly;
    CaCtxXX * ctxXX_ptr;
    ca_ctx_t & ctx();
    std::string name;
public:
    CaPolyXX(CaCtxXX & ctxXX);
    CaPolyXX(CaPolyXX & P);
    ~CaPolyXX();
    ca_poly_t & unwrap();
    void set_name(std::string_view new_name);
    void println();
    void set_coeff_ca(slong n, CaXX& x);
    void set_si(slong x);
    void set_to_neg();
    bool set_to_rem(CaPolyXX & A, CaPolyXX & B);
    static void neg(CaPolyXX minusA, CaPolyXX A, CaCtxXX ctxXX);
    static void add(CaPolyXX sum, CaPolyXX A, CaPolyXX B, CaCtxXX & ctxXX);
    static void sub(CaPolyXX difference, CaPolyXX A, CaPolyXX B, CaCtxXX & ctxXX);
    static void mul(CaPolyXX product, CaPolyXX A, CaPolyXX B, CaCtxXX & ctxXX);
    static bool rem(CaPolyXX & R, CaPolyXX & A, CaPolyXX & B, CaCtxXX & ctxXX);
    static bool divrem(CaPolyXX & Q, CaPolyXX & R, CaPolyXX & A, CaPolyXX & B, CaCtxXX & ctxXX);
    truth_t check_is_zero();
};