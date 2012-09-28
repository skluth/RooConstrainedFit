
# GNU makefile for RooConstrainedFit
# S. Kluth 9/2012

LD = $(CXX)
CXXFLAGS = -Wall -fPIC

LIBFILES = Constraints.cc ClsqSolver.cc
TESTFILE = testConstraints.cc
TESTEXE = $(basename $(TESTFILE) )
LIBOBJS = $(LIBFILES:.cc=.o)
LIB = libRooConstrainedFit.so
DEPS = $(LIBFILES:.cc=.d) $(TESTFILE:.cc=.d)
PROJECTPATH = $(shell echo $${PWD%/*} )
CPPFLAGS = -I $(PROJECTPATH)/RooAverageTools
LDFLAGS = -L $(PROJECTPATH)/RooAverageTools
LDLIBS = -lRooAverageTools -lMatrix
ifdef HEPROOT
CPPFLAGS += -I $(HEPROOT)/include -I $(HEPROOT)/include/boost-1_48/
LDFLAGS += -L $(HEPROOT)/lib64
LDLIBS += -lboost_unit_test_framework-gcc46-mt-1_48
else
CPPFLAGS += -I $(ROOTSYS)/include
LDFLAGS += -L $(ROOTSYS)/lib 
LDLIBS += -lboost_unit_test_framework
endif
LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):$(PROJECTPATH)/RooAverageTools:$(PROJECTPATH)/INIParser


all: $(TESTEXE)

$(DEPS): %.d: %.cc
	$(CXX) $(CPPFLAGS) -MM $< -MF $@
-include $(DEPS)

$(LIB): $(LIBOBJS)
	$(LD) -shared -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(TESTEXE): %: %.o $(LIB)
	$(LD) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH): ./$@ --log_level=message

clean:
	rm -f *.o $(DEPS) $(TESTEXE) $(LIB)

