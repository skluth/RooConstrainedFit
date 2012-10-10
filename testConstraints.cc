
// Unit tests Constraints class
// S. Kluth, 9/2012

// Tests for Constraints class
// S. Kluth 9/2012

#include "Constraints.hh"
#include "Dodo.hh"
#include "LinearConstraintFunction.hh"

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

#include "TVectorD.h"
#include "TMatrixDSym.h"
#include "TMatrixD.h"

// BOOST test stuff:
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE constraintstests
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

// Test fixture class for Constrains:
class ConstraintsTestFixture {
public:
  ConstraintsTestFixture() : dodo(), 
			     lcf( dodo.xabs ), 
			     cnstr( lcf ) {
    BOOST_MESSAGE( "Create ConstraintsTestFixture" );
  }
  virtual ~ConstraintsTestFixture() {
    BOOST_MESSAGE( "Tear down ConstraintsTestFixture" );
  }
  Dodo dodo;
  LinearConstraintFunction lcf;
  Constraints cnstr;
};

// Declare test suite name and fixture class to BOOST:
BOOST_FIXTURE_TEST_SUITE( constraintssuite, ConstraintsTestFixture )

// Test cases:

// Test calculation of constraints:
BOOST_AUTO_TEST_CASE( testCalculate ) {
  TVectorD constraints= cnstr.calculate( dodo.data, dodo.upar );
  Double_t ex[]= { 0.1, 0.4, 0.5, 0.4, 0.5 };
  TVectorD expected( 5, ex );

  for( Int_t i= 0; i < expected.GetNoElements(); i++ ) {
    BOOST_CHECK_CLOSE( expected[i], constraints[i], 0.0001 );
  }
}


BOOST_AUTO_TEST_CASE( testDerivative ){
	double xArray[3] = {1.,0.,0.};
	double varparArray[3] = {1.,1.,1.};
	double mparArray[3] = {0.,1.,0.};
	TVectorD x = TVectorD(3,xArray);
	TVectorD vpar = TVectorD(3,varparArray);
	TVectorD fixpar = TVectorD(3,mparArray);
	lcf = LinearConstraintFunction(x);
	TMatrixDSym h = cnstr.derivative(lcf, vpar, fixpar);
	//std::cout<<h(2,2)<<std::endl;
	BOOST_CHECK_MESSAGE(h(0,0) == 0, "h is not 0: " << h(0,0));
}


BOOST_AUTO_TEST_CASE( test_setH ) {


  double val = 2;
  double eps = 1;
  double result = cnstr.setH(eps, val);

  BOOST_CHECK_MESSAGE(result == 2, "large val");

}


BOOST_AUTO_TEST_CASE( test_setHSmallVal ) {

  double val = 0.000000001;
  double eps = 1;
  double result = cnstr.setH(eps, val);

  BOOST_CHECK_MESSAGE(result == 1, "small val");
}


BOOST_AUTO_TEST_CASE( test_derivativeM ) {


  TVectorD mpar = dodo.data;
  TVectorD upar = dodo.upar;
  int col_num = 5;
  int row_num = 5;


  TMatrixD derivative = derivativeM(mpar, upar);

  double tmp = [-1., 0., 0., 0., 0.,
		0., -1., 0., 0., 0.,
		0., 0., -1., 0., 0.,
		0., 0., 0., -1., 0.,
		0., 0., 0., 0., -1.];

  TMatrixD expected = (row_num, col_num, tmp);  

  for( int i= 0; i < row_num; i++ ) {
    for( int j= 0; j < col_num; j++ ) {
    BOOST_CHECK_CLOSE( expected[i][j], derivative[i][j], 0.0001 );
    }
  }

}


BOOST_AUTO_TEST_CASE( test_derivativeU ) {


  TVectorD mpar = dodo.data;
  TVectorD upar = dodo.upar;
  int col_num = 2;
  int row_num = 5;

  TMatrixD derivative = derivativeU(mpar, upar);

  double tmp =  [1.0, 1.0,
		 1.0, 2.0,
		 1.0, 3.0,
		 1.0, 4.0,
		 1.0, 5.0];
  
  TMatrixD expected = (row_num, col_num, tmp);  

  for( int i= 0; i < row_num; i++ ) {
    for( int j= 0; j < col_num; j++ ) {
    BOOST_CHECK_CLOSE( expected[i][j], derivative[i][j], 0.0001 );
    }
  }

}


BOOST_AUTO_TEST_CASE( testFivarpardimvePointStencil ) {
  Double_t ha[] = {1.,0.,0.,0.,0.};
  TVectorD h(5, ha);
  TVectorD points = cnstr.fivePointStencil( lcf, dodo.data, h, dodo.upar );
  Double_t ex[]= {-1.};
  TVectorD expected( 1, ex );
  for( Int_t i= 0; i < expected.GetNoElements(); i++ ) {
    BOOST_CHECK_CLOSE( expected[i], points[i], 0.0001 );
  }
}


BOOST_AUTO_TEST_SUITE_END()
