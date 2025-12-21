#pragma once

#include <flint/ca_poly.h>

// Computes the signed remainder sequence for P and Q and stores it in SRemS
int compute_signed_remainder_sequence(ca_poly_t * SRemS, ca_poly_t P, ca_poly_t Q, ca_ctx_t ctx);