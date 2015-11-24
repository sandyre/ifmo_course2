code segment para public 'code'
    assume cs:code

; +18 output_length
; +16 value
; +14 output_str
; +12 ret
; +10 si
; +8  bx
; +6  cx
; +4  dx
; +2  di
; +0  bp <- sp

; bool wordToChar(int value, char* output_str)
public wordToChar
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
    mov bx, [bp + 18]
    mov [bx], si
    pop bp
    pop di
    pop dx
    pop cx
    pop bx
    pop si

    ret
wordToChar endp

; filename +16
; handle +14
; data +12
; datasize +10
; ret +8
; bx +6
; cx +4
; dx +2
; bp +0

; bool writeToFile(char *filename, char *handle,  char *data, char datasize)
public writeToFile
writeToFile proc
    push bx
    push cx
    push dx
    push bp

    mov bp, sp

    mov ah, 3Dh ; openfile
    mov al, 1h
    mov dx, [bp + 16]
    int 21h
    jc ErrorWriteToFile

    mov bx, [bp + 14]
    mov [bx], ax

    mov ah, 40h
    mov bx, [bp + 14]
    mov bx, [bx]
    mov cx, [bp + 10]
    mov dx, [bp + 12]
    int 21h
    jc ErrorWriteToFile

    mov ah, 3Eh
    mov bx, [bp + 14]
    mov bx, [bx]
    int 21h
    jc ErrorWriteToFile
    jmp SuccessWriteToFile
ErrorWriteToFile:
    mov ax, 1
    jmp ExitWriteToFile
SuccessWriteToFile:
    mov ax, 0
    jmp ExitWriteToFile
ExitWriteToFile:
    pop bp
    pop dx
    pop cx
    pop bx
    ret
writeToFile endp

; bufferaddress +16
; stringsize +14
; line +12
; column +10
; ret +8
; bx +6
; cx +4
; dx +2
; bp +0
public readStr
readStr proc
    push bx
    push cx
    push dx
    push bp
    mov bp, sp

    ; cursor setting code;
    mov dh, [bp + 12] ; line
    mov dl, [bp + 10] ; column
    mov bh, 0
    mov ah, 2
    int 10h
    ; end of cursor setting code;

    xor dx, dx
    xor bx, bx
    xor cx, cx
    mov cx, 0

    mov bx, [bp + 16]
    ; reading string code ;
get_char:
    mov ah, 01h
    int 21h

    cmp al, 13
    je readStr_end

    mov ah, 0
    inc cx ; size counter++
    mov [bx], ax
    inc bx
    jmp get_char
    ; end of reading string code ;

    ; restore regiters
readStr_end:
    mov bx, [bp + 14]
    mov [bx], cx
    pop bp
    pop dx
    pop cx
    pop bx
    ret
readStr endp

; wordaddress +16
; stringsize +14
; stringaddress +12
; ret +10
; bx +8
; cx +6
; dx +4
; bp +2
; si +0
public strToWord
strToWord proc
	push bx
	push cx
	push dx
	push bp
        push si

	mov bp, sp

	mov cx, [bp + 14] ; size
	mov bx, [bp + 12] ; stringptr

	xor ax, ax
        mov dl, byte ptr[bx]
        cmp dl, '-'
        jne procloop
        mov si, 2
        inc bx
        dec cx
procloop:
	mov dx, 10
	mul dx
	cmp dx, 0
	jne incorrectStrToWord

	mov dl, byte ptr [bx]
	cmp dl, '0'
	jl incorrectStrToWord
	cmp dl, '9'
	jg incorrectStrToWord

	add al, dl
	jc incorrectStrToWord

	sub al, '0'

	inc bx
	loop procloop
	jmp correctStrToWord

incorrectStrToWord:
	mov ax, 1
	jmp exitStrToWord
correctStrToWord:
	; sending result
        cmp si, 2
        je  its_negative
	mov bx, [bp + 16]
	mov [bx], ax
	mov ax, 0
	jmp exitStrToWord
its_negative:
        neg ax
        mov bx, [bp + 16]
	mov [bx], ax
	mov ax, 0
	jmp exitStrToWord
exitStrToWord:
        pop si
	pop bp
	pop dx
	pop cx
	pop bx
	ret
strToWord endp
code ends
end
