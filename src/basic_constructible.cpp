#include "../include/basic_constructible.hpp"

BasicConstructible::BasicConstructible(CaCtxXX & ctxXX)
{
    ctxXX_ptr = &ctxXX;
}

void BasicConstructible::print_polys()
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

void BasicConstructible::add_poly_to_annihilate(CaPolyXX & P)
{
    polys_to_annihilate.push_back(&P);
}

void BasicConstructible::add_poly_not_to_annihilate(CaPolyXX & Q)
{
    polys_to_annihilate.push_back(&Q);
}

void BasicConstructible::compute_power_of_product_of_polys_not_to_annihilate(CaPolyXX & product, slong power)
{
    // First take the product of all polynomials in polys_not_to_annihilate
    CaPolyXX::mul_polys(product, polys_not_to_annihilate, *ctxXX_ptr);
    // Then take the power
    CaPolyXX::pow(product, product, power, *ctxXX_ptr);
}

bool BasicConstructible::is_empty()
{
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