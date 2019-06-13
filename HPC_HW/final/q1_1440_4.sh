#!/bin/bash
#SBATCH -o q1_1440_4.out
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4
#SBATCH -p defq

module add openmpi/gcc/64/1.10.1
mpirun q1_a 1