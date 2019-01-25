output:  
	mpicc -o prog1 prog1.c

run: 
	mpirun -np $(p) ./prog1 $(n) $(r)

clean: 
	rm *.o cpssim

