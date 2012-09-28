
#include "Dodo.hh"

Dodo::Dodo() : xabs(5), data(5), errors(5), upar(2), covm(5) {
  Double_t x[]= { 1.0, 2.0, 3.0, 4.0, 5.0 };
  Double_t d[]= { 1.1, 1.9, 2.9, 4.1, 5.1 };
  Double_t e[]= { 0.1, 0.1, 0.1, 0.1, 0.1 };
  Double_t u[]= { 0.1, 1.1 };
  xabs.SetElements( x );
  data.SetElements( d );
  errors.SetElements( e );
  upar.SetElements( u );
  for( Int_t i= 0; i < 5; i++ ) {
    covm(i,i)= errors[i]*errors[i];
  }
}

