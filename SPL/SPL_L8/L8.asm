format PE GUI 4.0
entry start
include 'C:\fasm\include\WIN32A.inc'

section '.code' code readable executable
;some const defines
    AMOUNT_OF_NUMBERS	    equ 8
    WINDOW_WIDTH	equ 640
    WINDOW_HEIGHT	equ 480

;ASCII codes for common symbols
    ASCII_0	    equ 48
    ASCII_SPACE 	equ 32
    ASCII_NEWLINE	equ 10
    arrSize	    equ 16
    _WORD_S equ 18

macro WRITECUSTOMWORD pos, array, _WORD_S  ;word stored in EBX
{
local lshiftIsZero, shift
    push ax
    push cx
    push dx
    push di

    mov [fro], 0
    mov [too], 0
    mov [buffer1], 0
    mov [buffer2], 0
    xor edi,edi

    mov al, pos
    mov dl, _WORD_S
    mul dl
    mov [fro], ax
    xor ax, ax
    mov al, pos
    inc ax
    mov dl, _WORD_S
    mul dl
    mov [too], ax
    mov ax, [fro]
    mov dl, 8
    div dl
    mov [buffer1],ax
    mov ax, [too];;;;
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
    mov [buffer2],ax
    mov edx, ebx
    xor ebx, ebx
    mov bx, [buffer2]
    xor bh, bh
    mov di, bx
    xor ax, ax
    mov ah, [array+edi]
    mov bx, [buffer2]
    mov cl, bh
    shr ax, cl
    mov ah, dl
    shl ax, cl
    mov [array+edi], ah
    mov al, dl
    mov ah, dh
    mov bx, [buffer2]
    mov cl, bh
    shl ax, cl
    dec di
    mov [array+edi], ah
    dec di
    mov bx, [buffer1]
    mov cx, bx
    xor ch, ch
    cmp di, cx
    je shift
    mov eax, edx
    mov cl, 8
    shr eax, cl
    mov al, dh
    mov bx, [buffer2]
    mov cl, bh
    shl ax, cl
    mov [array+edi], ah
    dec di

shift:
    mov ch, [array+edi]
    push cx
    mov cl, 2
    shr edx, cl
    mov ah, [array+edi]
    mov bx, [buffer1]
    mov cl, bh
    shl eax, cl
    mov ah, dh
    shr eax, cl
    pop cx
    mov [array+edi], ah ; 2 bytes + 2 bits

    pop di
    pop dx
    pop cx
    pop ax
}

macro READCUSTOMWORD pos, array, _WORD_S
{
local lshiftIsZero, shift, ex
    push cx
    push dx
    push di
    push bx

    mov [fro], 0
    mov [too], 0
    mov [buffer1], 0
    mov [buffer2], 0
    xor edi,edi

    mov al, pos
    mov dl, _WORD_S
    mul dl
    mov [fro], ax
    xor ax, ax
    mov al, pos
    inc ax
    mov dl, _WORD_S
    mul dl
    mov [too], ax
    mov ax, [fro]
    mov dl, 8
    div dl
    mov [buffer1], ax
    mov ax, [too]
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
    mov [buffer2], ax
    xor eax,eax
    mov ax, [buffer1]
    xor ah, ah
    mov di, ax
    xor ax, ax
    mov ah, [array+edi]
    inc di
    mov al, [array+edi]
    mov dx, [buffer1]
    mov cl, dh
    shl ax, cl
    shr ax, cl
    shl eax, 8
    inc di
    mov al, [array+edi]
    mov dx, [buffer2]
    xor dh, dh;
    mov cx, dx;
    cmp di, cx
    je shift

    shl eax, 8
    inc di
    mov al, [array+edi]
shift:
    xor cx, cx
    mov dx, [buffer2]
    mov cl, dh
    shr eax, cl

    jmp ex
    mov al, [array+edi]
ex:
    pop bx
    pop di
    pop dx
    pop cx
}

convertWord:
    pusha
    mov [bufSize], 0
    call getSign
    xor  esi, esi
    xor  edx, edx
    mov  edi, buff ;lea

    cmp  bx, 1
    jne  beginConvert
    mov  dl, '-'
    mov  [edi], dl
    inc  edi
    inc  [bufSize]

