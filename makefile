# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
# DO NOT MODIFY THIS MAKEFILE
# CHANGE OS SPECIFIC SETTINGS IN makefile_presets

PRESET_FILE := makefile_presets

ifeq ($(OS),Windows_NT)
	CONTENT = (echo \# Change the main here and other os specific settings & echo \# Do not commit this file & echo. & echo \# Relative link to the main file & echo TARGET_EXEC_FILE := main.cpp & echo. & echo CC = g++ & echo. & echo \# Extra Flags for compilation & echo EXTRA_FLAGS :=& echo. & echo \# c++ version & echo CPP_VER := -std=c++11 & echo. & echo \# Warning flags & echo WFLAGS := -Wall -Wextra -Wno-unused -Wno-unused-parameter -Wno-ignored-qualifiers)
else
	CONTENT = echo "\# Change the main here and other os specific settings\n\# Do not commit this file\n\n\# Relative link to the main file\nTARGET_EXEC_FILE := main.cpp\n\nCC = g++\n\n\# Extra Flags for compilation\nEXTRA_FLAGS :=\n\n\# c++ version\nCPP_VER := -std=c++11\n\n\# Warning flags\nWFLAGS := -Wall -Wextra -Wno-unused -Wno-unused-parameter -Wno-ignored-qualifiers"
endif

ifeq ($(strip $(wildcard $(PRESET_FILE))),)
	RES := $(shell $(CONTENT) > $(PRESET_FILE))
endif

include $(PRESET_FILE)

ifeq ($(OS),Windows_NT)
    FILESEP := \\
    MKDIR := mkdir
    DELETE := rd /s
else
    FILESEP := /
    MKDIR := mkdir -p
    DELETE := rm -r
endif

NULL :=
SPACE := $(NULL)

BUILD_DIR := .$(FILESEP)build
SRC_DIRS := .$(FILESEP)src
PREFIX_TESTFILES := main
PATHMAKEFILE := $(realpath makefile)
ABSOLUTEPATHPREFFIX = $(PATHMAKEFILE:%makefile=%)
TARGET_EXEC := $(basename $(TARGET_EXEC_FILE))
#TARGET_EXEC := main.cpp




# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
ifeq ($(OS),Windows_NT)
	ABSOLUTEPATHPREFFIX := $(subst /,\,$(ABSOLUTEPATHPREFFIX))
	ABSOLUTEPATHPREFFIX := $(strip $(ABSOLUTEPATHPREFFIX)\ )
	ABSSRCS := $(shell dir $(SRC_DIRS)\*.cpp /b/s | findstr /v/c:"\\$(PREFIX_TESTFILES)")
	SRCS := $(ABSSRCS:$(ABSOLUTEPATHPREFFIX)%=.$(FILESEP)%)
else
	SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -and -not -name '$(PREFIX_TESTFILES)*.cpp')
endif

SRCS += $(TARGET_EXEC).cpp

# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.o

OBJS := $(SRCS:%.cpp=$(BUILD_DIR)$(FILESEP)%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.o turns into ./build/hello.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
ifeq ($(OS),Windows_NT)
	INC_DIRS_WINDOWS := $(shell dir $(SRC_DIRS) /b/s/a:d)
	INC_DIRS := $(INC_DIRS_WINDOWS:$(ABSOLUTEPATHPREFFIX)%=.$(FILESEP)%)
else
	INC_DIRS := $(shell find $(SRC_DIRS) -type d)
endif

# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(WFLAGS) $(CPP_VER) -c $(EXTRA_FLAGS) $(INC_FLAGS) -MMD -MP -D DATA_ROOT="\"$(ABSOLUTEPATHPREFFIX)data\"" -D FILE_SEP="\"$(FILESEP)\""

#LDFLAGS := -ljsoncpp

# The final build step.
$(BUILD_DIR)$(FILESEP)$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(EXTRA_FLAGS)

# Build step for C++ source
ifeq ($(OS),Windows_NT)
$(BUILD_DIR)$(FILESEP)%.o: %.cpp
	IF not exist "$(dir $@)" ($(MKDIR) "$(dir $@)")
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
else
$(BUILD_DIR)$(FILESEP)%.o: %.cpp
	$(MKDIR) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
endif

cleanrun : cleanExec run

run : all
	$(BUILD_DIR)$(FILESEP)$(TARGET_EXEC)

all : $(BUILD_DIR)$(FILESEP)$(TARGET_EXEC)


.PHONY: clean run cleanExec all
cleanExec:
	$(DELETE) $(BUILD_DIR)$(FILESEP)$(TARGET_EXEC) $(BUILD_DIR)$(FILESEP)$(TARGET_EXEC).o
clean:
	$(DELETE) $(BUILD_DIR)
clean$(FILESEP)%:
	$(DELETE) $(subst clean, $(BUILD_DIR), $@)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)
