

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
	      Double_t eps=0.0001, Int_t mi= 100, 
	      Double_t dc=0.0001,
	      std::map<int,std::string> mpn=std::map<int,std::string>(), 
	      std::map<int,std::string> upn=std::map<int,std::string>(),
	      Int_t ndof=0 ); 
  
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
  std::vector<std::string> mparnames;
  std::vector<std::string> uparnames;
  TMatrixDSym invm;
  Int_t niterations;
  Int_t maxiterations;

};


#endif
