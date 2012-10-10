
// Class to Constraints calculate constraint equations using
// a function implemented via interface ConstraintFunction
// S. Kluth 9/2012

#ifndef CONSTRAINTS_HH
#define CONSTRAINTS_HH

#include "TVectorD.h"
#include "TMatrixDSym.h"
#include "TMatrixD.h"
#include "TMath.h"

class ConstraintFunction;

class Constraints {

public:

  // Ctor: construct from constraint function object and optional
  // precision value:
  Constraints( const ConstraintFunction&, Double_t epsilon=1.0e-4 );

  // Calculate constraints from measured and unmeasured parameters:
  TVectorD calculate( const TVectorD& mpar, const TVectorD& upar );
  TMatrixD derivative( const ConstraintFunction& function, const TVectorD& varpar, const TVectorD& fixpar );
  TMatrixD derivativeM(const TVectorD& mpar, const TVectorD& upar);
  TMatrixD derivativeU(const TVectorD& mpar, const TVectorD& upar);
  TVectorD fivePointStencil(const ConstraintFunction& fun, const TVectorD& varpar, const TVectorD& h, const TVectorD& fixpar);
  double setH(const double& eps, const double& val);

private:

  const ConstraintFunction& fun;
  Double_t precision;

};



#endif
