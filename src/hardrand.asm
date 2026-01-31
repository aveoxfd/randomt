[bits 64]

section .text

global __get_hardrand_rdrand
global __get_hardrand_rdseed

__get_hardrand_rdrand:
push rbp
mov rbp, rsp

mov rax, 1
cpuid
cmp rcx, (1 << 30)
je .hardrand_rdrand_not_support

rdrand rax
jmp .hardrand_rdrand_exit

.hardrand_rdrand_not_support:
mov rax, -1

.hardrand_rdrand_exit:
mov rsp, rbp
pop rbp
ret

__get_hardrand_rdseed:
push rbp
mov rbp, rsp

mov rax, 1
cpuid
cmp rcx, (1 << 18)
je .get_hardrand_rdseed_not_support

rdseed rax
jmp .get_hardrand_rdseed_exit

.get_hardrand_rdseed_not_support:
mov rax, -1

.get_hardrand_rdseed_exit:
mov rsp, rbp
pop rbp
ret