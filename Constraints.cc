
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
	TVectorD columns;
	unsigned int varpardim = varpar.GetNrows();
	std::cout<<varpardim<<std::endl;
	TMatrixDSym h(varpardim, 1);
	for(unsigned int iRow = 0; iRow < varpardim; iRow++){
		h(iRow, 0) = 0;
	}

	//TMatrixDSym dcdp;
	//return dcdp;
	return h;
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

double Constraints::setH(double eps, double val){
  
  double result = eps;

  if (TMath::Abs(val) > 1.0e-6)
    result *= val;

  return result;

}
