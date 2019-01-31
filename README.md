# HPC_PI_Approx

## Description
Introduction to High Performance Computing assignment 1, calculating pi approximation using MPI and dartboard algorithm.

## Prerequisite
MPI 

## Environment
	Mac OS 10.14.2

## Run

1. Git clone the repo.
2. Load mvapich
Note: please install MPI beforehand.
3. Compile
4. Run the example command to analyze speedup
5. An output file output.txt will be generated containing a summary of all runs
Note: To reset output file, delete from directory.

```
cd HPC_PI_Approx
module load gcc mvapich2/2.2
mpicxx -o prog1 prog1.cpp
for p in 1 2 4 8 16; do mpirun -np $p ./prog1 5000000 100; done

// output.txt will contain:
N=5000000, R=2, P=1, PI=X.XXXXXX
Time=XXX.XXXXXX
...
N=5000000, R=2, P=16, PI=X.XXXXXX
Time=XXX.XXXXXX


```
