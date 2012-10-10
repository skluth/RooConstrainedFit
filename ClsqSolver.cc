
// Solver for constrained linear least squares problem

#include "ClsqSolver.hh"

using std::string;
using std::map;
using std::vector;
#include <sstream>
#include <iomanip>

// Ctor:
ClsqSolver::ClsqSolver( const TVectorD& d, 
			const TMatrixDSym& c, 
			const TVectorD& u, 
			const ConstraintFunction& cfun, 
			const map<int,string>& upn, 
			const map<int,string>& mpn,
			Int_t nd, Int_t mi, Double_t eps, Double_t dc ) :
  data(d), covm(c), upar(u), mpar(d), constraints( cfun, eps ),
  ndof(nd), maxiterations(mi), epsilon(eps), deltachi2(dc) {
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
vector<string> ClsqSolver::getUParNames() const {
  return uparnames;
}
vector<string> ClsqSolver::getMParNames() const {
  return mparnames;
}


//! group2 modifications
//! ClsqSolver::setUpar
//! ClsgSolver::parameterIndex returns int
void ClsqSolver::setUpar(void* parspec, double val) {

	int ipar = ClsqSolver::parameterIndex(parspec, uparnames);
	upar[ipar] = val;
	
	cout << "Set unmeasured parameter " << uparnames[ipar] << " to " << val << endl;
	return;
}

//! ClsqSolver::setMpar
//! ClsgSolver::parameterIndex returns int
void ClsqSolver::setMpar(void* parspec, double val) {

	int ipar = ClsqSolver::parameterIndex(parspec, mparnames);
	upar[ipar] = val;
	
	cout << "Set measured parameter " << mparnames[ipar] << " to " << val << endl;
	return;
}
       
//! ClsgSolver::parameterIndex returns int
//! for int parspec  
int ClsqSolver::parameterIndex(int parspec, std::vector<std::string> parnames) {
  return parspec;
}
//! for string parspec
int ClsqSolver::parameterIndex(string parspec, std::vector<std::string> parnames) {

	for (int ipar = 0; ipar < parnames -> Size(); ipar++) if (parnames[ipar] == parspec) return ipar;
}