#
# Makefile per il simulatore di volo 
#
# Alessandro Bacchini 24-04-2014
#
#

# The compiler
FC = gcc
# flags for debugging or for maximum performance, comment as necessary
#FCFLAGS = -g -fbounds-check
#FCFLAGS = -O2 -cpp

OBJECTS = readMatrix.c printMatrix2.c readMatrix2.c printMatrix3.c readMatrix3.c atmoT.c main.c readDba.c readEngine.c readPropeller.c interp.c printMatrix.c  atmoPressure.c atmoDensity.c atmoC.c propel.c mathModel.c ode1.c writeResults.c readInput.c

NAME = simulatore

# "make" builds all
all: ${NAME}

${NAME}: ${OBJECTS}
	${FC} ${OBJECTS} -o ${NAME} -lm
%.o : %.c
	${FC} -c $*.c -o $*.o

clean: 
	rm -f *.o *.mod *.MOD
