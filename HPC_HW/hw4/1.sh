#!/bin/bash
#SBATCH -o p8.out
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=8
#SBATCH -p defq

mpirun hw4_p2p_block_dotprod