beginConvert:
    mov  ebx, 10
convert:
    xor edx, edx
    div ebx
    add dl, 30h
    push dx
    add si,1
    cmp eax, 0
jnz convert
    mov ax, si
tracenumber:
    pop dx
    mov [edi], dl
    inc edi
    dec si
    inc [bufSize]
    cmp si,0
    jnz tracenumber

    mov dl, '$'
    mov [edi], dl
    popa
    ret

getSign:
    mov bx, 0
    bt eax, 17
    jnc fromSign
    or eax, 0fffe0000h ; mask to check sign.
    not eax
    inc eax
    mov bx, 1

fromSign:
    ret

readFromFArr:
	READCUSTOMWORD [pointer], initial_array, _WORD_S
ret

readFromSArr:
	READCUSTOMWORD [pointer], secondary_array, _WORD_S
ret

start:
    mov cx, 0

    ; put some values! its powers on 2 going down.
fillWithData:
    pusha
    mov eax, 00001h
    xor cx, cx
fill_iteration:
    cmp cl, arrSize
    je fill_end

    mov ebx, eax
    WRITECUSTOMWORD cl, initial_array, _WORD_S
    ;shr eax, 1
    inc eax
    inc cl
    jmp fill_iteration
fill_end:
    popa

copy:
    push cx
    mov [pointer], cl
    READCUSTOMWORD [pointer], initial_array, _WORD_S
    pop cx
    mov ebx, eax
    push cx
    mov [pointer], cl
    WRITECUSTOMWORD cl, secondary_array, _WORD_S
    pop cx
    inc cx
    cmp cx, 15
jle copy

sort_array:
    xor ax, ax
    mov [pointer], 0
    mov cl, arrSize
    dec cl
sort_iteration:
    mov al, [pointer]
    cmp cl, [pointer]
    je sort_exit

    xor edx, edx
    xor esi, esi
    READCUSTOMWORD [pointer], secondary_array, _WORD_S
    mov esi, eax
    inc [pointer]
    READCUSTOMWORD [pointer], secondary_array, _WORD_S
    mov edx, eax
    dec [pointer]

    cmp esi, edx
    jg swap_elements

    inc [pointer]
    jmp sort_iteration
swap_elements:
    xor ebx, ebx
    mov ebx, edx
    WRITECUSTOMWORD [pointer], secondary_array, _WORD_S
    xor ebx, ebx
    mov ebx, esi
    inc [pointer]
    WRITECUSTOMWORD [pointer], secondary_array, _WORD_S
    mov [pointer], 0
    jmp sort_iteration
sort_exit:
    mov [pointer], 0

    xor ebx, ebx
    xor edx, edx
    mov cx, 0
    mov bx, 0
    mov dx, 0

; WINAPI PART

invoke GetModuleHandle,        0
    mov [wcex.hInstance],	       eax
    mov eax,			      sizeof.WNDCLASSEX
    mov [wcex.cbSize],		       eax
    mov [wcex.lpfnWndProc],	       WndProc
    mov [wcex.style],		       CS_HREDRAW+CS_VREDRAW

    invoke LoadIcon,[wcex.hInstance],  IDI_APPLICATION

    mov [wcex.hIcon],		       eax
    mov [wcex.hIconSm], 	       eax

    invoke LoadCursor,	   NULL,       IDC_ARROW

    mov [wcex.hCursor], 	       eax
    mov [wcex.hbrBackground],	       COLOR_WINDOW+1
    mov dword [wcex.lpszClassName],    szClass
    mov [wcex.cbClsExtra],	       0
    mov [wcex.cbWndExtra],	       0
    mov dword [wcex.lpszMenuName],     NULL
    invoke RegisterClassEx,	       wcex

    test eax,	   eax
    jz reg_error

    invoke CreateWindowEx,	   0,\
	szClass,szTitle,	   WS_OVERLAPPEDWINDOW,\
	CW_USEDEFAULT,	       CW_USEDEFAULT,\
	WINDOW_WIDTH,		   WINDOW_HEIGHT,\
	NULL,		       NULL,\
	[wcex.hInstance],	   NULL
    test eax,	   eax
    jz cr_error

    mov [h_wnd],   eax
    invoke ShowWindow,	   [h_wnd],	SW_SHOWNORMAL
    invoke UpdateWindow,   [h_wnd]

 msg_loop:
    invoke GetMessage,msg,NULL,0,0
    cmp eax,1
    jb exit
    jne msg_loop
    invoke TranslateMessage,msg
    invoke DispatchMessage,msg
    jmp msg_loop

    reg_error:
    invoke MessageBox,NULL,szRegError,szTitle,MB_ICONERROR+MB_OK
    jmp exit

    cr_error:

    invoke MessageBox,NULL,szCreateError,szTitle,MB_ICONERROR+MB_OK

