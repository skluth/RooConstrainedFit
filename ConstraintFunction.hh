#ifndef CONSTRAINTFUNCTION_HH
#define CONSTRAINTFUNCTION_HH

// Interface for constraint functions
// S. Kluth 9/2012

#include "TVectorD.h"

class ConstraintFunction {

public:

  virtual TVectorD calculate( const TVectorD&, const TVectorD& ) const = 0;

};


class ConstraintFunctionSwaped : public ConstraintFunction {

private:
  const ConstraintFunction * real_fun;

public:

  ConstraintFunctionSwaped(const ConstraintFunction * fun);
  TVectorD calculate( const TVectorD&, const TVectorD& ) const;

};





#endif

