BINARY = shaders
OBJS = GLSLProgram.o Camera.o Window.o IEngine.o Input.o main.o

BUILD_DIR = build
OBJ_DIR = obj

ifeq ($(OS),Windows_NT)
	LIB += -lmingw32
	BINARY := $(BINARY).exe
endif

LIB += -lGL -lglfw -lGLEW

output: $(OBJS)
	@mkdir -p ${BUILD_DIR}
	cd ${OBJ_DIR}; g++ -Wall $(SUBSYSTEM) $(OBJS) -o ../${BUILD_DIR}/$(BINARY) $(LIB)

$(OBJS): %.o: %.cpp
	@mkdir -p ${OBJ_DIR}
	cd ${OBJ_DIR}; g++ -Wall -c ../$< ${LIB}

clean:
	rm -rf ${OBJ_DIR} ${BUILD_DIR}
