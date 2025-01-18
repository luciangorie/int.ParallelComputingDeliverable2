# int.ParallelComputingDeliverable2
here is the repository for int.PARCO H2/D2



You can find:

some example of implementations of main (proj.cpp -> works for serial and implicitly parallelized solution, selects the option by reading if a -true is passed by the command line or not; modified from last time, in order to include copy process in time check.  projMPIG(N).cpp  -> MPI block based main functions, for N=4,9,16, projMPIG.cpp for RowBased solution with AlltoAll and projMPIGB9.cpp for partial solution (without collection) og 9 blocks based transposition for further checks if needed.

official document IEEE also submitted via e-mail and assignment in PDF
-PBS files, that can be used in order to execute codes on the HPC cluster of UniTN in the same manner I did: { testp1.pbs is for executing proj1.cpp (serial part) , t4.pbs t9.pbs and t16.pbs are for ProjMPIG4.cpp, ProjMPIG9.cpp and ProjMPIG16.cpp launch. testBaseRows.pbs for projMPIG.cpp and testBlock9.pbs for projMPIGB9.cpp
!!! ATTENTION: Please change the final directory with your name and the address you keep the cpp program stored.!!! pbs files can be launched with qsub name.pbs and job status can be checked with qstat name_account.
!!! All pbs files have a default space request between 800 mb and 2000 mb, feel free to adapt for necessity , after reading space usage considerations on PDF section. 
Segmentation faults or other mistakes can happen due to wrong space requests.
}

-header files with transposition functions and other features (Do not change anything, excluded the size N in matrice_h)

- Graphs for strong and weak scaling of OMP and MPI approaches
- File for visualization of block based transposition logic
- cpp code as tool used to calculate peak performance (no pbs, can run on laptop).

The main can also be created autonomously by the user that can customize an execution for different needs. be aware that:

-transposing more times the same matrix can give misleading results as data could already be in the cache or in faster memory. -the program can run everywhere, but not every N for matrix size could work in every system (calculate memory usage by calculating NN4 bytes for each matrix present in the code). MPI version given is not portable on average laptops achitechtures, as are needed more cpus.

Alessandro Luzzani
