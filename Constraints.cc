
// Calculation of constraints using ConstraintFunction
// S. Kluth 9/2012

#include "Constraints.hh"
#include "ConstraintFunction.hh"
#include "TVectorD.h"

Constraints::Constraints( const ConstraintFunction& cf, Double_t epsilon ) :
  fun( cf ), precision( epsilon ) {}

TVectorD Constraints::calculate( const TVectorD& mpar, 
				 const TVectorD& upar ) {
  TVectorD constraints= fun.calculate( mpar, upar );
  return constraints;
}

double Constraints::setH(double eps, double val){
  
  double result = eps;

  if (TMath::Abs(val) > 1.0e-6)
    result *= val;

  return result;

}
