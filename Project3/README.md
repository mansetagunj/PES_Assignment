Project3 for PES
Contributors: Gunj Manseta / Ashish Tak

Time profiler results can be found in the "Time Profiler Results" folder

(For BBB and Host, the non-DMA version (my_memmove/my_memset) is called twice instead of the DMA version)

Results on FRDM_KL25Z with -O0
https://github.com/mansetagunj/PES_Assignment/blob/master/Project3/Time%20Profiler%20Results/FRDM_normal_results.txt

Results on FRDM_KL25Z with -O3
https://github.com/mansetagunj/PES_Assignment/blob/master/Project3/Time%20Profiler%20Results/FRDM_opt_results.txt

Results on BBB with -O0
https://github.com/mansetagunj/PES_Assignment/blob/master/Project3/Time%20Profiler%20Results/BBB_normal_results.txt

Results on  BBB with -O3
https://github.com/mansetagunj/PES_Assignment/blob/master/Project3/Time%20Profiler%20Results/BBB_opt_results.txt

Results on Host machine with -O0
https://github.com/mansetagunj/PES_Assignment/blob/master/Project3/Time%20Profiler%20Results/HOST_normal_results.txt

Results on Host machine with -O3
https://github.com/mansetagunj/PES_Assignment/blob/master/Project3/Time%20Profiler%20Results/HOST_opt_results.txt


Observations:
For FRDM_KL25Z, the DMA version takes a significantly lesser time than the non-DMA version, since the transfer is offloaded from the processor. Further, for the non-DMA version, the transfer time is reduced with increase in optimization to O3. The least amount of time however, is for the standard library function.

On increasing the number of transferred bytes from 10 upto 1000 bytes, the time required per byte transfer drops gradually.
