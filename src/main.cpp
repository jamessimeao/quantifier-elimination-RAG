#include <stdio.h>
#include <stdlib.h>

#include "../include/signed-remainder.hpp"


/*
void test_SRemS()
{
    ca_ctx_t ctx;
    ca_ctx_init(ctx);

    ca_t one;
    ca_t two;
    ca_t minus_one;
    ca_init(one, ctx);
    ca_init(two, ctx);
    ca_init(minus_one, ctx);
    ca_one(one, ctx);
    // 2 = 1+1
    ca_add(two, one, one, ctx);
    // -1
    ca_neg_one(minus_one, ctx);

    ca_poly_t P;
    ca_poly_t Q;
    ca_poly_init(P, ctx);
    ca_poly_init(Q, ctx);
    
    // P = X^2 +2X +1
    ca_poly_set_coeff_ca(P, 0, one, ctx);
    ca_poly_set_coeff_ca(P, 1, two, ctx);
    ca_poly_set_coeff_ca(P, 2, one, ctx);
    // Q = X^2 -1
    ca_poly_set_coeff_ca(Q, 0, minus_one, ctx);
    ca_poly_set_coeff_ca(Q, 2, one, ctx);

    // print P and Q
    ca_poly_print(P, ctx);
    ca_poly_print(Q, ctx);

    size_t max_length = 10;
    ca_poly_t * SRemS = (ca_poly_t *) malloc(max_length*sizeof(ca_poly_t));
    int k = compute_signed_remainder_sequence(SRemS, P, Q, ctx);

    if(k >= 0)
    {
        ca_poly_t gcd;
        ca_poly_init(gcd, ctx);
        
        ca_poly_set(gcd, SRemS[k], ctx);
        // result should be X +1 multiplied by a non zero constant
        ca_poly_print(gcd, ctx);

        ca_poly_clear(gcd, ctx);
    }

    // Clearing
    printf("Clearing...\n");fflush(stdout);
    ca_poly_clear(SRemS[0],ctx);
    ca_poly_clear(SRemS[1],ctx);
    ca_poly_clear(SRemS[2],ctx);
    free(SRemS);

    ca_poly_clear(P, ctx);
    ca_poly_clear(Q, ctx);
    ca_clear(one, ctx);
    ca_clear(two, ctx);
    ca_ctx_clear(ctx);

    printf("Finished.\n");fflush(stdout);
}
*/

#include "../include/poly.hpp"

int main()
{
    CtxXX ctxXX;

    CaXX x = CaXX(ctxXX);
    x.set_si(5);
    x.println();

    PolyXX P = PolyXX(ctxXX);
    P.set_coeff(0,x);
    P.set_coeff(3,x);
    P.println();

    return 0;
}