
# GNU makefile for RooConstrainedFit
# S. Kluth 9/2012

LD = $(CXX)
CXXFLAGS = -Wall

LIBFILES = Constraints.cc ClsqSolver.cc
TESTFILE = testConstraints.cc
TESTEXE = $(basename $(TESTFILE) )
LIBOBJS = $(LIBFILES:.cc=.o)
LIB = libRooConstrainedFit.so
DEPS = $(LIBFILES:.cc=.d) $(TESTFILE:.cc=.d)
ROOTINC = $(ROOTSYS)/include
ROOTLIBS = $(ROOTSYS)/lib
PROJECTPATH = $(shell echo $${PWD%/*} )
CPPFLAGS = -I $(ROOTINC) -I $(PROJECTPATH)/AverageTools
LDFLAGS = -L $(ROOTLIBS) -L $(PROJECTPATH)/AverageTools
LDLIBS = -lMatrix

all: $(TESTEXE)

$(DEPS): %.d: %.cc
	$(CXX) $(CPPFLAGS) -MM $< -MF $@
-include $(DEPS)

$(LIB): $(LIBOBJS)
	$(LD) -shared -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(TESTEXE): %: %.o $(LIB)
	$(LD) -o $@ $^ -lboost_unit_test_framework $(LDFLAGS) $(LDLIBS)
	./$@ --log_level=message

clean:
	rm -f *.o $(DEPS) $(TESTEXE) $(LIB)

