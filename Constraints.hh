
// Class to Constraints calculate constraint equations using
// a function implemented via interface ConstraintFunction
// S. Kluth 9/2012

#ifndef CONSTRAINTS_HH
#define CONSTRAINTS_HH

#include "TVectorD.h"

class ConstraintFunction;

class Constraints {

public:
  Constraints( const ConstraintFunction&, Double_t epsilon=1.0e-4 );

  TVectorD calculate( const TVectorD&, const TVectorD& );

private:

  const ConstraintFunction& fun;
  Double_t precision;

};



#endif