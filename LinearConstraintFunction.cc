
#include "LinearConstraintFunction.hh"

LinearConstraintFunction::LinearConstraintFunction( const TVectorD& x ) : 
  xabs( x ) {}

TVectorD LinearConstraintFunction::calculate( const TVectorD& mpar,
					      const TVectorD& upar ) const {
  Int_t n= mpar.GetNoElements();
  TVectorD constraints( n );
  for( Int_t i= 0; i < n; i++ ) {
    constraints[i]= upar[0] + upar[1]*xabs[i] - mpar[i];
  }
  return constraints;
}
