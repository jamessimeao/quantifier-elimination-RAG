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

bool GRPoly::println()
{
    bool res {gr_poly_print(poly, ctx_ptr->unwrap_gr()) == 0};
    std::cout << "\n";
    return res;
}

bool GRPoly::set_coeff_si(slong exp, slong x)
{
    return gr_poly_set_coeff_si(poly, exp, x, ctx_ptr->unwrap_gr()) == 0; 
}

bool GRPoly::set_coeff_scalar(slong exp, GR & x)
{
    return gr_poly_set_coeff_scalar(poly, exp, x.unwrap_gr(), ctx_ptr->unwrap_gr()) == 0;
}

bool GRPoly::neg(GRPoly & minusPoly, GRPoly & poly, GRCtx & ctx)
{
    return gr_poly_neg(minusPoly.unwrap(), poly.unwrap(), ctx.unwrap_gr()) == 0;
}

bool GRPoly::add(GRPoly & sum, GRPoly & poly1, GRPoly & poly2, GRCtx & ctx)
{
    return gr_poly_add(sum.unwrap(), poly1.unwrap(), poly2.unwrap(), ctx.unwrap_gr()) == 0;
}

bool GRPoly::sub(GRPoly & difference, GRPoly & poly1, GRPoly & poly2, GRCtx & ctx)
{
    return gr_poly_sub(difference.unwrap(), poly1.unwrap(), poly2.unwrap(), ctx.unwrap_gr()) == 0;
}

bool GRPoly::mul(GRPoly & product, GRPoly & poly1, GRPoly & poly2, GRCtx & ctx)
{
    return gr_poly_mul(product.unwrap(), poly1.unwrap(), poly2.unwrap(), ctx.unwrap_gr()) == 0;
}