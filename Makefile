BINARY=shaders

BUILD_DIR=build
OBJ_DIR=obj

ifeq ($(OS),Windows_NT)
	LIB+=-lmingw32
	BINARY+=.exe
endif

LIB += -lGL -lglfw -lGLEW

output: GLSLProgram.o Camera.o main.o
	@mkdir -p ${BUILD_DIR}
	cd ${OBJ_DIR}; g++ -Wall $(SUBSYSTEM) GLSLProgram.o Camera.o main.o -o ../${BUILD_DIR}/$(BINARY) $(LIB)

GLSLProgram.o: GLSLProgram.cpp
	@mkdir -p ${OBJ_DIR}
	cd ${OBJ_DIR}; g++ -Wall -c ../GLSLProgram.cpp ${LIB}

Camera.o: Camera.cpp
	@mkdir -p ${OBJ_DIR}
	cd ${OBJ_DIR}; g++ -Wall -c ../Camera.cpp ${LIB}

main.o: main.cpp
	@mkdir -p ${OBJ_DIR}
	cd ${OBJ_DIR}; g++ -Wall -c ../main.cpp $(LIB)

clean:
	rm -rf ${OBJ_DIR} ${BUILD_DIR}
