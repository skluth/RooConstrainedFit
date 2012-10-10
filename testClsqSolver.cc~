
// Unit tests for ClsqSolver class
// S. Kluth, 9/2012

#include "ClsqSolver.hh"
#include "Dodo.hh"
#include "LinearConstraintFunction.hh"

#include <iostream>
#include <string>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::map;

#include "TVectorD.h"
#include "TMatrixDSym.h"

// BOOST test stuff:
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE clsqsolvertests
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

// Fixture for next suite:
class ClsqSolverTestFixture {
public:
  ClsqSolverTestFixture() : dodo(), 
			    lcf( dodo.xabs ) {
    map<int,string> uparnames;
    uparnames[0]= "zero";
    map<int,string> mparnames;
    mparnames[1]= "one";
    mparnames[3]= "three";
    clsq= new ClsqSolver( dodo.data, dodo.covm, dodo.upar, lcf,
			  uparnames, mparnames );
    BOOST_MESSAGE( "Create ClsqSolverTestFixture" );
  }
  virtual ~ClsqSolverTestFixture() {
    delete clsq;
    BOOST_MESSAGE( "Tear down ClsqSolverTestFixture" );
  }
  Dodo dodo;
  LinearConstraintFunction lcf;
  ClsqSolver* clsq;
};
BOOST_FIXTURE_TEST_SUITE( clsqsolversuite, ClsqSolverTestFixture )


// Test clsq parameter names:
BOOST_AUTO_TEST_CASE( testClsqMParNames ) {
  vector<string> parnames= clsq->getMParNames();
  vector<string> expected;
  expected.push_back( "Parameter 00" );
  expected.push_back( "one" );
  expected.push_back( "Parameter 02" );
  expected.push_back( "three" );
  expected.push_back( "Parameter 04" );
  for( size_t i= 0; i < expected.size(); i++ ) {
    BOOST_CHECK_EQUAL( expected[i], parnames[i] );
  }
}
BOOST_AUTO_TEST_CASE( testClsqUParNames ) {
  vector<string> parnames= clsq->getUParNames();
  vector<string> expected;
  expected.push_back( "zero" );
  expected.push_back( "Parameter 01" );
  for( size_t i= 0; i < expected.size(); i++ ) {
    BOOST_CHECK_EQUAL( expected[i], parnames[i] );
  }
}


BOOST_AUTO_TEST_SUITE_END()
