#  Reference: https://github.com/scmaree/HillVallEA/blob/master/Makefile
#  Makefile for HillVallEA (GECCO 2018)
#  Author  : S.C Maree 
# Call 'make all' to build using your favorite compiler
# Call 'make run; to run program SimpleGAs.cpp 

CC = g++
CFLAGS = -O3 -std=c++11 -MMD


POPOP_DIR := ./src
POPOP_SRC_FILES := $(wildcard $(POPOP_DIR)/*.cpp)
POPOP_OBJ_FILES := $(patsubst $(POPOP_DIR)/%.cpp,$(POPOP_DIR)/%.o,$(POPOP_SRC_FILES))
POPOP_DEP_FILES := $(patsubst $(POPOP_DIR)/%.cpp,$(POPOP_DIR)/%.d,$(POPOP_SRC_FILES))

all: SimpleGAs clean 
run: exc clean_run 
SimpleGAs: SimpleGAs.o $(POPOP_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ SimpleGAs.o $(POPOP_OBJ_FILES)
	
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(POPOP_OBJ_FILES) $(POPOP_DEP_FILES) *.o *.d

exc:
	./SimpleGAs
clean_run: 
	rm -f SimpleGAs
