flags = gcc -O3 -Wall -std=c11
mpiflags = mpicc -O3 -Wall -std=c11

name = serial_main.out
mpi_name = mpi_main.out


all: $(name) $(mpi_name)

$(name): serial_main.c
	$(flags) serial_main.c -o $(name)

$(mpi_name): mpi_main.c
	$(mpiflags) mpi_main.c -o $(mpi_name)

	
clean: 
	rm $(name) $(mpi_name)