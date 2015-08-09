CXXFLAGS=-Wall

all: rpiweather

rpiweather: RCSwitch.o RcOok.o Sensor.o data-sparkfun-post.o rpiweather.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lcurl

clean:
	$(RM) *.o rpiweather
