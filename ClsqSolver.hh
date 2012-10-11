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

  funcobj( Int_t& ipar, Double_t& val, std::string opt = "u" )
    : idx(ipar), value(val), meth(opt)
  {  }

  Double_t operator()( TVectorD& mpar, TVectorD& upar) {
    if ( meth == "u") return upar[idx] - value;
    if ( meth == "m") return mpar[idx] - value;
  }  

private:

  Int_t idx;
  Double_t value;
  std::string meth;
  
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
  void printTitle() const;
  void printFitParameters(Double_t Chisq , Int_t NDOF , const char* format);
  void printResults(const char * format , Bool_t cov=false, Bool_t corr=false );
  



  Double_t                 getChisq() const;
  Int_t                    getnDoF() const;
  TVectorD                 getUParv() const;
  double*                  getUPar();
  double*                  getMPar();
  double*                  getUparErrors() const;
  double*                  getMparErrors() const;
  TMatrixDSym              getUparErrorMatrix() const;
  TMatrixDSym              getMparErrorMatrix() const;
  TMatrixDSym              getCovMatrix() const;
  void solveByPartition( TVectorD& dcdmpm, TVectorD& dcdupm, TVectorD& constrv );
  void prepareDeltapar( Int_t& datadim, Int_t& upardim, Int_t& constrdim,
			Double_t& c11, Double_t& c21, Double_t& c31, 
			Double_t& c32, Double_t& c33, TVectorD& constrv );
  void solve( Bool_t& lpr, Bool_t& lBlobel);
  void fixMpar(Int_t parspec, Double_t *val=NULL, Bool_t lpr=true );
  void fixMpar(std::string parspec,Double_t *val=NULL, Bool_t lpr=true );
  void releaseMpar(Int_t parspec, Bool_t lpr=true );
  void releaseMpar(std::string parspec, Bool_t lpr=true );
  void fixUpar(Int_t parspec, Double_t *val=NULL, Bool_t lpr=true );
  void fixUpar(std::string parspec, Double_t *val=NULL, Bool_t lpr=true );
  void releaseUpar(Int_t parspec, Bool_t lpr=true );
  void releaseUpar(std::string parspec, Bool_t lpr=true );
  TVectorD prepareRhsv(Int_t dim, Int_t datadim, Int_t upardim, TVectorD constrv ); //returns a (0,...,0,(constrv))
  Double_t calcChisq(TMatrixD dcdmpm , Double_t c33);
  TVectorD getConstraints();
    //def getErrorMatrix( self ):
    //def getUparCorrMatrix( self ):
    //def getMparCorrMatrix( self ):
    //def getCorrMatrix( self ):
  TMatrixDSym getCovm() const;
  TMatrixDSym getInvm() const;
  TVectorD getData() const;
    //def getMparPulls( self ):
    //def makeInverseProblemMatrix( self, dcdmpm, dcdupm ):
    //def setUpar( self, parspec, val ):
    //def setMpar( self, parspec, val ):
    //def profileUpar( self, parspec, nstep=5, stepsize=1.0 ):
    //def profileMpar( self, parspec, nstep=5, stepsize=1.0 ):
    //def minosUpar( self, parspec, chisqmin=None, delta=1.0 ):
    //def minosMpar( self, parspec, chisqmin=None, delta=1.0 ):
    //def fun( x ):
    //def contour( self, iparspec, iopt, jparspec, jopt,
    //def profile2d( self, ipar, iopt, jpar, jopt, nstep=11, stepsize=0.5 ):


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
  void solveByInversion( TVectorD& dcdmpm,  TVectorD& dcdupm, TVectorD& constrv );
  Int_t parameterIndex(std::string parspec);
  Int_t parameterIndex(Int_t parspec);
	void printPars(double *par, double* parerrs, std::vector<std::string> &parnames,std::map<int,funcobj> fixedParFunctions, const char* ffmt="%.4f", Bool_t pulls=false);
    //def __setParNames( self, parnames, npar ):
    //def __printPars( self, par, parerrs, parnames, fixedParFunctions,
    //def __printMatrix( self, m, ffmt, names ):
    //def __getCorrMatrix( self, paropt ):
    //def __makeProblemMatrix( self, dcdmpm, dcdupm ):
    //def __profile( self, ipar, nstep, stepsize,
    //def __minos( self, ipar, chisqmin, delta,

};


#endif
