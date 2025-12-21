#include "../include/signed-remainder.hpp"

// It assumes that SRemS is an array big enough to store the signed remainder sequence.
// Code must be changed to allocate memory as needed.
int compute_signed_remainder_sequence(ca_poly_t * SRemS, ca_poly_t P, ca_poly_t Q, ca_ctx_t ctx)
{
    truth_t P_is_zero = ca_poly_check_is_zero(P, ctx);
    truth_t Q_is_zero = ca_poly_check_is_zero(Q, ctx);

    if(P_is_zero == T_UNKNOWN || Q_is_zero == T_UNKNOWN)
    {
        printf("Error in compute_signed_remainder_sequence couldn't check if P or Q is 0.");fflush(stdout);
        return -1;
    }

    if(P_is_zero == T_TRUE && Q_is_zero == T_TRUE)
    {
        printf("Error in compute_signed_remainder_sequence: both P and Q are 0.");fflush(stdout);
        return -1;
    }

    // Here we know if P and Q are 0 or not, and that not both are 0.

    // Empty SRemS
    //ca_poly_vec_set_length(SRemS,0,ctx); ca_poly_vec is incomplete

    // Add the first polynomial of SRemS, which is P
    //ca_poly_vec_append(SRemS, P, ctx); ca_poly_vec is incomplete
    ca_poly_set(SRemS[0], P, ctx);

    if(Q_is_zero == T_TRUE)
    {
        // return index of last non zero polynomial of the sequence
        return 0;
    }

    // Add the second polynomial of SRemS, which is Q
    //ca_poly_vec_append(SRemS, Q, ctx); ca_poly_vec is incomplete
    ca_poly_set(SRemS[1], Q, ctx);

    // Recursively add non zero signed remainders to SRemS.
    // Use a variable k to store the index of the last non zero polynomial in SRemS.
    // It will be returned by this function if there is no error.
    int k = 1;
    ca_poly_t signed_remainder;
    ca_poly_init(signed_remainder, ctx);
    while(1)
    {
        int success = ca_poly_rem(signed_remainder, SRemS[k-1], SRemS[k], ctx);
        if(!success)
        {
            printf("Error in compute_signed_remainder_sequence: failed to compute remainder.");fflush(stdout);
            k = -1;
            goto end;
        }

        truth_t zero_remainder = ca_poly_check_is_zero(signed_remainder, ctx);
        switch(zero_remainder)
        {
            case(T_UNKNOWN):
                printf("Error in compute_signed_remainder_sequence: failed to check if remainder is zero.");fflush(stdout);
                ca_poly_clear(signed_remainder, ctx);
                k = -1;
                goto end;

            case(T_FALSE):
                //ca_poly_vec_append(SRemS, remainder, ctx); ca_poly_vec is incomplete
                k++;
                // multiply the remainder by -1
                ca_poly_neg(signed_remainder, signed_remainder, ctx);
                // add the signed remainder to SRemS
                ca_poly_set(SRemS[k], signed_remainder, ctx);
                break;

            case(T_TRUE):
                goto end;
        }
    }
    end:
    ca_poly_clear(signed_remainder, ctx);
    // Return k.
    // If there was no error, k is the index of the last non zero polynomial in SRemS.
    // Otherwise, k = -1, which means there was an error.
    return k;
}