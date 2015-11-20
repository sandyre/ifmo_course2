stack segment para stack 'stack'
    DB 100h dup(?)
stack ends

data segment para public 'data'
    output_str db 11 dup('$')
    errormsg db 'function returned error code'
data ends

code segment para public 'code'
    assume cs:code, ds:data
extrn wordToChar:near

main:
    mov ax, data
    mov ds, ax
    
    mov ax, -500
    push ax
    lea ax, output_str
    push ax
    
    call wordToChar
    
    cmp ax, 0
    je if_returned_true
    jne if_returned_false
if_returned_true:
    lea dx, output_str
    jmp exit
if_returned_false:
    lea dx, errormsg
    jmp exit

exit:
    mov ah, 09h
    int 21h
    
    mov ax, 4C00h
    int 21h
code ends
end main