
// Interface for constraint functions
// S. Kluth 9/2012

#ifndef CONSTRAINTFUNCTION_HH
#define CONSTRAINTFUNCTION_HH

#include "TVectorD.h"

class ConstraintFunction {

public:

  virtual TVectorD calculate( const TVectorD&, const TVectorD& ) const = 0;

};


#endif
