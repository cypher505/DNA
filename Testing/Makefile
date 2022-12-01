CFLAGS = -g -Wall
CC = gcc
TARGETS = testingNM_ALL_INST testingDP_ALL_INST  DIST1vsDIST2 MV 
OBJ = DIST1vsDIST2.o math.o io.o DATA_struct.o small_tests.o  testingNM_ALL_INST.o testingDP_ALL_INST.o
HEDERS =  ../src/math.h ../src/io.h ../src/DATA_struct.h 

all : myProg  $(TARGETS) 

DIST1vsDIST2: DIST1vsDIST2.o math.o io.o DATA_struct.o 
	$(CC) $(CFLAGS) -o DIST1vsDIST2 DIST1vsDIST2.o math.o io.o DATA_struct.o 

DIST1vsDIST2.o : DIST1vsDIST2.c ../src/math.h ../src/io.h ../src/DATA_struct.h .
	$(CC) $(CFLAGS) -c DIST1vsDIST2.c

myProg : small_tests.o math.o io.o DATA_struct.o 
	$(CC) $(CFLAGS) -o myProg small_tests.o math.o io.o DATA_struct.o 

small_tests.o : small_tests.c ../src/math.h ../src/io.h ../src/DATA_struct.h .
	$(CC) $(CFLAGS) -c small_tests.c

testingNM_ALL_INST : testingNM_ALL_INST.o math.o  DATA_struct.o io.o
	$(CC) $(CFLAGS) -o testingNM_ALL_INST testingNM_ALL_INST.o  math.o DATA_struct.o io.o

testingDP_ALL_INST : testingDP_ALL_INST.o  math.o DATA_struct.o io.o 
	$(CC) $(CFLAGS) -o testingDP_ALL_INST testingDP_ALL_INST.o math.o DATA_struct.o io.o 

testingNM_ALL_INST.o : testingNM_ALL_INST.c ../src/math.h ../src/io.h  ../src/DATA_struct.h 
	$(CC) $(CFLAGS) -c testingNM_ALL_INST.c

testingDP_ALL_INST.o :  testingDP_ALL_INST.c  ../src/io.h ../src/math.h ../src/DATA_struct.h 
	$(CC) $(CFLAGS) -c testingDP_ALL_INST.c

##############################################################

io.o : ../src/io.c  ../src/DATA_struct.h   ../src/math.h  
	$(CC)  $(CFLAGS) -c ../src/io.c 

math.o : ../src/math.c ../src/math.h
	$(CC) $(CFLAGS) -c ../src/math.c

DATA_struct.o : ../src/DATA_struct.c ../src/DATA_struct.h ../src/math.h
	$(CC) $(CFLAGS) -c ../src/DATA_struct.c

MV :
	mv *.o build/
	mv myProg ../

clean : 
	rm -f *.o  $(TARGETS) 
	find build/ -type f  -delete
	find ../myProg -delete
	 
