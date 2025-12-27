#pragma once

#include <flint/ca_poly.h>
#include "ca_poly.hpp"
#include <vector>

class SRemS
{
private:
    std::vector<CaPoly*> sequence;
    size_t gcd_index;
public:
    SRemS(CaPoly & P, CaPoly & Q, CaCtx & ctx);
    ~SRemS();
    size_t get_gcd_index();
    void compute_gcd(CaPoly & gcd);
};