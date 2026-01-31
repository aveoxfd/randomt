@echo off

gcc -c src/hdrand.c -Isrc/header -o obj/hdrand.o -DRND_STATIC
nasm -f win64 src/hardrand.asm -o obj/hdasm.o

ar rcs lib/libhdrand.a obj/hdrand.o obj/hdasm.o

ar t lib/libhdrand.a
nm lib/libhdrand.a