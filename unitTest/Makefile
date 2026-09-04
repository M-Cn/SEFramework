# Compilatore
CC := g++

# Definizioni
DEFINES :=
DEBUG_DEFINES := DEBUG

# Flags
MAIN_FLAGS := -O3 $(addprefix -D,$(DEFINES))
DEBUG_FLAGS := -ggdb -g3 -Wall -Wextra -pedantic $(addprefix -D,$(DEBUG_DEFINES))

# Directory sorgenti
MOCC_LIB := ../mocc
RLIB_LIB := ../rlib
FRAMEWORK_LIB := ../framework
SRC_DIR := .

# Trova tutti i file .cpp
MOCC_CPP := $(wildcard $(MOCC_LIB)/*.cpp)
RLIB_CPP := $(shell find $(RLIB_LIB) -type f -name "*.cpp")
FRAMEWORK_CPP := $(shell find $(FRAMEWORK_LIB) -type f -name "*.cpp")
LOCAL_CPP := $(wildcard $(SRC_DIR)/*.cpp)

# Directory per oggetti e dipendenze
BUILD_DIR := build
MOCC_OBJ := $(patsubst $(MOCC_LIB)/%.cpp,$(BUILD_DIR)/mocc_%.o,$(MOCC_CPP))
RLIB_OBJ := $(patsubst $(RLIB_LIB)/%.cpp,$(BUILD_DIR)/rlib/%.o,$(RLIB_CPP))
FRAMEWORK_OBJ := $(patsubst $(FRAMEWORK_LIB)/%.cpp,$(BUILD_DIR)/framework/%.o,$(FRAMEWORK_CPP))
LOCAL_OBJ := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(LOCAL_CPP))

ALL_OBJ := $(MOCC_OBJ) $(RLIB_OBJ) $(FRAMEWORK_OBJ) $(LOCAL_OBJ)

.PHONY: all clean

all: main

# Target principali
main: CFLAGS := $(MAIN_FLAGS)
main: $(ALL_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

debug: CFLAGS := $(DEBUG_FLAGS)
debug: $(ALL_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Regola per i file locali
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Regola per MOCC
$(BUILD_DIR)/mocc_%.o: $(MOCC_LIB)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Regola per RLIB (gestisce le sottocartelle)
$(BUILD_DIR)/rlib/%.o: $(RLIB_LIB)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Regola per FRAMEWORK (gestisce le sottocartelle)
$(BUILD_DIR)/framework/%.o: $(FRAMEWORK_LIB)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(ALL_OBJ:.o=.d)

# Pulizia
clean:
	rm -rf $(BUILD_DIR) main debug