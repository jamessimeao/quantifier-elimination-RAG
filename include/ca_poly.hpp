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
    void set_coeff(slong n, CaXX& x);
    void set_to_neg();
    bool set_to_rem(CaPolyXX & A, CaPolyXX & B);
    truth_t check_is_zero();
};