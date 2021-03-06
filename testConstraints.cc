
// Unit tests Constraints class
// S. Kluth, 9/2012

#include "Constraints.hh"
#include "Dodo.hh"
#include "LinearConstraintFunction.hh"
#include "ConstraintFunction.hh"

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

BOOST_AUTO_TEST_CASE( test_setH ) {
  double val= 2.0;
  double eps= 1.0;
  double result= cnstr.setH(eps, val);
  BOOST_CHECK_MESSAGE( result == 2.0, "large val" );
}

BOOST_AUTO_TEST_CASE( test_setHSmallVal ) {
  double val= 0.000000001;
  double eps= 1.0;
  double result= cnstr.setH(eps, val);
  BOOST_CHECK_MESSAGE( result == 1.0, "small val" );
}

BOOST_AUTO_TEST_CASE( test_derivativeM ) {
  TVectorD mpar= dodo.data;
  TVectorD upar= dodo.upar;
  int col_num= 5;
  int row_num= 5;
  TMatrixD derivative= cnstr.derivativeM( mpar, upar );
  BOOST_CHECK_MESSAGE( derivative.GetNcols() == col_num && 
		       derivative.GetNrows() == row_num, "dim test" );
  double tmp[]= { -1., 0., 0., 0., 0.,
		  0., -1., 0., 0., 0.,
		  0., 0., -1., 0., 0.,
		  0., 0., 0., -1., 0.,
		  0., 0., 0., 0., -1. };  
  TMatrixD expected( row_num, col_num, tmp );  
  for( int i= 0; i < row_num; i++ ) {
    for( int j= 0; j < col_num; j++ ) {
    BOOST_CHECK_CLOSE( expected[i][j], derivative[i][j], 0.0001 );
    }
  }
}

BOOST_AUTO_TEST_CASE( test_derivativeU ) {
  TVectorD mpar= dodo.data;
  TVectorD upar= dodo.upar;
  int col_num= 2;
  int row_num= 5;
  TMatrixD derivative= cnstr.derivativeU( mpar, upar );
  BOOST_CHECK_MESSAGE( derivative.GetNcols() == col_num && 
		       derivative.GetNrows() == row_num, "dim test" );
  double tmp[]= { 1.0, 1.0,
		  1.0, 2.0,
		  1.0, 3.0,
		  1.0, 4.0,
		  1.0, 5.0 };
  TMatrixD expected( row_num, col_num, tmp );
  for( int i= 0; i < row_num; i++ ) {
    for( int j= 0; j < col_num; j++ ) {
    BOOST_CHECK_CLOSE( expected[i][j], derivative[i][j], 0.0001 );
    }
  }
}

BOOST_AUTO_TEST_CASE( testFivePointStencilCalculatorM ) {
  Double_t ha[]= { 1.0, 0.0, 0.0, 0.0, 0.0 };
  TVectorD h( 5, ha );
  FivePointStencilCalculatorM fpscm( &cnstr );
  TVectorD points= fpscm.derivative( dodo.data, h, dodo.upar );
  Double_t ex[]= { -1.0 };
  TVectorD expected( 1, ex );
  for( Int_t i= 0; i < expected.GetNoElements(); i++ ) {
    BOOST_CHECK_CLOSE( expected[i], points[i], 0.0001 );
  }
}

BOOST_AUTO_TEST_CASE( testFivePointStencilCalculatorU ) {
  Double_t ha[]= { 1.0, 0.0 };
  TVectorD h( 2, ha );
  FivePointStencilCalculatorU fpscu( &cnstr );
  TVectorD points= fpscu.derivative( dodo.upar, h, dodo.data );
  Double_t ex[]= { 1.0 };
  TVectorD expected( 1, ex );
  for( Int_t i= 0; i < expected.GetNoElements(); i++ ) {
    BOOST_CHECK_CLOSE( expected[i], points[i], 0.0001 );
  }
}

BOOST_AUTO_TEST_SUITE_END()
