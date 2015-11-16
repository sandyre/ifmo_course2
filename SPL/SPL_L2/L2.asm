stack segment para stack 'stack'
    DB 100h dup(?)
stack ends

data segment para public 'data'
    input_string DB 'XjSYgu7wPGvBrZqDeJRWFz,L9ZQHCnJcwc2CgXKWf5pxFpZwXthE,EQgwhAJv9LC'
    binary_string DW 0001000100010001b, 1111000011110000b, 1111000011110000b, 1111000011110000b
    binary_mask DB  '1111000011110000111100001111000011110000111100001111000011110000' 
    input_string_size EQU 64
    
    nul db '0'
    one db '1'
    low_bound db 'a'
    upper_bound db 'z'
    delimiter db ','
data ends

code segment para public 'code'
    assume cs:code, ds:data
println proc
    mov DL, 0Ah
    mov AH, 02h
    int 21h
    mov DL, 0Dh
    mov AH, 02h
    int 21h
    ret
println endp

printinputstring proc
    mov CX, input_string_size
    lea SI, input_string ; input_string addr.
printnextchar:
    lodsb ; [SI] -> AL, SI++
    mov DL, AL
    mov AH, 02h
    int 21h
    loop printnextchar ; CX--, if CX jmp printnextchar
    
    call println
    ret
printinputstring endp

printmask proc
    mov CX, input_string_size
    lea SI, binary_mask ; input_string addr.
printnextchar2:
    lodsb ; [SI] -> AL, SI++
    mov DL, AL
    mov AH, 02h
    int 21h
    loop printnextchar2 ; CX--, if CX jmp printnextchar
    
    call println
    ret
printmask endp


printfirstoutputstring proc
    mov CX, input_string_size
    lea SI, input_string ; input_string addr.
    mov DI, 0
    mov BX, binary_string[DI]
parsingloop1:
    lodsb ; [SI] -> AL, SI++
    rcl BX, 1
    jnc skip_element
    cmp AL, low_bound
    jl  skip_element
    cmp AL, upper_bound
    jle pass_element
pass_element:
    mov DL, AL
    mov AH, 02h
    int 21h
skip_element:
    cmp CX, 48
    je load_next_binary_string_part
    cmp CX, 32
    je load_next_binary_string_part
    cmp CX, 16
    je load_next_binary_string_part
    loop parsingloop1 ; CX--; if CX jmp parsingloop1
    
    call println
    ret
load_next_binary_string_part:
    add DI, 8
    mov BX, binary_string[DI]
    loop parsingloop1 ; CX--; if CX jmp parsingloop1
printfirstoutputstring endp

printsecondoutputstring proc
    std
    mov CX, input_string_size
    dec SI  ; SI now addresses last element of string
    clc     ; carry flag = 0. it saves if prev. symbol was delimiter
parsingloop2:
    lodsb   ; [SI] -> AL, SI--
    jnc isdelimiter
islowcaseletter:
    cmp AL, low_bound
    jl  isdelimiter ; AL < a -> check for del
    cmp AL, upper_bound
    jg  isdelimiter ; AL > z -> check for del
    jmp exit
isdelimiter:
    clc
    cmp AL, delimiter
    jne pass_element2
    stc
pass_element2:
    mov DL, AL
    mov AH, 02h
    int 21h
    loop parsingloop2
exit:
    call println
    ret
printsecondoutputstring endp

start:
    mov AX, data
    mov DS, AX
    
    call printinputstring
    call printmask
    call printfirstoutputstring
    call println
    call printinputstring
    call printsecondoutputstring
    
    mov AX, 4C00h
    int 21h
code ends
end start