.data
buf: .asciz "HMMMMMMMMMMMMMMMMMMMMMMMMM"
size: .long 0
.text
.global main
main:
mov $10, %ecx
mov $2356, %eax
l1:
xor %edx, %edx
cmp $0, %eax
jz l1e
div %ecx
incl size
add $0x30, %edx
push %edx
jmp l1
l1e:
mov size, %ecx
mov $buf, %edx
l2:
cmp $0, %ecx
jz l2e
pop %eax
movb %al, (%edx, 1)
#//;lea buf, %ebx 
inc %edx
dec %ecx
jmp l2
l2e:





exit:
    mov $0x1, %eax
    xor %ebx, %ebx
    int $0x80
