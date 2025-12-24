#include "../include/basic_constructible_1d.hpp"

BasicConstructible1D::BasicConstructible1D(CaCtxXX & ctxXX)
{
    ctxXX_ptr = &ctxXX;
}

BasicConstructible1D::~BasicConstructible1D()
{
    destruct_polys(polys_to_annihilate);
    destruct_polys(polys_not_to_annihilate);
}

void BasicConstructible1D::destruct_polys(std::list<CaPolyXX *> & polys)
{
    for(CaPolyXX * poly_ptr : polys)
    {
        poly_ptr->~CaPolyXX();
    }
}

void BasicConstructible1D::print_polys()
{
    std::cout << "Polynomials to annihilate:\n";
    for(CaPolyXX * poly_ptr : polys_to_annihilate)
    {
        poly_ptr->println();
    }

    std::cout << "Polynomials not to annihilate:\n";
    for(CaPolyXX * poly_ptr : polys_not_to_annihilate)
    {
        poly_ptr->println();
    }
}

void BasicConstructible1D::add_poly_to_annihilate(CaPolyXX & P)
{
    // only add non zero polynomials
    truth_t is_zero {P.check_is_zero()};
    CaPolyXX * P_copy_ptr {new CaPolyXX(P)};
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

void BasicConstructible1D::add_poly_not_to_annihilate(CaPolyXX & Q)
{
    // If Q is zero, only store the zero polynomial
    truth_t is_zero {Q.check_is_zero()};
    CaPolyXX * Q_copy_ptr {new CaPolyXX(Q)};
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

void BasicConstructible1D::compute_power_of_product_of_polys_not_to_annihilate(CaPolyXX & product, slong power)
{
    // First take the product of all polynomials in polys_not_to_annihilate
    CaPolyXX::mul_polys(product, polys_not_to_annihilate, *ctxXX_ptr);
    // Then take the power
    CaPolyXX::pow(product, product, power, *ctxXX_ptr);
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

    CaPolyXX gcd_bigger_degree {*ctxXX_ptr};
    bool successful {CaPolyXX::compute_gcd_of_polys(gcd_bigger_degree, polys_to_annihilate, *ctxXX_ptr)};
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

    CaPolyXX product {*ctxXX_ptr};
    compute_power_of_product_of_polys_not_to_annihilate(product, d);

    CaPolyXX gcd_smaller_degree {*ctxXX_ptr};
    successful = CaPolyXX::gcd(gcd_smaller_degree, gcd_bigger_degree, product, *ctxXX_ptr);
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