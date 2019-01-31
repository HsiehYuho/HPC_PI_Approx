output:  
	mpicxx -o prog1 prog1.cpp

run: 
	mpirun -np $(p) ./prog1 $(n) $(r)

clean: 
	rm *.o cpssim

