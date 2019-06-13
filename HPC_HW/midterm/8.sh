#!/bin/bash
#SBATCH -o p8.out
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=8
#SBATCH -p med_mem

module add openmpi/gcc/64/1.10.1
mpirun q2_mpi_pi
