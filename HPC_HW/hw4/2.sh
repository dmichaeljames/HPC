#!/bin/bash
#SBATCH -o p2.out
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH -p med_mem

module add openmpi/gcc/64/1.10.1
mpirun hw4_p2p_block_dotprod
