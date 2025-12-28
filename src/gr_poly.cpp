#include "../include/gr_poly.hpp"

GRPoly::GRPoly(GRCtx & ctx)
{
    ctx_ptr = &ctx;
    gr_poly_init(poly, ctx.unwrap());
}

GRPoly::~GRPoly()
{
    gr_poly_clear(poly, ctx_ptr->unwrap());
}

gr_poly_t & GRPoly::unwrap()
{
    return poly;
}

void GRPoly::println()
{
    gr_poly_print(poly, ctx_ptr->unwrap());
    std::cout << "\n";
}

bool GRPoly::set_coeff(slong exp, slong x)
{
    return gr_poly_set_coeff_si(poly, exp, x, ctx_ptr->unwrap()) == 0; 
}