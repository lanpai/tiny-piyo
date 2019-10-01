BINARY = tiny-piyo
OBJS = IGLSLShader.o Mesh.o Shaders.o Camera.o Window.o IEngine.o Input.o main.o
OBJS_C = glew.o

BUILD_DIR = build
OBJ_DIR = obj

LIB = -lGL -lglfw -lGLEW

ifeq ($(OS),Windows_NT)
	LIB = -lopengl32 -lglfw3 -lgdi32
	BINARY := $(BINARY).exe
	RUN_PREFIX = start
endif

output: $(OBJS_C) $(OBJS)
	@mkdir -p $(BUILD_DIR)
	cd $(OBJ_DIR); g++ -Wall -std=c++11 $(OBJS) $(OBJS_C) -o ../$(BUILD_DIR)/$(BINARY) $(LIB)

$(OBJS_C): %.o: %.c
	@mkdir -p ${OBJ_DIR}
	cd $(OBJ_DIR); g++ -w -c ../$< $(LIB)

$(OBJS): %.o: %.cpp
	@mkdir -p ${OBJ_DIR}
	cd $(OBJ_DIR); g++ -Wall -std=c++11 -c ../$< $(LIB)

run:
	$(RUN_PREFIX) $(BUILD_DIR)/$(BINARY)

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)
