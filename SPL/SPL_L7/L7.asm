extern  printf
extern  cosh
extern  puts
extern  scanf

section .data
ish db  "Enter accuracy: ",0
inx1 db "Enter x0: ", 0
inx2 db "Enter x_end : ", 0
indx db "Enter step x: ", 0
ishpat  db  "%lf"
err db  "Wrong accuracy format (e.g. 0.001) and e > 0",0
errx db "Wrong x format (e.g. 0.01, 1.05)",0
header  db  "| x          | Calculated | C-function    | n  ",0
fmt db  "| %10.6f | %10.6f | %10.6f    | %.4d  ", 10, 0
dbg db  "%f",10,0

x   dq  1.0
xmax    dq  50.0
xdelta  dq  0.001
prev_term    dq  0.0
sum dq  0.0
one dq  1.0
zero    dq  0.0
res dq  0.0
n   dq  1
factorial dq 1
buf dq  0
e   dq  0

section .text
global main
main:
    push    rbp
    mov rbp, rsp

    mov rdi, inx1
    mov rax, 0
    call    printf

    mov rdi, ishpat
    mov rsi, qword x
    mov rax, 0
    call    scanf

    mov rax, qword [x]

    mov rdi, inx2
    mov rax, 0
    call    printf

    mov rdi, ishpat
    mov rsi, qword xmax
    mov rax, 0
    call    scanf

    mov rax, qword [xmax]


    mov rdi, indx
    mov rax, 0
    call    printf

    mov rdi, ishpat
    mov rsi, qword xdelta
    mov rax, 0
    call    scanf

    mov rax, qword [xdelta]

    mov rdi, ish
    mov rax, 0
    call    printf

    mov rdi, ishpat
    mov rsi, qword e
    mov rax, 0
    call    scanf

    mov rax, qword [e]
    cmp rax, 0
    je  error

    fld qword [e]
    fabs
    fstp    qword [e]

    mov rdi, header
    mov rax, 0
    call    puts

row:
    movsd   xmm0, [x]
    mov eax, 1
    call    cosh
    movq    rax, xmm0
    mov qword [res], rax  ; cosh(x) -> [res]

    mov rax, 1
    mov qword [n], rax    ; n = 2
    mov [factorial], rax

    fld qword [one]   ; first term = x, sum = 1
    fld qword [one]   ;
cloop:
    ; st1: sum
    ; st0: prev_term

    fld qword [x]
    fld qword [x]    ; умножаем на нужный знак X
    fmulp            ; умножаем prev_term на (-1)^n*X
    fmulp
    fst qword [prev_term]
factor:
    xor rdx, rdx
    xor rax, rax
    mov rax, qword [factorial]
    mov rdx, qword [n]
    mul rdx
    mov rdx, qword [n]
    add rdx, 1
    mul rdx
    mov qword [factorial], rax

    fild  qword [factorial]
    fdivp ; verh / factorial
    faddp ; add term to sum
calc_end:
    fld qword [prev_term]
    fld qword [res]

    ; st2: sum
    ; st1: prev_term
    ; st0: res
difference:
    fsub    st2     ; st0 = res-sum
    fabs            ; st0 = |res-sum|

    fld qword [e]

    ; st3: sum
    ; st2: prev_term
    ; st1: |res-sum|
    ; st0: e
comparison:
    fcomi   st1     ; cmp e, |res-sum|
    jbe cont        ; e <= |res-sum| ; |res-sum| >= e
    jmp stop
cont:
    fcompp
    inc qword [n]
    inc qword [n]
    jmp cloop
stop:
    fcompp
    fstp    qword [sum] ; sum = prev_term
    fstp    qword [sum] ; sum = sum

    movsd   xmm2, xmm0
    movsd   xmm0, [x]
    movsd   xmm1, [sum]
    mov rdi, fmt
    mov rdx, qword [n]
    shr rdx, 1
    add rdx, 2
    mov rsi, rdx
    mov rax, 3
    call    printf

    fld qword [xmax]
    fld qword [x]
    fadd    qword [xdelta]
    fst qword [x]
    fcomi   st1
    jbe next
    jmp     exit
next:
    fcompp
    jmp row
error:
    mov rdi, err
    mov rax, 0
    call    puts
    jmp exit
exit:
    mov ebx, 0
    mov rax, 1
    int 0x80
ret
