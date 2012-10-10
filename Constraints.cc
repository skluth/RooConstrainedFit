
// Calculation of constraints using ConstraintFunction
// S. Kluth 9/2012

#include <iostream>
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


double Constraints::setH(const double& eps, const double& val){
  double result = eps;
  if (TMath::Abs(val) > 1.0e-6)
    result *= val;

  return result;
}


TMatrixD Constraints::derivativeM(const TVectorD& mpar, const TVectorD& upar){

  return this->derivative(fun, mpar, upar);

}


TMatrixD Constraints::derivativeU(const TVectorD& mpar, const TVectorD& upar){

  return this->derivative(fun, upar, mpar);

}

TVectorD Constraints::fivePointStencil(const ConstraintFunction& fun, const TVectorD& varpar, const TVectorD& h, const TVectorD& fixpar){
  TVectorD dfdp = (fun.calculate( varpar + 2.0*h, fixpar ) 
                   - 8.0*fun.calculate( varpar + h, fixpar ) 
                   + 8.0*fun.calculate( varpar - h, fixpar )
                   - fun.calculate( varpar - 2.0*h, fixpar ) );
  dfdp *= (-1. / (h.Sum() * 12.0 ));
  return dfdp;
}



