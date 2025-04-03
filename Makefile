all: PhotoLab PhotoLabTest

PhotoLab: PhotoLab.o DIPs.o FileIO.o Advanced.o Image.o Test.o libfilter.a
	gcc -Wall -g -std=c11 -o PhotoLab PhotoLab.o DIPs.o FileIO.o Advanced.o Image.o Test.o -L. -lfilter -lm

PhotoLabTest: PhotoLabDebug.o DIPs.o FileIO.o Advanced.o Image.o Test.o libfilter.a
	gcc -Wall -g -std=c11 -o PhotoLabTest PhotoLabDebug.o DIPs.o FileIO.o Advanced.o Image.o Test.o -L. -lfilter -lm

libfilter.a: PhotoLab.o DIPs.o FileIO.o Advanced.o Image.o Test.o
	ar rcs libfilter.a PhotoLab.o DIPs.o FileIO.o Advanced.o Image.o Test.o
	ranlib libfilter.a

PhotoLab.o: PhotoLab.c DIPs.h FileIO.h Advanced.h Image.h Test.h
	gcc -Wall -g -std=c11 -c PhotoLab.c -o PhotoLab.o

PhotoLabDebug.o: PhotoLab.c DIPs.h FileIO.h Advanced.h Image.h Test.h
	gcc -Wall -g -std=c11 -c PhotoLab.c -o PhotoLabDebug.o -DDEBUG

DIPs.o: DIPs.c DIPs.h Image.h
	gcc -Wall -g -std=c11 -c DIPs.c -o DIPs.o

FileIO.o: FileIO.c FileIO.h Image.h
	gcc -Wall -g -std=c11 -c FileIO.c -o FileIO.o

Image.o: Image.c Image.h
	gcc -Wall -g -std=c11 -c Image.c -o Image.o

Advanced.o: Advanced.c Advanced.h Image.h
	gcc -Wall -g -std=c11 -c Advanced.c -o Advanced.o

Test.o: Test.c Test.h Image.h
	gcc -Wall -g -std=c11 -c Test.c -o Test.o

clean:
	rm -f *.o PhotoLab PhotoLabTest libfilter.a
