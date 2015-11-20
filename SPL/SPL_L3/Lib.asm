code segment para public 'code'
    assume cs:code
    
; +16 value
; +14 output_str
; +12 ret
; +10 si
; +8  bx
; +6  cx
; +4  dx
; +2  di   
; +0  bp <- sp

public wordToChar ; bool wordToChar(int value, char* output_str)
wordToChar proc
prepare_for_execution:
    push si
    push bx
    push cx
    push dx
    push di
    push bp
    
    mov bp, sp ; bp now pointers on sp
    mov ax, [bp + 16] ; value
    test ax, ax
    jns is_positive
    mov bx, [bp + 14] ; output
    mov byte ptr [bx + si], '-'
    mov si, 1
    neg ax
is_positive:
    xor cx, cx
    mov bx, 10
divloop:
    xor dx, dx
    div bx
    push dx
    inc cx
    test ax, ax
    jnz divloop
    mov bx, [bp + 14]
    mov ax, 0
movloop:
    pop dx
    cmp si, 5
    jg  set_error_code
    add dl, 30h
    mov byte ptr [bx + si], dl
    inc si
    jmp continue
set_error_code: ; not exit, because we need to repair stack
    mov ax, 1
continue:
    loop movloop
reestablish_registers_and_exit:
    pop bp
    pop di
    pop dx
    pop cx
    pop bx
    pop si
    
    ret
wordToChar endp
code ends
end