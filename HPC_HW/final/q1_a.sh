#!/bin/bash
#SBATCH -o q1_a.out
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=16
#SBATCH -p defq

module add openmpi/gcc/64/1.10.1
mpirun q1_a 1