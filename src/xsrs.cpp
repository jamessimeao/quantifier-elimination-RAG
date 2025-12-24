#include "../include/xsrs.hpp"

XSRemS::XSRemS(CaPolyXX & P, CaPolyXX & Q, CaCtxXX & ctxXX)
{
    ctxXX_ptr = &ctxXX;

    truth_t P_is_zero {P.check_is_zero()};
    truth_t Q_is_zero {Q.check_is_zero()};

    if(P_is_zero == T_UNKNOWN || Q_is_zero == T_UNKNOWN)
    {
        throw std::runtime_error("Error in XSRemS constructor: couldn't check if P or Q is 0.\n");
    }

    if(P_is_zero == T_TRUE && Q_is_zero == T_TRUE)
    {
        throw std::runtime_error("Error in XSRemS constructor: both P and Q are 0.\n");
    }

    // Here we know if P and Q are 0 or not, and that not both are 0.

    // Empty the signed remainder sequence
    sequence.clear();

    // Add the first polynomial of SRemS, which is P
    std::cout << "push_back" << std::endl;
    CaPolyXX * P_copy_ptr {new CaPolyXX(P)};
    P_copy_ptr->set_name("SRemS_" + std::to_string(0));
    CaPolyXX * U0_ptr {new CaPolyXX(ctxXX)};
    U0_ptr->set_si(1);
    CaPolyXX * V0_ptr {new CaPolyXX(ctxXX)};
    V0_ptr->set_si(0);
    sequence.push_back(std::make_tuple(P_copy_ptr,U0_ptr,V0_ptr));

    if(Q_is_zero == T_TRUE)
    {
        // return index of last non zero polynomial of the sequence
        gcd_index = 0;
        return;
    }

    // Add the second polynomial of SRemS, which is Q
    std::cout << "push_back" << std::endl;
    CaPolyXX * Q_copy_ptr {new CaPolyXX(Q)};
    Q_copy_ptr->set_name("SRemS_" + std::to_string(1));
    CaPolyXX * U1_ptr {new CaPolyXX(ctxXX)};
    U1_ptr->set_si(0);
    CaPolyXX * V1_ptr {new CaPolyXX(ctxXX)};
    V1_ptr->set_si(1);
    sequence.push_back(std::make_tuple(Q_copy_ptr,U1_ptr,V1_ptr));

    // Recursively add non zero signed remainders to SRemS.
    // Use a variable k to store the index of the last non zero polynomial in SRemS.
    // It will be returned by this function if there is no error.
    size_t i {1};

    CaPolyXX quotient {ctxXX};
    quotient.set_name("quotient");
    CaPolyXX signed_remainder {ctxXX};
    signed_remainder.set_name("signed_remainder");
    truth_t zero_remainder;
    std::tuple<CaPolyXX *, CaPolyXX *, CaPolyXX *> tuple;
    std::cout << "Entering while loop" << std::endl;
    while(true)
    {
        std::cout << "Computing remainder" << std::endl;
        CaPolyXX * SRemS_i_minus_1_ptr = std::get<0>(sequence[i-1]);
        CaPolyXX * SRemS_i_ptr = std::get<0>(sequence[i]);
        bool success = CaPolyXX::divrem(quotient, signed_remainder,*SRemS_i_minus_1_ptr, *SRemS_i_ptr, ctxXX);
        if(!success)
        {
            throw std::runtime_error("Error in XSRemS constructor: failed to compute remainder.\n");
        }
        
        CaPolyXX * U_i_minus_1_ptr = std::get<1>(sequence[i-1]);
        CaPolyXX * U_i_ptr = std::get<1>(sequence[i]);
        CaPolyXX * V_i_minus_1_ptr = std::get<2>(sequence[i-1]);
        CaPolyXX * V_i_ptr = std::get<2>(sequence[i]);

        zero_remainder = signed_remainder.check_is_zero();
        // multiply the remainder by -1
        signed_remainder.set_to_neg();
        CaPolyXX * signed_remainder_copy_ptr = new CaPolyXX(signed_remainder);

        std::cout << "Computing U..." << std::endl;
        // U[i+1] = quotient*U[i] -U[i-1]
        CaPolyXX * U_ptr {new CaPolyXX(ctxXX)};
        std::cout << "Multiplying polynomials" << std::endl; 
        CaPolyXX::mul(*U_ptr, quotient, *U_i_ptr, ctxXX);
        std::cout << "Subtracting polynomials" << std::endl;
        CaPolyXX::sub(*U_ptr, *U_ptr, *U_i_minus_1_ptr, ctxXX);

        std::cout << "Computing V..." << std::endl;
        // V[i+1] = quotient*V[i] -V[i-1]
        CaPolyXX * V_ptr {new CaPolyXX(ctxXX)};
        CaPolyXX::mul(*V_ptr, quotient, *V_i_ptr, ctxXX);
        CaPolyXX::sub(*V_ptr, *V_ptr, *V_i_minus_1_ptr, ctxXX);

        // Make the tuple that will be stored in the extended signed remainder sequence
        tuple = std::make_tuple(signed_remainder_copy_ptr, U_ptr, V_ptr);

        std::cout << "Switch case" << std::endl;
        switch(zero_remainder)
        {
            case(T_UNKNOWN):
                throw std::runtime_error("Error in XSRemS constructor: failed to check if remainder is zero.\n");

            case(T_FALSE):
                i++;
                // add the signed remainder, U and V to the sequence
                signed_remainder_copy_ptr->set_name("SRemS_" + std::to_string(i));
                sequence.push_back(tuple);
                break;

            case(T_TRUE):
                // Store the index of the GCD, which is the index of the last non zero remainder
                gcd_index = i;
                i++;
                // add the signed remainder, U and V to the sequence
                signed_remainder_copy_ptr->set_name("SRemS_" + std::to_string(i));
                sequence.push_back(tuple);
                return;
        }
    }
}

XSRemS::~XSRemS()
{
    std::cout << "Destructing XSRemS...\n";
    for(std::tuple<CaPolyXX *, CaPolyXX *, CaPolyXX *> & tuple : sequence)
    {
        // Can't just use a for loop here, without some workaround
        std::get<0>(tuple)->~CaPolyXX();
        std::get<1>(tuple)->~CaPolyXX();
        std::get<2>(tuple)->~CaPolyXX();
    }
    std::cout << "Finished destructing XSRemS\n";
}

size_t XSRemS::get_gcd_index()
{
    return gcd_index;
}

CaPolyXX & XSRemS::gcd()
{
    CaPolyXX * gcd_ptr {std::get<0>(sequence[gcd_index])};
    return *gcd_ptr;
}

void XSRemS::compute_mdc(CaPolyXX & mdc)
{
    // U[k+1]P = -V[k+1]Q, and both sides are an mdc of P and Q.
    // Here k is the index of the gcd.
    // I'll use U[k+1]P.
    CaPolyXX * P_ptr {std::get<0>(sequence[0])};
    CaPolyXX * U_ptr {std::get<1>(sequence[gcd_index+1])};
    CaPolyXX::mul(mdc, *U_ptr, *P_ptr, *ctxXX_ptr);
}