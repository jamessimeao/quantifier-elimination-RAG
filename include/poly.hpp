#pragma once

#include "flint/ca_poly.h"
#include "../include/ctx.hpp"
#include "../include/ca.hpp"

// C++ wrapper for ca_poly_t
class PolyXX
{
private:
    ca_poly_t poly;
    CtxXX * ctxXX_ptr;
    ca_ctx_t * ctx_ptr();
    std::string name;
public:
    PolyXX(CtxXX & ctxXX);
    PolyXX(PolyXX & P);
    ~PolyXX();
    void set_name(std::string_view new_name);
    void println();
    void set_coeff(slong n, CaXX& x);
    void set_to_neg();
    bool set_to_rem(PolyXX & A, PolyXX & B);
    truth_t check_is_zero();
};