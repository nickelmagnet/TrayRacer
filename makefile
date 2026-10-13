CXX := g++
CC  := gcc
AR  := ar

BIN := bin
BUILD := build

TARGET := $(BIN)/$(CONFIG)/TrayRacer
GLFW_LIB := $(BIN)/$(CONFIG)/lib/libglfw.a

CPPFLAGS := \
	-Isrc/TrayRacer \
	-Ivendor/imgui \
	-Ivendor/imgui/backends \
	-Ivendor/glfw/include \
	-Ivendor/glm \
	-Ivendor/stb_image

CONFIG ?= Debug

ifeq ($(CONFIG),Debug)
    CXXFLAGS := -std=c++17 -Wall -Wextra -O0 -g 
    CFLAGS   := -std=c11 -Wall -Wextra -O0 -g -D_GLFW_X11 -D_GNU_SOURCE
else ifeq ($(CONFIG),Release)
    CXXFLAGS := -std=c++17 -Wall -Wextra -O2
    CFLAGS   := -std=c11 -Wall -Wextra -O2 -D_GLFW_X11 -D_GNU_SOURCE
endif

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

CPP_OBJ := $(patsubst %.cpp,$(BUILD)/$(CONFIG)/%.o,$(CPP_SRC))

GLFW_SRC := $(wildcard vendor/glfw/src/*.c)
GLFW_OBJ := $(patsubst %.c,$(BUILD)/$(CONFIG)/%.o,$(GLFW_SRC))

.PHONY: all clean run glfw debug release

all: $(TARGET)

$(TARGET): $(CPP_OBJ) $(GLFW_LIB)
	@mkdir -p $(BIN)
	$(CXX) $^ $(LDLIBS) -o $@

$(GLFW_LIB): $(GLFW_OBJ)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

$(BUILD)/$(CONFIG)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD)/$(CONFIG)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

glfw: $(GLFW_LIB)

debug:
	@$(MAKE) CONFIG=Debug all > build/debug.log 2>&1 || (echo "Debug build failed. See build/debug.log" && exit 1)
	@echo "Debug build succeeded."

release:
	@$(MAKE) -j$(nproc) CONFIG=Release all > build/release.log 2>&1 || (echo "Release build failed. See build/release.log" && exit 1)
	@echo "Release build succeeded."

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD) $(BIN)
