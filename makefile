# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O3 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all	: cb
	@echo -n ""

# optimized version
cb	: src/main.cpp src/build_cycle.h
			$(CC) $(OPTFLAGS) src/main.cpp -o cb

# DEBUG Version
dbg : cb_dbg
	@echo -n ""

cb_dbg	: src/main.cpp src/build_cycle.h
			$(CC) $(DBGFLAGS) src/main.cpp -o cb_dbg

# clean all the .o and executable files
clean:
		rm -rf *.o cb cb_dbg