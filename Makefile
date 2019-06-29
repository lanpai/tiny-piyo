BINARY=shaders

BUILD_DIR=build
OBJ_DIR=obj

ifeq ($(OS),Windows_NT)
	LIB+=-lmingw32
	BINARY:=$(BINARY).exe
endif

LIB += -lGL -lglfw -lGLEW

output: GLSLProgram.o Camera.o Window.o IEngine.o Input.o main.o
	@mkdir -p ${BUILD_DIR}
	cd ${OBJ_DIR}; g++ -Wall $(SUBSYSTEM) GLSLProgram.o Camera.o Window.o IEngine.o Input.o main.o -o ../${BUILD_DIR}/$(BINARY) $(LIB)

GLSLProgram.o: GLSLProgram.cpp
	@mkdir -p ${OBJ_DIR}
	cd ${OBJ_DIR}; g++ -Wall -c ../GLSLProgram.cpp ${LIB}

Camera.o: Camera.cpp
	@mkdir -p ${OBJ_DIR}
	cd ${OBJ_DIR}; g++ -Wall -c ../Camera.cpp ${LIB}

Window.o: Window.cpp
	@mkdir -p ${OBJ_DIR}
	cd ${OBJ_DIR}; g++ -Wall -c ../Window.cpp ${LIB}

IEngine.o: IEngine.cpp
	@mkdir -p ${OBJ_DIR}
	cd ${OBJ_DIR}; g++ -Wall -c ../IEngine.cpp ${LIB}

Input.o: Input.cpp
	@mkdir -p ${OBJ_DIR}
	cd ${OBJ_DIR}; g++ -Wall -c ../Input.cpp ${LIB}

main.o: main.cpp
	@mkdir -p ${OBJ_DIR}
	cd ${OBJ_DIR}; g++ -Wall -c ../main.cpp $(LIB)

clean:
	rm -rf ${OBJ_DIR} ${BUILD_DIR}
