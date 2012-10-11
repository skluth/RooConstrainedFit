
// Solver for constrained linear least squares problem

#include "ClsqSolver.hh"

using std::string;
using std::map;
using std::vector;
#include <iostream>
#include <sstream>
#include <iomanip>

// Ctor:
ClsqSolver::ClsqSolver( const TVectorD& d, 
			const TMatrixDSym& c, 
			const TVectorD& u, 
			const ConstraintFunction& cfun, 
			const map<int,string>& upn, 
			const map<int,string>& mpn,
			Int_t nd, Int_t mi, Double_t eps, Double_t dc )
  : data(d), covm(c), upar(u), mpar(d), constraints( cfun, eps ),
    ndof(nd), maxiterations(mi), epsilon(eps), deltachi2(dc) 
{
  chisq = -1e99;
  uparnames= setParameterNames( upn, upar.GetNoElements() );
  mparnames= setParameterNames( mpn, mpar.GetNoElements() );
}

// Helper to setup parameter names:
vector<string> 
ClsqSolver::setParameterNames( const map<int,string>& parnamesmap,
			       Int_t npar ) {
  vector<string> parnames;
  string parname;
  for( Int_t ipar= 0; ipar < npar; ipar++ ) {
    map<int,string>::const_iterator mpiter= parnamesmap.find( ipar );
    if( mpiter != parnamesmap.end() ) {
      parname= mpiter->second;
    }
    else {
      std::ostringstream osstr;
      osstr << std::setfill( '0' );
      osstr << std::setw( 2 );
      osstr << std::setiosflags( std::ios_base::right );
      osstr << ipar;
      parname= "Parameter " + osstr.str();
    }
    parnames.push_back( parname );
  }
  return parnames;
}


// Get parameter names
std::vector<string> ClsqSolver::getUParNames() const {
  return uparnames;
}
std::vector<string> ClsqSolver::getMParNames() const {
  return mparnames;
}

void ClsqSolver::printTitle() const {
  std::cout<<"Constrained least squares CLSQ"<<std::endl;
}

Double_t ClsqSolver::getChisq() const {
  return chisq < 0 ? 1e-99 : chisq;
}

Int_t ClsqSolver::getnDoF() const {
  return ndof < 0 ? -1 : ndof;
}

TVectorD ClsqSolver::getUParv() const{
  return upar;
}

double* ClsqSolver::getUPar() {
  return upar.GetMatrixArray();
}

double* ClsqSolver::getMPar() {
  return mpar.GetMatrixArray();
}

TMatrixDSym ClsqSolver::getCovMatrix() const{
  return covm;
}

void ClsqSolver::solve(Bool_t &lpr, Bool_t &lBlobel){
}
