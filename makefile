CXX := g++
CC  := gcc
AR  := ar

BIN := bin
BUILD := build

TARGET := $(BIN)/TrayRacer
GLFW_LIB := $(BIN)/lib/libglfw.a

CPPFLAGS := \
	-Isrc/TrayRacer \
	-Ivendor/imgui \
	-Ivendor/imgui/backends \
	-Ivendor/glfw/include \
	-Ivendor/glm \
	-Ivendor/stb_image

CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -g

CFLAGS := -std=c11 -Wall -Wextra -O2 -g \
	-D_GLFW_X11 \
	-D_GNU_SOURCE

LDLIBS := \
	-lvulkan \
	-lX11 \
	-lXrandr \
	-lXi \
	-lXinerama \
	-lXcursor \
	-lXxf86vm \
	-ldl \
	-lpthread \

CPP_SRC := $(wildcard \
	src/TrayRacer/*.cpp \
	src/TrayRacer/Input/*.cpp \
	TrayRacerApp/src/*.cpp \
	vendor/imgui/*.cpp)

CPP_SRC += \
	vendor/imgui/backends/imgui_impl_glfw.cpp \
	vendor/imgui/backends/imgui_impl_vulkan.cpp

CPP_OBJ := $(patsubst %.cpp,$(BUILD)/%.o,$(CPP_SRC))

GLFW_SRC := $(wildcard vendor/glfw/src/*.c)
GLFW_OBJ := $(patsubst %.c,$(BUILD)/%.o,$(GLFW_SRC))

.PHONY: all clean run glfw

all: $(TARGET)

$(TARGET): $(CPP_OBJ) $(GLFW_LIB)
	@mkdir -p $(BIN)
	$(CXX) $^ $(LDLIBS) -o $@

$(GLFW_LIB): $(GLFW_OBJ)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

$(BUILD)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

glfw: $(GLFW_LIB)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD) $(BIN)
