#include "../include/basic_constructible_1d.hpp"

BasicConstructible1D::BasicConstructible1D(CaCtx & ctx)
{
    ctx_ptr = &ctx;
}

BasicConstructible1D::~BasicConstructible1D()
{
    destruct_polys(polys_to_annihilate);
    destruct_polys(polys_not_to_annihilate);
}

void BasicConstructible1D::destruct_polys(std::list<CaPoly *> & polys)
{
    for(CaPoly * poly_ptr : polys)
    {
        poly_ptr->~CaPoly();
    }
}

void BasicConstructible1D::print_polys()
{
    std::cout << "Polynomials to annihilate:\n";
    for(CaPoly * poly_ptr : polys_to_annihilate)
    {
        poly_ptr->println();
    }

    std::cout << "Polynomials not to annihilate:\n";
    for(CaPoly * poly_ptr : polys_not_to_annihilate)
    {
        poly_ptr->println();
    }
}

void BasicConstructible1D::add_poly_to_annihilate(CaPoly & P)
{
    // only add non zero polynomials
    truth_t is_zero {P.check_is_zero()};
    CaPoly * P_copy_ptr {new CaPoly(P)};
    switch(is_zero)
    {
        case T_UNKNOWN:
            throw std::runtime_error("Error: Failed to check if polynomial is zero in add_poly_to_annihilate.\n");
        case T_FALSE:
            polys_to_annihilate.push_back(P_copy_ptr);
            break;
        case T_TRUE:
            std::cout << "Won't add zero polynomial to polynomials to annihilate\n";
            break;
    }
    
}

void BasicConstructible1D::add_poly_not_to_annihilate(CaPoly & Q)
{
    // If Q is zero, only store the zero polynomial
    truth_t is_zero {Q.check_is_zero()};
    CaPoly * Q_copy_ptr {new CaPoly(Q)};
    switch(is_zero)
    {
        case T_UNKNOWN:
            throw std::runtime_error("Error: Failed to check if polynomial is zero in add_poly_not_to_annihilate.\n");
        case T_FALSE:
            polys_to_annihilate.push_back(Q_copy_ptr);
            break;
        case T_TRUE:
            std::cout << "Adding a zero polynomial in add_poly_not_to_annihilate. Will only keep the zero polynomial.\n";
            if(!polys_not_to_annihilate_has_zero)
            {
                polys_not_to_annihilate_has_zero = true;
                destruct_polys(polys_not_to_annihilate);
                polys_not_to_annihilate.clear();
                polys_not_to_annihilate.push_back(Q_copy_ptr);
            }
            break;
    }
}

void BasicConstructible1D::compute_power_of_product_of_polys_not_to_annihilate(CaPoly & product, slong power)
{
    // First take the product of all polynomials in polys_not_to_annihilate
    CaPoly::mul_polys(product, polys_not_to_annihilate, *ctx_ptr);
    // Then take the power
    CaPoly::pow(product, product, power, *ctx_ptr);
}

bool BasicConstructible1D::is_empty()
{
    // Degerate cases first
    if(polys_not_to_annihilate_has_zero)
    {
        return true;
    }

    // polys_not_to_annihilate_has_zero = false
    if(polys_to_annihilate.size() == 0)
    {
        return false;
    }

    // Now we have
    // polys_not_to_annihilate_has_zero = false,
    // polys_to_annihilate.size() > 0, without zero polynomials.
    // This guarantees that all gcds below exist and are not 0.

    CaPoly gcd_bigger_degree {*ctx_ptr};
    bool successful {CaPoly::compute_gcd_of_polys(gcd_bigger_degree, polys_to_annihilate, *ctx_ptr)};
    if(!successful)
    {
        throw std::runtime_error("Error: Failed to compute gcd of polynomials that shouldn't be annihilated.\n");
    }

    successful = gcd_bigger_degree.compute_degree();
    if(!successful)
    {
        throw std::runtime_error("Error: gcd of bigger degree isn't proper, won't compute its degree.\n");
    }
    slong bigger_degree {gcd_bigger_degree.get_degree()};
    slong d {bigger_degree + 1};

    CaPoly product {*ctx_ptr};
    compute_power_of_product_of_polys_not_to_annihilate(product, d);

    CaPoly gcd_smaller_degree {*ctx_ptr};
    successful = CaPoly::gcd(gcd_smaller_degree, gcd_bigger_degree, product, *ctx_ptr);
    if(!successful)
    {
        throw std::runtime_error("Error: couldn't compute the gcd of smaller degree.\n");
    }

    successful = gcd_smaller_degree.compute_degree();
    if(!successful)
    {
        throw std::runtime_error("Error: gcd of smaller degree isn't proper, won't compute its degree.\n");
    }
    slong smaller_degree {gcd_smaller_degree.get_degree()};

    return smaller_degree == bigger_degree;
}