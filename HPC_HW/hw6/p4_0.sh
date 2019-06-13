#!/bin/bash
#SBATCH -o p4_0.out
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4
#SBATCH -p defq

module add openmpi/gcc/64/1.10.1
mpirun a.out 0
