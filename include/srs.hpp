#pragma once

#include <flint/ca_poly.h>
#include "ca_poly.hpp"
#include <vector>

class SRemS
{
private:
    std::vector<CaPolyXX*> sequence;
    size_t gcd_index;
public:
    SRemS(CaPolyXX & P, CaPolyXX & Q, CaCtxXX & ctxXX);
    ~SRemS();
    size_t get_gcd_index();
    void compute_gcd(CaPolyXX & gcd);
};