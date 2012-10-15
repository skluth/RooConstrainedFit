#ifndef CONSTRAINTS_HH
#define CONSTRAINTS_HH

// Class to calculate constraint equations using
// a function implemented via interface ConstraintFunction
// S. Kluth 9/2012

#include "TVectorD.h"
#include "TMatrixDSym.h"
#include "TMatrixD.h"
#include "TMath.h"

class ConstraintFunction;
class FivePointStencilCalculator;

class Constraints {

public:

  // Ctor: construct from constraint function object and optional
  // precision value:
  Constraints( const ConstraintFunction&, Double_t epsilon=1.0e-4 );

  // Calculate constraints from measured and unmeasured parameters:
  TVectorD calculate( const TVectorD& mpar, const TVectorD& upar ) const;
  TMatrixD derivativeM( const TVectorD& mpar, const TVectorD& upar) const;
  TMatrixD derivativeU( const TVectorD& mpar, const TVectorD& upar) const;
  TMatrixD derivative( const FivePointStencilCalculator& fpsc, 
		       const TVectorD& varpar, 
		       const TVectorD& fixpar ) const;

  double setH( const double eps, const double val ) const;

private:

  const ConstraintFunction& fun;
  Double_t precision;

};


// Derivatives for measured or unmeasured parameters
// using 5-point stencil in a template method pattern:
class FivePointStencilCalculator {
public:
  TVectorD derivative( const TVectorD& varpar, 
		       const TVectorD& h, 
		       const TVectorD& fixpar ) const;
protected:
  virtual TVectorD calculate( const TVectorD& varpar, 
			      const TVectorD& fixpar ) const = 0;
};
class FivePointStencilCalculatorM : public FivePointStencilCalculator {
public:
  FivePointStencilCalculatorM( const Constraints* c ) : cnstr( c ) {}
protected:
  TVectorD calculate( const TVectorD& varpar, 
		      const TVectorD& fixpar ) const;
private:
  const Constraints* cnstr;
};
class FivePointStencilCalculatorU : public FivePointStencilCalculator {
public:
  FivePointStencilCalculatorU( const Constraints* c ) : cnstr( c ) {}
protected:
  TVectorD calculate( const TVectorD& varpar, 
		      const TVectorD& fixpar ) const;
private:
  const Constraints* cnstr;
};


#endif
