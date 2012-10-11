
// Unit tests for ClsqSolver class
// S. Kluth, 9/2012

#include "ClsqSolver.hh"
#include "Dodo.hh"
#include "LinearConstraintFunction.hh"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
using std::string;
using std::vector;
using std::map;

#include "TVectorD.h"
#include "TMatrixDSym.h"

// BOOST test stuff:
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE clsqsolvertests
#define SOLUTION_OK 0

#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/output_test_stream.hpp>

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
  void CheckSolution();
  Dodo dodo;
  LinearConstraintFunction lcf;
  ClsqSolver* clsq;
};

void ClsqSolverTestFixture::CheckSolution(){
//	BOOST_FAIL("test not ready yet");
	double* mpar = clsq->getMPar();
	double* upar = clsq->getUPar();
	double expectedmpar[5] = {0.98, 2.0, 3.02, 4.04, 5.06};
	double expectedupar[2] = {-0.04, 1.02};
	char err_message[50];
	
	for(int i=0;i<5;i++){
		sprintf(err_message,"mpar number %d is not expected!",i);
		BOOST_CHECK_MESSAGE(expectedmpar[i]==mpar[i], err_message);
	}
	for(int i=0;i<2;i++){
		sprintf(err_message,"upar number %d is not expected!",i);
		BOOST_CHECK_MESSAGE(expectedupar[i]==upar[i], err_message);
		
	}
}


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

BOOST_AUTO_TEST_CASE( testGetChiq ){
  BOOST_CHECK_EQUAL( clsq->getChisq(),  -1e99 );
}

BOOST_AUTO_TEST_CASE( testnDoF ){
  BOOST_CHECK_EQUAL( clsq->getnDoF(), 0 );
}

BOOST_AUTO_TEST_CASE( testgetUParV ){
  std::cout << clsq->getCovMatrix().GetMatrixArray() << std::endl;
  BOOST_CHECK_MESSAGE( !clsq->getCovMatrix().GetMatrixArray()  , "No CovMatrix found");
}

class cout_redirect{
private:
  std::streambuf * save;
public:
  cout_redirect(std::streambuf * buffer)
  {
    save=std::cout.rdbuf(buffer);
  }
  ~cout_redirect(){
    std::cout.rdbuf(save);
  }
};

BOOST_AUTO_TEST_CASE( testClsprintTitle ){
  boost::test_tools::output_test_stream output;
  {
    cout_redirect testout(output.rdbuf());
    clsq->printTitle();
    //test the prints
  }
  BOOST_CHECK(output.is_equal("Constrained least squares CLSQ\n"));
}

BOOST_AUTO_TEST_CASE( test_solve ){
  BOOST_FAIL("test not ready");
}

BOOST_AUTO_TEST_CASE( test_calculate){
  BOOST_FAIL("test not ready");
}

BOOST_AUTO_TEST_CASE( test_derivativeM){
  BOOST_FAIL("test not ready yet");
}

BOOST_AUTO_TEST_CASE( test_derivativeU){ 
  BOOST_FAIL("test not ready yet");
}

BOOST_AUTO_TEST_CASE( test_setUp){
  BOOST_FAIL("test not ready yet");
}

BOOST_AUTO_TEST_CASE( test_clsqSolverInversion){ 
  clsq->solveByInversion( TVectorD& dcdmpm,  TVectorD& dcdupm, TVectorD& constrv );
  CheckSolution();
}

BOOST_AUTO_TEST_CASE( test_clsqSolverPartition){
  //  clsq->solveByPartition( TVectorD& dcdmpm, TVectorD& dcdupm, TVectorD& constrv );
  CheckSolution();
}

BOOST_AUTO_TEST_CASE( test_checkSolution){
}

BOOST_AUTO_TEST_SUITE_END()
