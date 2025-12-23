#include <stdio.h>
#include <stdlib.h>

#include "../include/srs.hpp"
#include "../include/xsrs.hpp"

void test_SRemS()
{
    CaCtxXX ctxXX;

    CaXX one {ctxXX};
    CaXX two {ctxXX};
    CaXX minus_one {ctxXX};

    one.set_si(1);
    two.set_si(2);
    minus_one.set_si(-1);
    
    CaPolyXX P {ctxXX};
    CaPolyXX Q {ctxXX};
    P.set_name("P");
    Q.set_name("Q");
    
    // P = X^2 +2X +1
    P.set_coeff_ca(0, one);
    P.set_coeff_ca(1, two);
    P.set_coeff_ca(2, one);

    // Q = X^2 -1
    Q.set_coeff_ca(0, minus_one);
    Q.set_coeff_ca(2, one);

    // print P and Q
    P.println();
    Q.println();

    std::cout << "Computing SRemS" << std::endl;

    SRemS srs {P, Q, ctxXX};

    std::cout << "Print the gcd" << std::endl;

    CaPolyXX & gcd {srs.gcd()};
    gcd.println();

    std::cout << "Finished." << std::endl;
}

void test_XSRemS()
{
    CaCtxXX ctxXX;

    CaXX one {ctxXX};
    CaXX two {ctxXX};
    CaXX minus_one {ctxXX};

    one.set_si(1);
    two.set_si(2);
    minus_one.set_si(-1);
    
    CaPolyXX P {ctxXX};
    CaPolyXX Q {ctxXX};
    P.set_name("P");
    Q.set_name("Q");
    
    // P = X^2 +2X +1
    P.set_coeff_ca(0, one);
    P.set_coeff_ca(1, two);
    P.set_coeff_ca(2, one);

    // Q = X^2 -1
    Q.set_coeff_ca(0, minus_one);
    Q.set_coeff_ca(2, one);

    // print P and Q
    P.println();
    Q.println();

    std::cout << "Computing SRemS" << std::endl;

    // Extended signed remainder sequence
    XSRemS srs {P, Q, ctxXX};

    std::cout << "Print the gcd" << std::endl;

    CaPolyXX & gcd {srs.gcd()};
    gcd.println();

    std::cout << "Finished." << std::endl;
}

void testDegree()
{
CaCtxXX ctxXX;

    CaXX one {ctxXX};
    CaXX two {ctxXX};
    CaXX minus_one {ctxXX};

    one.set_si(1);
    two.set_si(2);
    minus_one.set_si(-1);
    
    CaPolyXX P {ctxXX};
    P.set_name("P");
    
    // P = X^2 +2X +1
    P.set_coeff_ca(0, one);
    P.set_coeff_ca(1, two);
    P.set_coeff_ca(2, one);
    CaXX zero {CaXX(ctxXX)};
    zero.set_si(0);
    P.set_coeff_ca(5, zero);

    bool result {P.compute_degree()};
    if(result)
    {
        std::cout << "degree = " << P.get_degree() << std::endl;
    }

}

int main()
{
    testDegree();
    return 0;
}