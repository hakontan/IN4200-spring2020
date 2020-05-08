flags = gcc -O3 -std=c11 -Wall
mpi_flag = mpicc -O3 -std=c11 -Wall

serial_prog = serial_count.out
mpi_prog = mpi_count.out

all:	${mpi_prog} ${serial_prog}


${mpi_prog} : mpi_main.c
			${mpi_flag} mpi_main.c -o ${mpi_prog}

${serial_prog} : serial_main.c
				${flags} serial_main.c -o ${serial_prog}


clean:
		rm *.out