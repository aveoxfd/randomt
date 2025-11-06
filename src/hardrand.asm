[bits 64]

global __get_hardrand_rdrand
global __get_hardrand_rdseed

__get_hardrand_rdrand:
push rbp
mov rbp, rsp

mov rax, 1
cpuid
cmp rcx, (1 << 30)
je .not_support

rdrand rax
jmp .exit

.not_support:
mov rax, -1
.exit:
mov rsp, rbp
pop rbp
ret

__get_hardrand_rdseed:
push rbp
mov rbp, rsp

mov rax, 1
cpuid
cmp rcx, (1 << 30)
je .not_support

rdseed rax
jmp .exit

.not_support:
mov rax, -1
.exit:
mov rsp, rbp
pop rbp
ret