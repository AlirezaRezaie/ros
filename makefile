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
KERNEL_C_FILES :=  $(wildcard $(KERNEL)/*.c)          \
				   $(wildcard $(KERNEL)/utils/*.c)    \
				   $(wildcard $(KERNEL)/keyboard/*.c) \
				   $(wildcard $(KERNEL)/std/*.c)

# List of object files for each C file in the kernel directory
KERNEL_OBJ_FILES := $(patsubst $(KERNEL)/%.c, $(BIN_FOLDER)/%.o, $(KERNEL_C_FILES)) 

# Rule to create the final OS image
all: $(BIN_FOLDER)/boot.bin $(BIN_FOLDER)/full_kernel.bin $(BIN_FOLDER)/zeroes.bin
	cat $? > bin/os.img

# Rule to assemble bootloader code
$(BIN_FOLDER)/boot.bin: $(BOOTLOADER)/boot.asm
	nasm $< -f bin -o $@ -i"include"

# Rule to assemble kernel entry code
$(BIN_FOLDER)/kernel_entry.o: $(BOOTLOADER)/kernel_entry.asm
	nasm $< -f elf -o $@

# Rule to assemble zeroes code
$(BIN_FOLDER)/zeroes.bin: $(BOOTLOADER)/zeroes.asm
	nasm $< -f bin -o $@


# Rule to compile each C file in the kernel directory to object files
$(BIN_FOLDER)/%.o: $(KERNEL)/%.c
	mkdir -p bin/utils/
	mkdir -p bin/std/
	$(CROSSCOMPILER_PATH)/i686-elf-gcc $(GCC_COMPILE_OPT) $< -o $@

$(BIN_FOLDER)/%.o: $(KERNEL)/utils/%.c
	$(CROSSCOMPILER_PATH)/i686-elf-gcc $(GCC_COMPILE_OPT) $< -o $@


# Rule to link kernel entry object file with all kernel object files
$(BIN_FOLDER)/full_kernel.bin: $(BIN_FOLDER)/kernel_entry.o $(KERNEL_OBJ_FILES)
	$(CROSSCOMPILER_PATH)/i686-elf-ld -o $@ -T linker.d $^ --oformat binary


# Rule to create the bootable image for VirtualBox
create_virtualbox_image: all
	dd if=/dev/zero of=$(BIN_FOLDER)/osflop.img bs=512 count=2880  # Create a 1.44 MB blank disk image
	dd if=$(BIN_FOLDER)/boot.bin of=$(BIN_FOLDER)/osflop.img conv=notrunc  # Write the bootloader to the disk image
	dd if=$(BIN_FOLDER)/full_kernel.bin of=$(BIN_FOLDER)/osflop.img seek=1 conv=notrunc  # Write the kernel after the bootloader

# Rule to clean generated files
clean:
	rm -rf $(BIN_FOLDER)/*

# Rule to run the OS image in QEMU
run:
	qemu-system-x86_64 -drive format=raw,file=$(BIN_FOLDER)/os.img,index=0,if=floppy,  -m 128M
run-vbox:
	VirtualBoxVM --startvm "ros"