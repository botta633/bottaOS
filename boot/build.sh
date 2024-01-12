nasm -f bin -o boot.bin boot.asm
nasm -f bin -o loader.bin loader.asm
nasm -f elf64 -o kernel.o kernel.asm
nasm -f elf64 -o trapa.o ../kern/includes/trap.asm
nasm -f elf64 -o liba.o ../kern/includes/lib.asm
x86_64-linux-gnu-gcc -ggdb -std=c99 -mcmodel=large -ffreestanding -fno-stack-protector -mno-red-zone -c main.c
x86_64-linux-gnu-gcc -ggdb -std=c99 -mcmodel=large -ffreestanding -fno-stack-protector -mno-red-zone -c ../kern/src/debug.c
x86_64-linux-gnu-gcc -ggdb -std=c99 -mcmodel=large -ffreestanding -fno-stack-protector -mno-red-zone -c ../kern/src/print.c
x86_64-linux-gnu-gcc -ggdb -std=c99 -mcmodel=large -ffreestanding -fno-stack-protector -mgeneral-regs-only -mno-red-zone -mgeneral-regs-only -c ../kern/src/trap.c
x86_64-linux-gnu-gcc -ggdb -std=c99 -mcmodel=large -ffreestanding -fno-stack-protector -mgeneral-regs-only -mno-red-zone -mgeneral-regs-only -c ../kern/src/exception.c
x86_64-linux-gnu-gcc -ggdb -std=c99 -mcmodel=large -ffreestanding -fno-stack-protector -mno-red-zone -c ../kern/utils/math.c
x86_64-linux-gnu-gcc -ggdb -std=c99 -mcmodel=large -ffreestanding -fno-stack-protector -mno-red-zone -c mem.c

ld -nostdlib -T link.lds -o kernel kernel.o  main.o trapa.o liba.o trap.o print.o debug.o mem.o exception.o  math.o
objcopy -O binary kernel kernel.bin
dd if=boot.bin of=boot.img bs=512 count=1 conv=notrunc
dd if=loader.bin of=boot.img bs=512 count=5 seek=1 conv=notrunc
dd if=kernel.bin of=boot.img bs=512 count=100 seek=6 conv=notrunc
