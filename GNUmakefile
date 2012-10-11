
# GNU makefile for RooConstrainedFit
# S. Kluth 9/2012

LD = $(CXX)
CXXFLAGS = -Wall -fPIC -g

LIBFILES = Constraints.cc ClsqSolver.cc
TESTLIBFILES = Dodo.cc LinearConstraintFunction.cc ConstraintFunction.cc
TESTFILE = testConstraints.cc testClsqSolver.cc
TESTEXE = $(basename $(TESTFILE) )
LIBOBJS = $(LIBFILES:.cc=.o)
TESTLIBOBJS = $(TESTLIBFILES:.cc=.o)
LIB = libRooConstrainedFit.so
TESTLIB = libRooConstrainedFitTest.so
DEPS = $(LIBFILES:.cc=.d) $(TESTFILE:.cc=.d)
PROJECTPATH = $(shell echo $${PWD%/*} )
CPPFLAGS = -I $(PROJECTPATH)/RooAverageTools
LDFLAGS = -L $(PROJECTPATH)/RooAverageTools
LDLIBS = -lRooAverageTools -lMatrix -lCore
ifdef HEPROOT
CPPFLAGS += -I $(HEPROOT)/include -I $(HEPROOT)/include/boost-1_48/ -g
LDFLAGS += -L $(HEPROOT)/lib64
LDLIBS += -lboost_unit_test_framework-gcc46-mt-1_48
else
CPPFLAGS += -I $(ROOTSYS)/include -g
LDFLAGS += -L $(ROOTSYS)/lib 
LDLIBS += -lboost_unit_test_framework
endif
LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):$(PROJECTPATH)/RooAverageTools:$(PROJECTPATH)/INIParser

.INTERMEDIATE: $(LIBOBJS) $(TESTLIBOBJS) $(TESTFILE:.cc=.o)

all: $(TESTEXE)

$(DEPS): %.d: %.cc
	$(CXX) $(CPPFLAGS) -MM $< -MF $@ -include $(DEPS)

$(LIB): $(LIBOBJS)
	$(LD) -shared -o $@ $^ $(LDFLAGS) $(LDLIBS)
$(TESTLIB): $(TESTLIBOBJS)
	$(LD) -shared -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(TESTEXE): %: %.o $(LIB) $(TESTLIB)
	$(LD) -o $@ $^ $(LDFLAGS) $(LDLIBS) -g
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH): ./$@ --log_level=message

clean:
	rm -f $(DEPS) $(TESTEXE) $(LIB) $(TESTLIB)

