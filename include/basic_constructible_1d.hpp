#pragma once

#include "ca_poly.hpp"
#include <list>

class BasicConstructible1D
{
private:
    std::list<CaPoly *> polys_to_annihilate;
    std::list<CaPoly *> polys_not_to_annihilate;
    CaCtx * ctx_ptr;

    bool polys_not_to_annihilate_has_zero {false};

    void destruct_polys(std::list<CaPoly *> & polys);

    void compute_power_of_product_of_polys_not_to_annihilate(CaPoly & product, slong power);

public:
    BasicConstructible1D(CaCtx & ctx);
    ~BasicConstructible1D();
    void print_polys();
    void add_poly_to_annihilate(CaPoly & P);
    void add_poly_not_to_annihilate(CaPoly & Q);
    bool is_empty();
};