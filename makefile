TARGET_EXEC ?= a.out

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

CC = g++

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# find <dir> -type d returns all directories in <dir>
# it's an overkill
#INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_DIRS := ./include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

LIB_DIRS := ./lib
LDFLAGS := $(addprefix -L,$(LIB_DIRS)) -lGL -lGLEW -lglfw3 -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp

CPPFLAGS ?= $(INC_FLAGS) -g -Wall -std=c++2a

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p