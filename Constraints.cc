
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


TMatrixD Constraints::derivative( const ConstraintFunction& function, TVectorD& varpar, TVectorD& fixpar )
{
	unsigned int varpardim = varpar.GetNrows();
	std::vector<TVectorD > columns;
	TVectorD h(varpardim);
	for(unsigned int iRow = 0; iRow < varpardim; iRow++){
		h[iRow] = 0;
	}
	for(unsigned int ipar = 0; ipar < varpardim; ipar++){
		h[ipar] = setH(this->precision, varpar[ipar]);
		TVectorD column = fivePointStencil( function, varpar, h, fixpar );
			columns.push_back(column);
		h[ipar] = 0;
	}
	double cnstrdim;
	if(columns.size() > 0){
		cnstrdim = columns.at(0).GetNrows();
	}
	else{
		cnstrdim = 0;
	}
	TMatrixD dcdp(cnstrdim,varpardim);
	for(int i=0; i<varpardim;i++){
		for(int j=0; j<cnstrdim; j++){
			dcdp(j,i) = columns.at(i)[j];
		}
	}

	return dcdp;
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



