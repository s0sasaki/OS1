.code32
.globl io_hlt
.globl copyseg

.text

io_hlt:
    hlt
    ret

copyseg:
    movl 4(%esp), %edx
    movl 8(%esp), %eax
;    movl $32, %ecx
;1:
    movl (%edx), %ebx 
    movl %ebx, (%eax)
;    dec %ecx
;    cmp $0, %ecx
;    je 1b
    ret
