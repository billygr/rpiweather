CXXFLAGS=-Wall -DVERSION=\"$(GIT_VERSION)\"
CCFLAGS=

GIT_VERSION := $(shell git describe --dirty --always --tags)

all: rpiweather

rpiweather: RCSwitch.o RcOok.o Sensor.o data-sparkfun-post.o rpiweather.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lcurl

debug: CXXFLAGS += -DDEBUG
debug: CCFLAGS += -DDEBUG
debug: all

clean:
	$(RM) *.o rpiweather
