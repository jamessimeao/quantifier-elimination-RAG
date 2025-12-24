#pragma once

#include "ca_poly.hpp"
#include <list>

class BasicConstructible1D
{
private:
    std::list<CaPolyXX *> polys_to_annihilate;
    std::list<CaPolyXX *> polys_not_to_annihilate;
    CaCtxXX * ctxXX_ptr;

    bool polys_not_to_annihilate_has_zero {false};

    void compute_power_of_product_of_polys_not_to_annihilate(CaPolyXX & product, slong power);

public:
    BasicConstructible1D(CaCtxXX & ctxXX);
    void print_polys();
    void add_poly_to_annihilate(CaPolyXX & P);
    void add_poly_not_to_annihilate(CaPolyXX & Q);
    bool is_empty();
};