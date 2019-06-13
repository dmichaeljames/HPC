#!/bin/bash
#SBATCH -o p2_2.out
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH -p defq

module add openmpi/gcc/64/1.10.1
mpirun a.out 2
