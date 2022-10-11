TARGET   = libsubmet

# MODULES are all .C/.h file combinations containing your own classes except the ones which have to put in a shared library
# The ROOT linkage has to be specified in 'LinkDef.h'
MODULES = SPulse SEvent

CXXFLAGS := -fPIC -I`root-config --incdir`
LDFLAGS  := -shared `root-config --libs`

all: $(TARGET).so

$(TARGET).so: $(addsuffix .o,$(MODULES)) $(TARGET)Dict.o
	$(CXX) -fPIC -O2 -shared $^ -o $@

$(TARGET)Dict.C: $(addsuffix .h,$(MODULES)) LinkDef.h
	rootcint -f $@ -c -p $^

%.o: %.C 
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm $(TARGET).so
	-rm $(addsuffix .o,$(MODULES))
	-rm *Dict.*
