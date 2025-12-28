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
