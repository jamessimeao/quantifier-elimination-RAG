#include <stdio.h>
#include <stdlib.h>


#include "../include/srs.hpp"
#include "../include/xsrs.hpp"
#include "../include/basic_constructible_1d.hpp"
#include "../include/complex_mpoly.hpp"
#include "../include/gr_complex_ctx.hpp"

void test_SRemS()
{
    CaCtx ctx;

    Ca one {ctx};
    Ca two {ctx};
    Ca minus_one {ctx};

    one.set_si(1);
    two.set_si(2);
    minus_one.set_si(-1);
    
    CaPoly P {ctx};
    CaPoly Q {ctx};
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

    SRemS srs {P, Q, ctx};

    std::cout << "Print the gcd" << std::endl;

    CaPoly gcd {ctx};
    srs.compute_gcd(gcd);
    gcd.set_name("gcd");
    gcd.println();

    std::cout << "Finished." << std::endl;
}

void test_XSRemS()
{
    CaCtx ctx;

    Ca one {ctx};
    Ca two {ctx};
    Ca minus_one {ctx};

    one.set_si(1);
    two.set_si(2);
    minus_one.set_si(-1);
    
    CaPoly P {ctx};
    CaPoly Q {ctx};
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
    XSRemS xsrs {P, Q, ctx};

    std::cout << "Print the gcd" << std::endl;

    CaPoly gcd {ctx};
    xsrs.compute_gcd(gcd);
    gcd.set_name("gcd");
    gcd.println();

    CaPoly mdc {ctx};
    xsrs.compute_mdc(mdc);
    mdc.set_name("mdc");
    mdc.println();

    std::cout << "Finished." << std::endl;
}

void testDegree()
{
    CaCtx ctx;

    Ca one {ctx};
    Ca two {ctx};
    Ca minus_one {ctx};

    one.set_si(1);
    two.set_si(2);
    minus_one.set_si(-1);
    
    CaPoly P {ctx};
    P.set_name("P");
    
    // P = X^2 +2X +1
    P.set_coeff_ca(0, one);
    P.set_coeff_ca(1, two);
    P.set_coeff_ca(2, one);
    Ca zero {Ca(ctx)};
    zero.set_si(0);
    P.set_coeff_ca(5, zero);

    bool result {P.compute_degree()};
    if(result)
    {
        std::cout << "degree = " << P.get_degree() << std::endl;
    }

}

void testBasicConstructible1D()
{
    CaCtx ctx;

    Ca one {ctx};
    Ca two {ctx};
    Ca minus_one {ctx};

    one.set_si(1);
    two.set_si(2);
    minus_one.set_si(-1);
    
    CaPoly P {ctx};
    CaPoly Q {ctx};
    P.set_name("P");
    Q.set_name("Q");
    
    // P = X^2 +2X +1
    P.set_coeff_ca(0, one);
    P.set_coeff_ca(1, two);
    P.set_coeff_ca(2, one);

    // Q = X^2 -1
    Q.set_coeff_ca(0, minus_one);
    Q.set_coeff_ca(2, one);

    BasicConstructible1D bc {ctx};
    bc.add_poly_to_annihilate(P);
    bc.add_poly_not_to_annihilate(Q);

    std::cout << std::boolalpha;
    bool empty {bc.is_empty()};
    std::cout << "Empty: " << empty << std::endl;
}

void testComplexMPoly()
{
    // Complex numbers
    GRComplexCtx CC {};
    // Complex Polynomials with 2 variables
    ComplexMPolyCtx ctx  = ComplexMPolyCtx(CC, 2);
    // A complex polynomial with 2 variables
    ComplexMPoly P {ctx};
    // Set P to 3 * x1^5 * x2^7
    ulong exp[] = {5,7};
    bool success;
    success = P.set_coeff_si(3,exp);
    if(!success)
    {
        throw std::runtime_error("Failed to set coeff.");
    }
    // Print the polynomial
    P.println();
}

int main()
{
    testComplexMPoly();

    return 0;
}