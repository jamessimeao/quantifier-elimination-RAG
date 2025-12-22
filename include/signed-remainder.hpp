#pragma once

#include <flint/ca_poly.h>
#include "poly.hpp"
#include <vector>

class SRemS
{
private:
    std::vector<PolyXX*> sequence;
    size_t last_index;
public:
    SRemS(PolyXX & P, PolyXX & Q, CtxXX & ctxXX);
    ~SRemS();
    size_t get_last_index();
    PolyXX & gcd();
};