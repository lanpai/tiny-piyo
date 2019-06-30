BINARY = shaders
OBJS = GLSLProgram.o Camera.o Window.o IEngine.o Input.o main.o
OBJS_C = glew.o

BUILD_DIR = build
OBJ_DIR = obj

LIB = -lGL -lglfw -lGLEW

ifeq ($(OS),Windows_NT)
	LIB = -lmingw32 -lopengl32 -lglfw3 -lgdi32
	BINARY := $(BINARY).exe
endif

output: $(OBJS_C) $(OBJS)
	@mkdir -p $(BUILD_DIR)
	cd $(OBJ_DIR); g++ -Wall $(SUBSYSTEM) $(OBJS) $(OBJS_C) -o ../$(BUILD_DIR)/$(BINARY) $(LIB)

$(OBJS_C): %.o: %.c
	@mkdir -p $(BUILD_DIR)
	cd $(OBJ_DIR); g++ -w -c ../$< $(LIB)

$(OBJS): %.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	cd $(OBJ_DIR); g++ -Wall -c ../$< $(LIB)

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)
