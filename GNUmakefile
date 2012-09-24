
LD = $(CXX)
CXXFLAGS = -Wall

LIBFILES = Constraints.cc ClsqSolver.cc
TESTFILE = testConstraints.cc
TESTEXE = $(basename $(TESTFILE) )
LIBOBJS = $(LIBFILES:.cc=.o)
DEPS = $(LIBFILES:.cc=.d) $(TESTFILE:.cc=.d)
ROOTLIBS = $(ROOTSYS)/lib
ROOTINC = $(ROOTSYS)/include
CPPFLAGS = -I $(ROOTINC)
LDFLAGS = -L $(ROOTLIBS)
LDLIBS = -lMatrix

all: $(TESTEXE)

$(DEPS): %.d: %.cc
	$(CXX) $(CPPFLAGS) -MM $< -MF $@
-include $(DEPS)

libRooConstrainedFit.so: $(LIBOBJS)
	$(LD) -shared -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(TESTEXE): $(TESTFILE:.cc=.o) libRooConstrainedFit.so
	$(LD) -o $@ $^ -lboost_unit_test_framework $(LDFLAGS) $(LDLIBS)
	./$@ --log_level=message

clean:
	rm -f *.o $(DEPS) $(TESTEXE) libRooConstrainedFit.so