exit:
    invoke  ExitProcess, 0


proc WndProc uses ebx esi edi,hwnd,wmsg,wparam,lparam
    cmp    [wmsg],   WM_PAINT
    je	   .PAINT

    cmp    [wmsg],   WM_DESTROY
    je .DESTROY

.DEFAULT:
    invoke DefWindowProc,[hwnd],[wmsg],[wparam],[lparam]
    jmp .DONE

.PAINT:
    invoke BeginPaint,[hwnd],ps
    mov [hdc],eax

    mov ebx, 75
    mov si, 0
    mov ecx, arrSize+1
.next:
    push ecx

    ; draw first column
    mov cx, si
    mov [pointer], cl
    call readFromFArr
    call convertWord
    xor edx, edx
    mov dl, [bufSize]

    invoke TextOut, [hdc], 175, ebx, buff, edx

    ; draw second column
    mov dx, 1
    mov cx, si
    mov [pointer], cl
    call readFromSArr
    call convertWord
    xor edx, edx
    mov dl, [bufSize]

    invoke TextOut, [hdc], 375, ebx, buff,  edx
    pop ecx
    add ebx, 15
    inc si
    dec di

    loop .next

    invoke EndPaint,[hwnd],ps
    jmp .DONE

.DESTROY:
    invoke PostQuitMessage,0
    xor eax,eax

.DONE:
    ret
endp

section '.idata' import data readable writeable
    library kernel,	    'KERNEL32.DLL',\
	user,		    'USER32.DLL',\
	gdi,		    'GDI32.DLL'

    import kernel,\
	GetModuleHandle,    'GetModuleHandleA',\
	ExitProcess,	    'ExitProcess'

    import user,\
	RegisterClassEx,    'RegisterClassExA',\
	CreateWindowEx,     'CreateWindowExA',\
	ShowWindow,	    'ShowWindow',\
	UpdateWindow,	    'UpdateWindow',\
	GetMessage,	    'GetMessageA',\
	TranslateMessage,   'TranslateMessage',\
	DispatchMessage,    'DispatchMessageA',\
	MessageBox,	    'MessageBoxA',\
	DefWindowProc,	    'DefWindowProcA',\
	BeginPaint,	    'BeginPaint',\
	EndPaint,	    'EndPaint',\
	PostQuitMessage,    'PostQuitMessage',\
	LoadIcon,	    'LoadIconA',\
	LoadCursor,	    'LoadCursorA'

    import gdi,\
	TextOut,	    'TextOutA'




section '.data' readable writeable
    arrSize equ 16
    initial_array db 36 dup(0h)
    secondary_array db 36 dup(0h)
    buff    db 10 dup(0)
    bufSize db 0
    columnWidth     equ 28
    fro dw 0
    too dw 0
    buffer1 dw 0
    buffer2 dw 0
    pointer db 0

    szTitle	TCHAR "Lab8. Var 2.", 0
    szClass TCHAR "Lab8. Win 32 api",  0
    szRegError	    TCHAR "Call to RegisterClassEx failed!",	0
    szCreateError   TCHAR "Call to CreateWindowEx failed!",	0
    wcex	WNDCLASSEX
    ps		PAINTSTRUCT
    msg 	MSG
    h_wnd	dd			0
    hdc 	dd			0
