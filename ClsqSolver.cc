

#include "ClsqSolver.hh"


using std::string;
using std::map;
using std::vector;
#include <sstream>
#include <iomanip>
// using std::ostringstream;




ClsqSolver::ClsqSolver( const TVectorD& d, 
			const TMatrixDSym& c, 
			const TVectorD& u, 
			const ConstraintFunction& cfun, 
			Double_t eps, Int_t mi, Double_t dc,
			map<int,string> mpn, map<int,string> upn,
			Int_t ndof ) : 
  data(d), covm(c), upar(u), mpar(d), constraints( cfun, eps ),
  maxiterations( mi ) {

  mparnames= setParameterNames( mpn, mpar.GetNoElements() );
  uparnames= setParameterNames( upn, upar.GetNoElements() );

}

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



vector<string> ClsqSolver::getMParNames() const {
  return mparnames;
}
vector<string> ClsqSolver::getUParNames() const {
  return uparnames;
}
