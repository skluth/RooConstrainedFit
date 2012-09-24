
// Unit tests Constraints class
// S. Kluth, 9/2012

// Tests for Constraints class
// S. Kluth 9/2012

#include "Constraints.hh"
#include "ConstraintFunction.hh"

#include <iostream>

#include "TVectorD.h"


// BOOST test stuff:
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE constraintstests
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>


// Test fixture for all tests:
// Data for tests:
class Dodo {
public:
  Dodo() : xabs(5), data(5), errors(5), upar(2) {
    Double_t x[]= { 1.0, 2.0, 3.0, 4.0, 5.0 };
    Double_t d[]= { 1.1, 1.9, 2.9, 4.1, 5.1 };
    Double_t e[]= { 0.1, 0.1, 0.1, 0.1, 0.1 };
    Double_t u[]= { 0.1, 1.1 };
    xabs.SetElements( x );
    data.SetElements( d );
    errors.SetElements( e );
    upar.SetElements( u );
  }
  TVectorD xabs;
  TVectorD data;
  TVectorD errors;
  TVectorD upar;
};
// ConstraintFunction subclass for tests:
class LinearConstraintFunction : public ConstraintFunction {
public:
  LinearConstraintFunction( const TVectorD& x ) : xabs( x ) {}
  virtual TVectorD calculate( const TVectorD& mpar,
			      const TVectorD& upar ) const {
    Int_t n= mpar.GetNoElements();
    TVectorD constraints( n );
    for( Int_t i= 0; i < n; i++ ) {
      constraints[i]= upar[0] + upar[1]*xabs[i] - mpar[i];
    }
    return constraints;
  }
private:
  TVectorD xabs;
};
// Actual test fixture class for boost:
class ConstraintsTestFixture {
public:
  ConstraintsTestFixture() : dodo(), 
			     lcf( dodo.xabs ), 
			     cnstr( lcf ) {
    BOOST_MESSAGE( "Create test fixture" );
  }
  virtual ~ConstraintsTestFixture() {
    BOOST_MESSAGE( "Tear down test fixture" );
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


BOOST_AUTO_TEST_SUITE_END()
