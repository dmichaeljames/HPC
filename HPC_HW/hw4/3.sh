#!/bin/bash
#SBATCH -o p2.out
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH -p defq

mpirun hw4_p2p_block_dotprod
