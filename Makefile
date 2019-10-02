ifeq ($(CC),)
	CC := clang
endif

ifeq ($(CXX),)
	CXX := clang++
endif

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

BINARY = libtiny-piyo.a
HEADER_DIR = tiny-piyo
OBJS = IGLSLShader.o Mesh.o Shaders.o Camera.o Window.o IEngine.o Input.o
OBJS_C = glew.o

BUILD_DIR = build
OBJ_DIR = obj

LIB = -lGL -lglfw -lGLEW

output: $(OBJS_C) $(OBJS)
	@mkdir -p $(BUILD_DIR)
	cd $(OBJ_DIR); $(AR) rcs ../$(BUILD_DIR)/$(BINARY) $(OBJS_C) $(OBJS)

$(OBJS_C): %.o: %.c
	@mkdir -p ${OBJ_DIR}
	cd $(OBJ_DIR); $(CC) -w -c ../$<

$(OBJS): %.o: %.cpp
	@mkdir -p ${OBJ_DIR}
	cd $(OBJ_DIR); $(CXX) -Wall -std=c++11 -c ../$<

install: $(BUILD_DIR)/$(BINARY)
	install -d $(DEST_DIR)$(PREFIX)/lib/
	cd $(BUILD_DIR); install -m 644 $(BINARY) $(DEST_DIR)$(PREFIX)/lib/
	install -d $(DEST_DIR)$(PREFIX)/include/$(HEADER_DIR)/
	install -m 644 *.h $(DEST_DIR)$(PREFIX)/include/$(HEADER_DIR)/

run:
	$(BUILD_DIR)/$(BINARY)

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)
