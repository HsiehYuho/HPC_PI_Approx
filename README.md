# HPC_PI_Approx

## Descrption
Introduction to High Performance Computing assignment 1, calculating pi approximation using MPI and dartboard algorithm.

## Prerequisite
	* MPI 

## Environment
	Mac OS 10.14.2

## Run
Git glone the repo then
```
cd HPC_PI_Approx  
```
```
make
```

Then run the command:
```
make run p=NUM_OF_PROCESSOR n=NUM_OF_DARTS r=NUM_OF_ITERATION
```

For example:
```
make run p=2 n=100 r=2
```

The above is equivalent to the following command
```
mpirun -np 2 ./100 2
```
You should be able to see the output of:
```
Approx PI: X.XXXXXX
```