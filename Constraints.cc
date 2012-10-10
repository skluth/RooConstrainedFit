
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


TMatrixDSym
Constraints::derivative( const ConstraintFunction& function, TVectorD& varpar, TVectorD& fixpar )
{
	unsigned int varpardim = varpar.GetNrows();
	TMatrixDSym columns(varpardim);
	TVectorD h(varpardim);
	for(unsigned int iRow = 0; iRow < varpardim; iRow++){
		h[iRow] = 0;
	}
	for(unsigned int ipar = 0; ipar < varpardim; ipar++){
		h[ipar] = setH(this->precision, varpar[ipar]);
		TVectorD column = fivePointStencil( function, varpar, h, fixpar );
		for(unsigned int i = 0; i < varpardim; i++){
			columns(i,ipar) = column[i];
		}
		h[ipar] = 0;
	}

	//TMatrixDSym dcdp;
	//return dcdp;
	return columns;
}

//def __derivative( self, function, varpar, fixpar ):
//    columns= []
//    varpardim= len(varpar)
//    h= matrix( zeros( shape=(varpardim,1) ) )
//    for ipar in range( varpardim ):
//        h[ipar]= setH( self.__precision, varpar[ipar] )
//        column= fivePointStencil( function, varpar, h, fixpar )
//        columns.append( column )
//        h[ipar]= 0.0
//    if len(columns) > 0:
//        cnstrdim= len(columns[0])
//    else:
//        cnstrdim= 0
//    dcdp= matrix( zeros( shape=(cnstrdim,varpardim) ) )
//    for ipar in range( varpardim ):
//        dcdp[:,ipar]= columns[ipar]
//    return dcdp


double Constraints::setH(const double& eps, const double& val){
  double result = eps;
  if (TMath::Abs(val) > 1.0e-6)
    result *= val;

  return result;
}

TVectorD Constraints::fivePointStencil(const ConstraintFunction& fun, const TVectorD& varpar, const TVectorD& h, const TVectorD& fixpar){
  TVectorD dfdp = (fun.calculate( varpar + 2.0*h, fixpar ) 
                   - 8.0*fun.calculate( varpar + h, fixpar ) 
                   + 8.0*fun.calculate( varpar - h, fixpar )
                   - fun.calculate( varpar - 2.0*h, fixpar ) );
  dfdp *= (-1. / (h.Sum() * 12.0 ));
  return dfdp;
}





