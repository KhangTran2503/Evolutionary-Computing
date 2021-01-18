#  Reference: https://github.com/scmaree/HillVallEA/blob/master/Makefile
#  Makefile for HillVallEA (GECCO 2018)
#  Author  : S.C Maree 
# Call 'make all' : to build using your favorite compiler
# Call 'make run' : to run program pso.cpp 
# Call 'make clean_run' : to clean file run PSO 
CC = g++
CFLAGS = -O3 -std=c++11


PSO_DIR := ./src
PSO_SRC_FILES := $(wildcard $(PSO_DIR)/*.cpp)
PSO_OBJ_FILES := $(patsubst $(PSO_DIR)/%.cpp,$(PSO_DIR)/%.o,$(PSO_SRC_FILES))
PSO_DEP_FILES := $(patsubst $(PSO_DIR)/%.cpp,$(PSO_DIR)/%.d,$(PSO_SRC_FILES))

all: PSO clean 
run: ./PSO
PSO: PSO.o $(PSO_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ PSO.o $(PSO_OBJ_FILES)
	
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(PSO_OBJ_FILES) $(PSO_DEP_FILES) *.o *.d

clean_run: 
	rm -f PSO
