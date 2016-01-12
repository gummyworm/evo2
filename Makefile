PLATFORM = sdl
LIBS  = -lm -lSDL2 -lglew -framework OpenGL
INCLUDE = -I.
CFLAGS = -shared -Wall -fPIC

SRC=$(wildcard *.c)
TESTSRC=$(wildcard testing/*.c)
BASECSRC=$(wildcard components/*.c) # base components for engine
PLATSRC=$(wildcard platform/$(PLATFOMR)/*.c) # platform specific source

libevo2.so: $(SRC) $(BASECSRC) $(PLATSRC)
	gcc -o $@ $^ $(CFLAGS) $(PLATFORM) $(INCLUDE) $(LIBS)

test: $(TESTSRC) libevo2.so 
	cd testing && $(MAKE)
	mv testing/test .

clean:
	rm libevo2.so
	rm test
	cd testing && $(MAKE) clean
