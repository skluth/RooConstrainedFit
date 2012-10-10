#ifndef CLSQSOLVER_HH
#define CLSQSOLVER_hh

// Solver for constrained linear least squares

#include "Constraints.hh"
#include "ConstraintFunction.hh"

#include "TVectorD.h"
#include "TMatrixD.h"

#include <string>
#include <map>
#include <vector>

class funcobj{

public:

  funcobj();

  funcobj( Int_t& ipar, Double_t& val, std::string opt = "u" );

private:


  
  
};

class ClsqSolver {

public:

  // Ctor: pass input data, constraint function object and optional
  // parameter name maps mapping parameter number (0-n) to names:
  ClsqSolver( const TVectorD& d, 
	      const TMatrixDSym& c, 
	      const TVectorD& u, 
	      const ConstraintFunction& cfun, 
	      const std::map<int,std::string>& upn=std::map<int,std::string>(),
	      const std::map<int,std::string>& mpn=std::map<int,std::string>(), 
	      Int_t nd=0, Int_t mi=100, 
	      Double_t eps=0.0001, Double_t dc=0.0001 );
  
  // Accessors:
  std::vector<std::string> getMParNames() const;
  std::vector<std::string> getUParNames() const;

  Double_t                 getChisq() const;
  Int_t                    getnDoF() const;
  TVectorD                 getUParv() const;
  double*                  getUPar();
  double*                  getMPar();
  double*                  getMparErrors() const;
  TMatrixDSym              getUparErrorMatrix() const;
  TMatrixDSym              getMparErrorMatrix() const;
  TMatrixDSym              getCovMatrix() const;

private:
  
  // Helper to setup parameter names
  std::vector<std::string> 
  setParameterNames( const std::map<int,std::string>& parnames,
		     Int_t npar );
			  
  // Instance variables:
  TVectorD data;
  TMatrixDSym covm, invm;
  TVectorD upar;
  TVectorD mpar;
  Constraints constraints;
  std::vector<std::string> uparnames;
  std::vector<std::string> mparnames;
  Int_t ndof;
  Int_t maxiterations;
  Int_t niterations;
  Double_t epsilon;
  Double_t chisq;
  Double_t deltachi2;

  std::map<int,funcobj> fixedUparFunctions;
  std::map<int,funcobj> fixedMparFunctions;

  // Instance Methods
  Double_t calcChisq( TVectorD& dcdmpm, Double_t c33 );
  void solve( Bool_t& lpr, Bool_t& lBlobel);
  void solveByInversion( TVectorD& dcdmpm,  TVectorD& dcdupm, TVectorD& constrv );
  void solveByPartition( TVectorD& dcdmpm, TVectorD& dcdupm, TVectorD& constrv );

  void prepareDeltapar( Int_t& datadim, Int_t& upardim, Int_t& constrdim,
			Double_t& c11, Double_t& c21, Double_t& c31, 
			Double_t& c32, Double_t& c33, TVectorD& constrv );
};


#endif
