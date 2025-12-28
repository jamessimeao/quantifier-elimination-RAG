#include "../include/gr_poly.hpp"

GRPoly::GRPoly(GRCtx & ctx)
{
    ctx_ptr = &ctx;
    gr_poly_init(poly, ctx.unwrap_gr());
}

GRPoly::~GRPoly()
{
    gr_poly_clear(poly, ctx_ptr->unwrap_gr());
}

gr_poly_t & GRPoly::unwrap()
{
    return poly;
}

void GRPoly::println()
{
    gr_poly_print(poly, ctx_ptr->unwrap_gr());
    std::cout << "\n";
}

bool GRPoly::set_coeff_si(slong exp, slong x)
{
    return gr_poly_set_coeff_si(poly, exp, x, ctx_ptr->unwrap_gr()) == 0; 
}

bool GRPoly::set_coeff_scalar(slong exp, GR & x)
{
    return gr_poly_set_coeff_scalar(poly, exp, x.unwrap_gr(), ctx_ptr->unwrap_gr());
}