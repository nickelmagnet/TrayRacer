CXX := g++
CC  := gcc
AR  := ar

BIN := bin
BUILD := build

CONFIG ?= Debug

TARGET := $(BIN)/$(CONFIG)/TrayRacer
GLFW_LIB := $(BIN)/$(CONFIG)/lib/libglfw.a

CPPFLAGS := \
	-Icore \
	-Iapp/TrayRacer \
	-isystem vendor/imgui \
	-isystem vendor/imgui/backends \
	-isystem vendor/glfw/include \
	-isystem vendor/glm \
	-isystem vendor/stb_image

ifeq ($(CONFIG),Debug)
    CXXFLAGS := -std=c++17 -Wall -Wextra -MMD -MP -O0 -g 
    CFLAGS   := -std=c11 -Wall -Wextra -MMD -MP -O0 -g -D_GLFW_X11 -D_GNU_SOURCE
else ifeq ($(CONFIG),Release)
    CXXFLAGS := -std=c++17 -Wall -Wextra -MMD -MP -O2
    CFLAGS   := -std=c11 -Wall -Wextra -MMD -MP -O2 -D_GLFW_X11 -D_GNU_SOURCE
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
	core/*.cpp \
	core/Input/*.cpp \
	app/*.cpp \
	app/TrayRacer/*.cpp \
	vendor/imgui/*.cpp)

CPP_SRC += \
	vendor/imgui/backends/imgui_impl_glfw.cpp \
	vendor/imgui/backends/imgui_impl_vulkan.cpp

CPP_OBJ := $(patsubst %.cpp,$(BUILD)/$(CONFIG)/%.o,$(CPP_SRC))

GLFW_SRC := $(wildcard vendor/glfw/src/*.c)
GLFW_OBJ := $(patsubst %.c,$(BUILD)/$(CONFIG)/%.o,$(GLFW_SRC))

.PHONY: all clean test run glfw debug release

all: $(TARGET)

$(TARGET): $(CPP_OBJ) | $(GLFW_LIB)
	@mkdir -p $(dir $@)
	$(CXX) $(CPP_OBJ) $(GLFW_LIB) $(LDLIBS) -o $@

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
	@$(MAKE) CONFIG=Debug all > debug.log 2>&1 || (echo "Debug build failed" && cat debug.log && rm -f debug.log && exit 1)
	@rm -f debug.log
	@echo "Debug build succeeded."

release:
	@$(MAKE) -j$(nproc) CONFIG=Release all > release.log 2>&1 || (echo "Release build failed" && cat release.log && rm -f release.log && exit 1)
	@rm -f release.log
	@echo "Release build succeeded."

test:
	@$(MAKE) debug
	./$(BIN)/Debug/TrayRacer

run:
	@$(MAKE) release
	./$(BIN)/Release/TrayRacer

clean:
	rm -rf $(BUILD) $(BIN)

-include $(CPP_OBJ:.o=.d) $(GLFW_OBJ:.o=.d)
