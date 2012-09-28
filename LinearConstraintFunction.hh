#ifndef LINEARCONSTRAINTFUNCTION_HH
#define LINEARCONSTRAINTFUNCTION_HH

#include "ConstraintFunction.hh"

// ConstraintFunction subclass for tests:
class LinearConstraintFunction : public ConstraintFunction {

public:

  LinearConstraintFunction( const TVectorD& x );

  virtual TVectorD calculate( const TVectorD& mpar,
			      const TVectorD& upar ) const;

private:

  TVectorD xabs;

};

#endif
