#include "../include/complex_mpoly.hpp"

ComplexMPoly::ComplexMPoly(ComplexMPolyCtx & ctx)
{
    ctx_ptr = &ctx;
    gr_mpoly_init(poly, ctx.unwrap());
}

ComplexMPoly::~ComplexMPoly()
{
    gr_mpoly_clear(poly, ctx_ptr->unwrap());
}

gr_mpoly_t & ComplexMPoly::unwrap()
{
    return poly;
}

gr_srcptr ComplexMPoly::unwrap_gr()
{
    return poly;
}

void ComplexMPoly::println()
{
    gr_mpoly_print_pretty(poly, ctx_ptr->unwrap());
    std::cout << "\n";
}

bool ComplexMPoly::set_coeff_si(slong c, ulong * exp)
{
    return gr_mpoly_set_coeff_si_ui(poly, c, exp, ctx_ptr->unwrap()) == 0;
}

bool ComplexMPoly::set_coeff_scalar(GR & c, const ulong * exp)
{
    return gr_mpoly_set_coeff_scalar_ui(poly, c.unwrap_gr(), exp, ctx_ptr->unwrap()) == 0;
}

bool ComplexMPoly::neg(ComplexMPoly & minusPoly, ComplexMPoly & poly, ComplexMPolyCtx & ctx)
{
    return gr_mpoly_neg(minusPoly.unwrap(), poly.unwrap(), ctx.unwrap()) == 0;
}

bool ComplexMPoly::add(ComplexMPoly & sum, ComplexMPoly & poly1, ComplexMPoly & poly2, ComplexMPolyCtx & ctx)
{
    return gr_mpoly_add(sum.unwrap(), poly1.unwrap(), poly2.unwrap(), ctx.unwrap()) == 0;
}

bool ComplexMPoly::sub(ComplexMPoly & difference, ComplexMPoly & poly1, ComplexMPoly & poly2, ComplexMPolyCtx & ctx)
{
    return gr_mpoly_sub(difference.unwrap(), poly1.unwrap(), poly2.unwrap(), ctx.unwrap()) == 0;
}

bool ComplexMPoly::mul(ComplexMPoly & product, ComplexMPoly & poly1, ComplexMPoly & poly2, ComplexMPolyCtx & ctx)
{
    return gr_mpoly_mul(product.unwrap(), poly1.unwrap(), poly2.unwrap(), ctx.unwrap()) == 0;
}