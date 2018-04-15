all: nonparallel.out thread.out process.out

nonparallel.out: nonparallel.cpp
	clang++-3.8 -o nonparallel nonparallel.cpp 
  
thread.out: thread.cpp
	clang++-3.8 -o thread thread.cpp -lpthread
 
process.out: process.cpp
	clang++-3.8 -o process process.cpp

clean:
	rm nonparallel
	rm thread
	rm process
