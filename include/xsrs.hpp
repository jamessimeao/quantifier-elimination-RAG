#pragma once

#include <flint/ca_poly.h>
#include "ca_poly.hpp"
#include <vector>

class XSRemS
{
private:
    CaCtx * ctx_ptr;
    std::vector<std::tuple<CaPoly*, CaPoly*, CaPoly*>> sequence;
    size_t gcd_index;

public:
    XSRemS(CaPoly & P, CaPoly & Q, CaCtx & ctx);
    ~XSRemS();
    size_t get_gcd_index();
    void compute_gcd(CaPoly & gcd);
    void compute_mdc(CaPoly & mdc);
};