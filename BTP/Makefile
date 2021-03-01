all : TestDataGenerator TestNewApproach

TestNewApproach : TestNewApproach.out
	$ ./TestNewApproach.out

TestNewApproach.out : TestNewApproach.cpp utils.cpp constants.h 
	$ g++ TestNewApproach.cpp -o TestNewApproach.out 

TestDataGenerator : TestDataGenerator.out
	$ ./TestDataGenerator.out

TestDataGenerator.out : TestDataGenerator.cpp constants.h
	$ g++ TestDataGenerator.cpp -o TestDataGenerator.out

clean :
	rm -rf *.out