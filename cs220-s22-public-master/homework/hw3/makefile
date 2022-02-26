CXX=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g

all: png2txt txt2png cs220_paint

txt2png: txt2png.o pnglite.o cs220_paint.o
	$(CXX)  -o txt2png txt2png.o pnglite.o cs220_paint.o -lm -lz
	
png2txt: png2txt.o pnglite.o cs220_paint.o
	$(CXX)  -o png2txt png2txt.o pnglite.o cs220_paint.o -lm -lz

cs220_paint: driver.o cs220_paint.o
	$(CXX)  -o cs220_paint driver.o cs220_paint.o -lm -lz

png2txt.o: png2txt.c pnglite.h cs220_paint.h
	$(CXX) $(CFLAGS) -c png2txt.c

txt2png.o: txt2png.c pnglite.h cs220_paint.h
	$(CXX) $(CFLAGS) -c txt2png.c

pnglite.o: pnglite.h pnglite.c
	$(CXX) $(CFLAGS) -c pnglite.c
	
cs220_paint.o: cs220_paint.h cs220_paint.c
	$(CXX) $(CFLAGS) -c cs220_paint.c

driver.o: cs220_paint.h driver.c
	$(CXX) $(CFLAGS) -c driver.c
clean:
	rm -f *.o txt2png png2txt cs220_paint