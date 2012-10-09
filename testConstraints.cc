
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

  double val = 2;
  double eps = 1;
  double result = cnstr.setH(eps, val);

  BOOST_CHECK_MESSAGE(result == 2, "large val");

  val = 0.000000001;
  eps = 1;
  result = cnstr.setH(eps, val);

  BOOST_CHECK_MESSAGE(result == 1, "small val");

}


BOOST_AUTO_TEST_SUITE_END()
