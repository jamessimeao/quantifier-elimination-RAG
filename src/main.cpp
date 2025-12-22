#include <stdio.h>
#include <stdlib.h>

#include "../include/signed-remainder.hpp"

void test_SRemS()
{
    CaCtxXX ctxXX;

    CaXX one = CaXX(ctxXX);
    CaXX two = CaXX(ctxXX);
    CaXX minus_one = CaXX(ctxXX);

    one.set_si(1);
    two.set_si(2);
    minus_one.set_si(-1);
    
    CaPolyXX P = CaPolyXX(ctxXX);
    CaPolyXX Q = CaPolyXX(ctxXX);
    P.set_name("P");
    Q.set_name("Q");
    
    // P = X^2 +2X +1
    P.set_coeff(0, one);
    P.set_coeff(1, two);
    P.set_coeff(2, one);

    // Q = X^2 -1
    Q.set_coeff(0, minus_one);
    Q.set_coeff(2, one);

    // print P and Q
    P.println();
    Q.println();

    std::cout << "Computing SRemS" << std::endl;

    SRemS srs = SRemS(P, Q, ctxXX);

    std::cout << "Print the gcd" << std::endl;

    CaPolyXX & gcd = srs.gcd();
    gcd.println();

    std::cout << "Finished." << std::endl;
}

int main()
{
    test_SRemS();
    return 0;
}