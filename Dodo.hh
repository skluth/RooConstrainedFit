#ifndef DODO_HH
#define DODO_hh

#include "TVectorD.h"
#include "TMatrixDSym.h"

// Data for tests:
class Dodo {
public:
  Dodo();
  TVectorD xabs;
  TVectorD data;
  TVectorD errors;
  TVectorD upar;
  TMatrixDSym covm;
};

#endif
