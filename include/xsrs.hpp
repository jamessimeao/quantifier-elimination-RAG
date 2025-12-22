#pragma once

#include <flint/ca_poly.h>
#include "ca_poly.hpp"
#include <vector>

class XSRemS
{
private:
    std::vector<std::tuple<CaPolyXX*, CaPolyXX*, CaPolyXX*>> sequence;
    size_t gcd_index;
public:
    XSRemS(CaPolyXX & P, CaPolyXX & Q, CaCtxXX & ctxXX);
    ~XSRemS();
    size_t get_gcd_index();
    CaPolyXX & gcd();
};