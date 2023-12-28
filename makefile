# Directories
KERNEL=src/arch/x86
BOOTLOADER=src/boot
CROSSCOMPILER_PATH=~/cross/bin
BIN_FOLDER=bin

# Compiler Options
GCC_COMPILE_OPT =		\
	-ffreestanding   	\
	-m32				\
	-g					\
	-c

# List of C source files in the kernel directory
KERNEL_C_FILES := $(wildcard $(KERNEL)/*.c)

# List of object files for each C file in the kernel directory
KERNEL_OBJ_FILES := $(patsubst $(KERNEL)/%.c, $(BIN_FOLDER)/%.o, $(KERNEL_C_FILES))

# Rule to create the final OS image
all: $(BIN_FOLDER)/boot.bin $(BIN_FOLDER)/full_kernel.bin $(BIN_FOLDER)/zeroes.bin
	cat $? > bin/os.img

# Rule to assemble bootloader code
$(BIN_FOLDER)/boot.bin: $(BOOTLOADER)/boot.asm
	nasm $< -f bin -o $@ -i"include"

# Rule to link kernel entry object file with all kernel object files
$(BIN_FOLDER)/full_kernel.bin: $(BIN_FOLDER)/kernel_entry.o $(KERNEL_OBJ_FILES)
	$(CROSSCOMPILER_PATH)/i686-elf-ld -o $@ -T linker.d $^ --oformat binary

# Rule to assemble kernel entry code
$(BIN_FOLDER)/kernel_entry.o: $(BOOTLOADER)/kernel_entry.asm
	nasm $< -f elf -o $@

# Rule to compile each C file in the kernel directory to object files
$(BIN_FOLDER)/%.o: $(KERNEL)/%.c
	$(CROSSCOMPILER_PATH)/i686-elf-gcc $(GCC_COMPILE_OPT) $< -o $@

# Rule to assemble zeroes code
$(BIN_FOLDER)/zeroes.bin: $(BOOTLOADER)/zeroes.asm
	nasm $< -f bin -o $@

# Rule to clean generated files
clean:
	rm -rf $(BIN_FOLDER)/*

# Rule to run the OS image in QEMU
run:
	qemu-system-x86_64 -drive format=raw,file=$(BIN_FOLDER)/os.img,index=0,if=floppy,  -m 128M
