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

Nordic Test Results
https://github.com/mansetagunj/PES_Assignment/blob/master/Project3/Time%20Profiler%20Results/Nordic%20Test%20Results.txt

Observations:
For FRDM_KL25Z, the DMA version takes a significantly lesser time than the non-DMA version, since the transfer is offloaded from the processor. Further, for the non-DMA version, the transfer time is reduced with increase in optimization to O3. The least amount of time however, is for the standard library function.

On increasing the number of transferred bytes from 10 upto 1000 bytes, the time required per byte transfer drops gradually.

Makefile Description:
Builds and Compile Time switches available:
		1. compile-all 	: Compiles all the .c/.s files to .o files \n\
		2. build	: Compiles and Links all the .o files to .elf output file\n \
		3. clean	: Cleans all the make generated files \n\
		4. generate-lib	: Generates the .a library from .o files \n\
		5. build-lib	: Generates the .a library, links it with main.o to generate .elf output file\n \
		6. size		: Executes 2. build target and creates a code size file.\n \
		7. code-dump-report	:Generates the code dump report \n \
		8. clean-lib	: Cleans the library created \n \
		9. help		: Shows all the builds and compile time switch available \n \
		Switches available:\n\
		1. PLATFORM = { HOST, BBB, KL25Z }\n \
		2. VERBOSE  = true\n"


Extra Credit Work:
1. Python Script to interpret data from Binary Logger: The Python Script used for this work, a sample binary log file and a snapshot of the interpreted output can be found inside the folder 'Python Script Extra Credit'
2. Accurate Time Stamp: The current epoch time is fetched at run time and fed into the epoch seconds register for accurate time stamps during logging
3. Wireless communication: The part attempted for this extra credit work can be found through the functions NRF_transmit_data, NRF_read_data and NRF_mode_configure inside the file nordic_driver.c. Currently, an interrupt is getting generated on Nordic's IRQ pin, but there is an issue while flushing out the whole buffer.
