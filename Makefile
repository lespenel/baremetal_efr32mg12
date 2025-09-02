BIN_DIR := bin
BUILD_DIR := build
SRC_DIR := src
INC := include
LINKER_DIR := linker

# outfiles
NAME := $(BIN_DIR)/firmware.s37
ELF := $(BUILD_DIR)/firmware.elf
MAP := $(BUILD_DIR)/firmware.map

# tools
CC := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy

# architecture opt
MATCH := cortex-m4
MCUFLAGS := -mcpu=$(MATCH) -mthumb

CFLAGS := -c $(MCUFLAGS) -std=c99 -g -O0 -Wall -Wextra -Werror \
		  -I $(INC)

LDFLAGS := -T $(LINKER_DIR)/linker.ld -nostdlib -Wl,-Map=$(MAP)

# src files def
include	src.mk 

DEP := $(patsubst %.c, $(BUILD_DIR)/%.d, $(SRC))
OBJ := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC))

.PHONY: all
all: $(NAME)

.PHONY: elf
elf: $(ELF)

# ELF -> SREC
$(NAME): $(ELF)
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O srec $< $@

# link
$(ELF): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

-include $(DEP)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MD -MP $< -o $@

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	$(RM) -r $(NAME) $(BIN_DIR)

.PHONY: re
re: fclean all
