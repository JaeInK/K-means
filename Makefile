all: nonparallel thread process

nonparallel: nonparallel.cpp
	clang++-3.8 -o nonparallel nonparallel.cpp 
  
thread: thread.cpp
	clang++-3.8 -o thread thread.cpp -lpthread
 
process: process.cpp
	clang++-3.8 -o process process.cpp

clean:
	rm nonparallel
	rm thread
	rm process
