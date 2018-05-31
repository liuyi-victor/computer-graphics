CC = g++
CFLAGS = -pg -g -O2 -Wall
LDFLAGS = -pg -g
LIBS = -lm

raytracer:  main.cpp raytracer.cpp util.cpp light_source.cpp scene_object.cpp bmp_io.cpp
	$(CC) main.cpp raytracer.cpp util.cpp light_source.cpp scene_object.cpp bmp_io.cpp $(LDFLAGS) -o raytracer #\
	#main.o raytracer.o util.o light_source.o scene_object.o bmp_io.o $(LIBS)

clean:
	-rm -f core *.o
	-rm raytracer
