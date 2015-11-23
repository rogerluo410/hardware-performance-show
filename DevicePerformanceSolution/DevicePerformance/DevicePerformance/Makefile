CC = g++
CC_FLAG	= -D_NOMNG -D_FILELINE -fPIC
DIR_LIB = ./lib_linux
DIR_OBJ = ./obj_linux

LIB_NAME = libDevicePerformance
OBJ	= DevicePerformance.o DevicePerformanceInstance.o
SHARE_LIB	:= $(DIR_LIB)/$(LIB_NAME).so
OBJ_IN_DIR	:= $(DIR_OBJ)/DevicePerformance.o $(DIR_OBJ)/DevicePerformanceInstance.o
 
all:$(SHARE_LIB)

$(SHARE_LIB):$(OBJ)
	$(CC) -shared -o $@ $(OBJ_IN_DIR)

.SUFFIXES: .c .o .cpp
.cpp.o:
	$(CC) $(CC_FLAG) $(INC) -c $*.cpp -o $(DIR_OBJ)/$*.o

install:
	cp -r ./DevicePerformance.h ./lib_linux/libDevicePerformance.so ../Linux

clean:
	rm -rf $(DIR_OBJ)/*.o $(DIR_LIB)/*.so


