.model small
.486 

stack segment para stack 'stack'
	DB  100h dup(?)
stack ends

const segment
        _WORD_S equ 18
const ends
data segment para public 'data'
	arrSize equ 16
	arr db 36 dup(0h)
        delimiter db '|'
	arrBuf db 36 dup(0h)
	index  db 0
data ends

;write word by index
WRITE18BWORD macro array, index; RESULT STORED IN EBX
local lshiftIsZero, shift
        pushad
	
	mov bp, sp
	mov al, index
	mov dl, _WORD_S
	mul dl
	push ax ; from. AH = offset in byte, AL = offset in array
	xor ax, ax
	mov al, index 
	inc ax
	mov dl, _WORD_S
	mul dl
	push ax ;to AH = offset in byte, 
	mov ax, [bp-2];from
	mov dl, 8
	div dl
	push ax; first byte (offset/index)
	mov ax, [bp-4];to	
	mov dl, 8
	div dl
	dec al
	cmp ah, 0h
        je lshiftIsZero ; if no need to shr
        
	inc al
	not ah
	inc ah
	add ah, 8
lshiftIsZero:
	push ax ; last byte (offset/index)
	mov edx, ebx; WORDTOWRITE -> EDX
	xor ebx, ebx
	mov bx, [bp-8]
	xor bh, bh
	mov di, bx
	xor ax, ax
	mov ah, array[di]
	mov bx, [bp-8];
	mov cl, bh
	shr ax, cl
	mov ah, dl
	shl ax, cl
	mov array[di], ah ;0 byte
	mov al, dl
	mov ah, dh
	mov bx, [bp-8];
	mov cl, bh
	shl ax, cl
	dec di
	mov array[di], ah; 1 byte
	dec di
	mov bx, [bp-6];
	mov cx, bx
	xor ch, ch
	cmp di, cx
        je shift ; ERROR GDE TO TUT!
        
	mov eax, edx
	mov cl, 8 
	shr eax, cl ; ok, stiraem 8 bit sprava
	mov al, dh ;
	mov bx, [bp-8];
	mov cl, bh 
	shl ax, cl
	mov array[di], ah; 2 byte
	dec di
shift:	
        ; zapis poslednego byte.
        ; tut perezapis' idet
        mov ch, array[di]
        push cx
	mov cl, 2
	shr edx, cl
	mov ah, array[di]
	mov bx, [bp-6]
	mov cl, bh
	shl eax, cl
	mov ah, dh
	shr eax, cl
        pop cx
        ;add ah, ch       ; nujno prev + ah
	mov array[di], ah; 2 or 3 byte

	pop di;
	pop di;
	pop di; KOSTILI!
	pop di;
	
	popad
endm

;Read word by index
READ18BWORD macro array, index
local lshiftIsZero, shift, ex
	push bp
	push cx
	push ax
	push di
	push bx
	
	mov bp, sp
	mov al, index
	mov dl, _WORD_S
	mul dl
	push ax ; from. AH - offset in byte, AL - in array
	xor ax, ax
	mov al, index
	inc ax
	mov dl, _WORD_S
	mul dl
	push ax ; to . AH - offset in byte, AL - in array
	mov ax, [bp-2];from
	mov dl, 8
	div dl
	push ax 
	mov ax, [bp-4];to	
	mov dl, 8
	div dl
	dec al
	cmp ah, 0h
        je lshiftIsZero 
        
	inc al
	not ah
	inc ah
	add ah, 8
lshiftIsZero:
	push ax ; last byte offset/index
        ; EXCHANGE: EAX na EDX
	mov dx, [bp-6]
	xor dh, dh
	mov di, dx ; di now stores first byte OF/IND
	xor dx, dx
	mov dh, array[di] ; first byte -> ah
	inc di
	mov dl, array[di] ; second byte -> al
	mov ax, [bp-6] ; 
	mov cl, ah
	shl dx, cl
	shr dx, cl
	shl edx, 8
	inc di
	mov dl, array[di] ; third byte -> al
        
	mov ax, [bp-8]
	xor ah, ah
	mov cx, ax
	cmp di, cx

	je shift
	shl edx, 8
	inc di 
	mov dl, array[di]
shift:
        xor cx, cx
	mov ax, [bp-8]
	mov cl, ah
	shr edx, cl   
ex:
	pop bx;
	pop bx;
	pop bx
	pop bx;
	
	pop bx
        pop di
        pop ax
	pop cx
	pop bp
endm


code segment para public 'code'
	assume CS:code,DS:data, ss:stack
fillWithData proc
        pusha
        xor cx, cx
        mov ebx, 100000000000000000b
iteration:
        cmp cl, arrSize
        je fwd_exit
        WRITE18BWORD arr, cl
        shr ebx, 1
        inc cl
        jmp iteration
fwd_exit:
        popa
        ret
fillWithData endp

sortData proc
        pusha
        xor ax, ax ; bh - i, bl - j
        mov cl, arrSize
        dec cl
iteration:
        mov al, index
        cmp cl, index
        je sort_exit
        
        xor EDX, EDX
        xor ESI, ESI
        READ18BWORD arr, index
        mov ESI, EDX
        inc index
        xor EDX, EDX
        READ18BWORD arr, index ; a - EAX, b - EDX
        dec index
        
        cmp ESI, EDX
        jg swap_elements
        
        inc index
        jmp iteration
swap_elements:
        xor EBX, EBX
        mov EBX, EDX
        WRITE18BWORD arr, index
        xor EBX, EBX
        mov EBX, ESI
        inc index
        WRITE18BWORD arr, index
        mov index, 0
        jmp iteration
sort_exit:        
        popa
        ret
sortData endp	

start: 	
        mov ax, data
	mov ds, ax

        call fillWithData
        call sortData
        
	mov ax, 4c00h
	int 21h                 
code ends				  
end start			  
	
		