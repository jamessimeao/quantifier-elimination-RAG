#include "../include/srems.hpp"

SRemS::SRemS(CaPolyXX & P, CaPolyXX & Q, CaCtxXX & ctxXX)
{
    truth_t P_is_zero = P.check_is_zero();
    truth_t Q_is_zero = Q.check_is_zero();

    if(P_is_zero == T_UNKNOWN || Q_is_zero == T_UNKNOWN)
    {
        throw std::runtime_error("Error in compute_signed_remainder_sequence: couldn't check if P or Q is 0.\n");
    }

    if(P_is_zero == T_TRUE && Q_is_zero == T_TRUE)
    {
        throw std::runtime_error("Error in compute_signed_remainder_sequence: both P and Q are 0.\n");
    }

    // Here we know if P and Q are 0 or not, and that not both are 0.

    // Empty the signed remainder sequence
    sequence.clear();

    // Add the first polynomial of SRemS, which is P
    std::cout << "push_back" << std::endl;
    CaPolyXX * P_copy_ptr = new CaPolyXX(P);
    P_copy_ptr->set_name("SRemS_" + std::to_string(0));
    sequence.push_back(P_copy_ptr);

    if(Q_is_zero == T_TRUE)
    {
        // return index of last non zero polynomial of the sequence
        last_index = 0;
        return;
    }

    // Add the second polynomial of SRemS, which is Q
    std::cout << "push_back" << std::endl;
    CaPolyXX * Q_copy_ptr = new CaPolyXX(Q);
    Q_copy_ptr->set_name("SRemS_" + std::to_string(1));
    sequence.push_back(Q_copy_ptr);

    // Recursively add non zero signed remainders to SRemS.
    // Use a variable k to store the index of the last non zero polynomial in SRemS.
    // It will be returned by this function if there is no error.
    last_index = 1;

    CaPolyXX signed_remainder = CaPolyXX(ctxXX);
    signed_remainder.set_name("signed_remainder");
    std::cout << "Entering while loop" << std::endl;
    while(true)
    {
        std::cout << "Computing remainder" << std::endl;
        bool success = signed_remainder.set_to_rem(*sequence[last_index-1], *sequence[last_index]);
        if(!success)
        {
            throw std::runtime_error("Error in compute_signed_remainder_sequence: failed to compute remainder.\n");
        }

        truth_t zero_remainder = signed_remainder.check_is_zero();
        std::cout << "Switch case" << std::endl;
        // multiply the remainder by -1
        signed_remainder.set_to_neg();
        CaPolyXX * signed_remainder_copy_ptr = new CaPolyXX(signed_remainder);
        switch(zero_remainder)
        {
            case(T_UNKNOWN):
                throw std::runtime_error("Error in compute_signed_remainder_sequence: failed to check if remainder is zero.\n");

            case(T_FALSE):
                last_index++;
                // add the signed remainder to SRemS
                signed_remainder_copy_ptr->set_name("SRemS_" + std::to_string(last_index));
                sequence.push_back(signed_remainder_copy_ptr);
                break;

            case(T_TRUE):
                return;
        }
    }
}

SRemS::~SRemS()
{
    std::cout << "Destructing SRemS...\n";
    for(CaPolyXX * poly_ptr : sequence)
    {
        poly_ptr->~CaPolyXX();
    }
    std::cout << "Finished destructing SRemS\n";
}

size_t SRemS::get_last_index()
{
    return last_index;
}

CaPolyXX & SRemS::gcd()
{
    return *sequence[last_index];
}