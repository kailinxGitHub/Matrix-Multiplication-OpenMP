#!/bin/bash
#SBATCH --job-name=hello_world    # Names the job for easier identification
#SBATCH --output=hello_output.txt  # Redirects output to a file named "hello_output.txt"
#SBATCH --ntasks=1                 # Specifies that the job will run a single task (1 CPU core)
#SBATCH --time=00:01:00            # Sets the maximum runtime to 1 minute
#SBATCH --partition=standard       # Specifies the partition (queue) to use for the job
