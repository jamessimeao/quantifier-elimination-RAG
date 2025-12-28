#pragma once

#include "gr_ctx.hpp"

// Abstract class that is a wrapper for gr_srcptr.
// It represents an element of the ring encoded by a gr_ctx_t.

class GR
{
public:
    virtual gr_srcptr unwrap_gr() = 0;
};