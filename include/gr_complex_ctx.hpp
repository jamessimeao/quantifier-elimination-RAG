#pragma once

#include "gr_ctx.hpp"

// Wrapper class for gr_ctx_t initilized as complex numbers as implemented by Calcium.

class GRComplexCtx : public GRCtx
{
public:
    GRComplexCtx();
    ~GRComplexCtx();
};