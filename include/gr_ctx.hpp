#pragma once

#include "flint/gr.h"

// Abstract class that is a wrapper for gr_ctx_t.
// It is abstract because there are multiple choice for initilization of a gr_ctx_t.
// A choice of initialization can be made in an implementation of the abstract class.

class GRCtx
{
protected:
    gr_ctx_t ctx;
public:
    virtual ~GRCtx() = 0; // make the destructor abstract, so the class has to be inherited
    gr_ctx_t & unwrap();
};