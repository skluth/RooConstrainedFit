
// Calculation of constraints using ConstraintFunction
// S. Kluth 9/2012

#include <iostream>
#include "Constraints.hh"
#include "ConstraintFunction.hh"
#include "TVectorD.h"

Constraints::Constraints( const ConstraintFunction& cf, Double_t epsilon ) :
  fun( cf ), precision( epsilon ) {
}

TVectorD Constraints::calculate( const TVectorD& mpar,
				 const TVectorD& upar ) const {
  TVectorD constraints= fun.calculate( mpar, upar );
  return constraints;
}

TMatrixD Constraints::derivativeM( const TVectorD& mpar, 
				   const TVectorD& upar ) const {
  FivePointStencilCalculatorM fpscm( this );
  return derivative( fpscm, mpar, upar );
}
TMatrixD Constraints::derivativeU( const TVectorD& mpar, 
				   const TVectorD& upar ) const {
  FivePointStencilCalculatorU fpscu( this );
  return derivative( fpscu, upar, mpar );
}
TMatrixD Constraints::derivative( const FivePointStencilCalculator& fpsc, 
				  const TVectorD& varpar, 
				  const TVectorD& fixpar ) const {
  Int_t varpardim= varpar.GetNrows();
  std::vector<TVectorD> columns;
  TVectorD h( varpardim );
  for( Int_t ipar= 0; ipar < varpardim; ipar++ ) {
    h[ipar]= setH( precision, varpar[ipar] );
    TVectorD column= fpsc.derivative( varpar, h, fixpar );
    columns.push_back( column );
    h[ipar]= 0.0;
  }
  Int_t cnstrdim;
  if( columns.size() > 0 ) {
    cnstrdim= columns.at(0).GetNrows();
  }
  else {
    cnstrdim= 0;
  }
  TMatrixD dcdp( cnstrdim, varpardim );
  for( Int_t i= 0; i < varpardim; i++ ) {
    for( Int_t j= 0; j < cnstrdim; j++ ) {
      dcdp(j,i)= columns.at(i)[j];
    }
  } 
  return dcdp;
}

double Constraints::setH( const double eps, const double val ) const {
  double result= eps;
  if( TMath::Abs( val ) > 1.0e-6 ) result*= val;
  return result;
}


TVectorD 
FivePointStencilCalculator::derivative( const TVectorD& varpar, 
					const TVectorD& h, 
					const TVectorD& fixpar ) const {
  TVectorD dfdp= ( calculate( varpar + 2.0*h, fixpar ) 
		   - 8.0*calculate( varpar + h, fixpar ) 
		   + 8.0*calculate( varpar - h, fixpar )
		   - calculate( varpar - 2.0*h, fixpar ) );
  dfdp*= (-1.0 / (h.Sum() * 12.0 ));
  return dfdp;
}

TVectorD 
FivePointStencilCalculatorM::calculate( const TVectorD& varpar, 
					const TVectorD& fixpar ) const {
  return cnstr->calculate( varpar, fixpar );
}

TVectorD 
FivePointStencilCalculatorU::calculate( const TVectorD& varpar, 
					const TVectorD& fixpar ) const {
  return cnstr->calculate( fixpar, varpar );
}
