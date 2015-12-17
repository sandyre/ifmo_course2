; VARIANT 2.
; INTERRUPT - 09H - KEYBOARD
; <SHIFT>+<ALT>+<C> - PRINT HARDWARE INFO
; <SHIFT>+<ALT>+<D> - UNINSTALL

;CONSTANTS
_SCREEN_SZ equ 80 * 25
_SC_C equ 2eh
_SC_D equ 20h
_SHIFT_ALT_PRESSED equ 00000011b
;

code segment para public 'code'
    assume cs:code, ds:code, ss:code
    org 300h       
begin:
    jmp setup
    
    MSG_INSTALL      db 'Program loaded. To print hardware info - press <SHIFT>+<ALT>+<C>. ',
                        'To close program - press <SHIFT>+<ALT>+<D>$'
    MSG_OMIT_INSTALL db 'Program is already installed.', 13, 10, '$'
    MSG_UNINSTALL    db 'Program has been removed from memory.$'
    MSG_COPROCESSOR_YES db 13,10,'Coprocessor: yes', 13, 10, '$'
    MSG_COPROCESSOR_NO db 'Coprocessor: no', 13, 10, '$'
    MSG_FLOPPYDISK_YES db 'Floppy disks: yes', 13, 10, '$'
    MSG_FLOPPYDISK_NO db 'Floppy disks: no', 13, 10, '$'
    systemhandler    dd ? ; system handler address
    
;resident handler body
switch_handler proc
    push AX
    push CX
    push ds
    push es
    
print_hardware_info:
    mov ah, 02h
    int 16h
    and al, _SHIFT_ALT_PRESSED
    cmp al, 0h
    je invoke_system_interrupt
    in al, 60h
    cmp al, _SC_D
    je uninstall
    cmp al, _SC_C
    jne invoke_system_interrupt
    ; PRINT HARDWARE INFO!
    push AX
    push DX
    push ds
    
    mov AX, cs
    mov ds, AX
    
    int 11h ; check for coprocessor
    and AX, 10b
    cmp AX, 10b
    je coprocessor_exists
    jne coprocessor_not_exists
coprocessor_exists:
    lea DX, MSG_COPROCESSOR_YES
    jmp print_coprocessor_info
coprocessor_not_exists:
    lea DX, MSG_COPROCESSOR_NO
    jmp print_coprocessor_info
print_coprocessor_info:
    xor AX, AX
    mov AH, 09h
    int 21h
    
    int 11h ; check for floppy_disks
    and AX, 01b
    cmp AX, 01b
    je floppy_disk_exists
    jne floppy_disk_not_exists
floppy_disk_exists:
    lea DX, MSG_FLOPPYDISK_YES
    jmp print_floppy_disk_info
floppy_disk_not_exists:
    lea DX, MSG_FLOPPYDISK_NO
    jmp print_floppy_disk_info
print_floppy_disk_info:
    xor AX, AX
    mov AH, 09h
    int 21h
    
    ;exit
    pop ds
    pop DX
    pop AX
    jmp omit_system_interrupt

uninstall:
    mov AX, WORD PTR cs:systemhandler[2]
    mov ds, AX
    mov DX, WORD PTR cs:systemhandler
    mov AX, 2509h
    int 21h
    
    mov AX, 25FFh
    mov DX, 0000h
    int 21h
    
    push es
    
    mov es, cs:2Ch
    mov AH, 49h
    int 21h
    
    push cs
    pop es
    mov AH, 49h
    int 21h
    pop es
    
    push DS
    mov AX, cs
    mov ds, AX
    lea DX, cs:MSG_UNINSTALL
    mov AH, 9h
    int 21h
    pop ds
    
    jmp omit_system_interrupt
    
invoke_system_interrupt:
    pushf
    call cs:systemhandler
    jmp exit
omit_system_interrupt:
    in al, 61h
    mov ah, al
    or al, 80h
    out 61h, al
    xchg ah, al
    out 61h, al
    
    mov al, 20h
    out 20h, al
    
    jmp exit
    
exit:
    pop es
    pop ds
    pop CX
    pop AX
    
    iret
switch_handler endp
switch_handler_end:

setup:
    mov AX, 35FFh
    int 21h
    cmp BX, 0000h
    je install
    jne omit_install

install:
    mov AX, cs
    mov ds, AX
    lea DX, MSG_INSTALL
    mov AH, 09h
    int 21h
    
    mov AX, 3509h
    int 21h
    mov WORD PTR cs:systemhandler, BX
    mov WORD PTR cs:systemhandler+2, es
    
    mov AX, 2509h
    lea DX, switch_handler
    int 21h
    
    lea DX, switch_handler
    sub DX, offset switch_handler_end
    mov CL, 4
    shr DX, CL
    inc DX
    mov AX, 3100h
    int 21h
omit_install:
    mov AX, cs
    mov ds, AX
    lea DX, MSG_OMIT_INSTALL
    mov AH, 09h
    int 21h
    
    mov AX, 4C00h
    int 21h
localstack dw 100h dup(?)
code ends
end begin