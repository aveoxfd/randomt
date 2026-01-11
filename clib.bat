gcc -c src/hdrand.c -Isrc/header -o obj/hdrand.o
nasm -f elf64 src/hardrand.asm -o obj/hdasm.o

ar rcs lib/libhdrand.a obj/hdrand.o obj/hdasm.o