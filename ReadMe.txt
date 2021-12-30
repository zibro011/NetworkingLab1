INET4001
Lab 1
Adelaide Zibrowski
October 20, 2021

I/O:
	When prompted, user enters a command. If it is built-in (showStats or showProcs), a new thread is
	created and the corresponding function results are printed to the screen. If not, a new process 
	is created and run. User continues to enter commands until the user inputs "quit" at which time the
	program is terminated.

Functions:
	showStats: creates new thread, increments numThreads, and prints results of numThreads to screen

	showProcs: creates new thread, increments numThreads, and prints result of numProcs to screen

	fileOut: prints results of showStats and showProcs to output file every 5 seconds