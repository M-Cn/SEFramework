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
SRC_DIR := .

# Trova tutti i file .cpp
MOCC_CPP := $(wildcard $(MOCC_LIB)/*.cpp)
RLIB_CPP := $(shell find $(RLIB_LIB) -type f -name "*.cpp")
LOCAL_CPP := $(wildcard $(SRC_DIR)/*.cpp)

# Directory per oggetti e dipendenze
BUILD_DIR := build
MOCC_OBJ := $(patsubst $(MOCC_LIB)/%.cpp,$(BUILD_DIR)/mocc_%.o,$(MOCC_CPP))
RLIB_OBJ := $(patsubst $(RLIB_LIB)/%.cpp,$(BUILD_DIR)/rlib/%.o,$(RLIB_CPP))
LOCAL_OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/local_%.o,$(LOCAL_CPP))

ALL_OBJ := $(MOCC_OBJ) $(RLIB_OBJ) $(LOCAL_OBJ)

# Target principali
.PHONY: all main debug clean

all: main

main: CFLAGS := $(MAIN_FLAGS)
main: $(ALL_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

debug: CFLAGS := $(DEBUG_FLAGS)
debug: $(ALL_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Regola per i file sorgente locali
$(BUILD_DIR)/local_%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Regola per MOCC
$(BUILD_DIR)/mocc_%.o: $(MOCC_LIB)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Regola per RLIB (accetta sottocartelle grazie al pattern % nello step di compilazione)
$(BUILD_DIR)/rlib/%.o: $(RLIB_LIB)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(ALL_OBJ:.o=.d)

# Pulizia
clean:
	rm -rf $(BUILD_DIR) main debug