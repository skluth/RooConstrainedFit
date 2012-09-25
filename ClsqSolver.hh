

#ifndef CLSQSOLVER_HH
#define CLSQSOLVER_hh


#include "Constraints.hh"
#include "ConstraintFunction.hh"

#include "TVectorD.h"
#include "TMatrixD.h"

#include <string>
#include <map>
#include <vector>

class ClsqSolver {

public:

  ClsqSolver( const TVectorD& d, 
	      const TMatrixDSym& c, 
	      const TVectorD& u, 
	      const ConstraintFunction& cfun, 
	      const std::map<int,std::string>& upn=std::map<int,std::string>(),
	      const std::map<int,std::string>& mpn=std::map<int,std::string>(), 
	      Int_t nd=0, Int_t mi=100, 
	      Double_t eps=0.0001, Double_t dc=0.0001 );
  
  std::vector<std::string> getMParNames() const;
  std::vector<std::string> getUParNames() const;

private:
  
  std::vector<std::string> 
  setParameterNames( const std::map<int,std::string>& parnames,
		     Int_t npar );
			  
  TVectorD data;
  TMatrixDSym covm;
  TVectorD upar;
  TVectorD mpar;
  Constraints constraints;
  std::vector<std::string> uparnames;
  std::vector<std::string> mparnames;
  TMatrixDSym invm;
  Int_t ndof;
  Int_t maxiterations;
  Double_t epsilon;
  Double_t deltachi2;
  Int_t niterations;

};


#endif
