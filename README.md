# HPC_PI_Approx

## Descrption
Introduction to High Performance Computing assignment 1, calculating pi approximation using MPI and dartboard algorithm.

## Prerequisite
MPI 

## Environment
	Mac OS 10.14.2

## Run

1. Git clone the repo.
2. Using makefile to compile .c file(s)
3. Run the exmaple command (p=NUM_OF_PROCESSOR n=NUM_OF_DARTS r=NUM_OF_ITERATION)
4. You should be able to see the output.
Note: please install MPI beforehand. 

```
cd HPC_PI_Approx  
make
make run p=2 n=5000000 r=2

// Output:
N=500000, R=2, P=2, PI=X.XXXXXX
Time=XXX.XXXXXX

```

The example command is equivalent
```
mpirun -np 2 ./prog1 5000000 2
```
