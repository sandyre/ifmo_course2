stack segment para stack 'stack'
    DB 100h dup(?)
stack ends

data segment para public 'data'
    wordrepresentation dw 0
    writeoutput db 30 dup('W')
    writeoutput_size dw 0
    readedstring db 30 dup('R')
    readedstringsize dw 10
    outputfilepath db 'C:\output.txt', 0
    filehandle dw ?
    successmsg db 'success$'
    errormsg db 'function returned error code$'
data ends

code segment para public 'code'
    assume cs:code, ds:data
extrn strToWord:near
extrn readStr:near
extrn wordToChar:near
extrn writeToFile:near
main:
    mov ax, data
    mov ds, ax

    ;read WORKS JUST FINE
    lea ax, readedstring
    push ax
    lea ax, readedstringsize
    push ax
    mov ax, 2
    push ax
    mov ax, 1
    push ax

    call readStr

    ; str to word DOESNT WORK
    lea ax, wordrepresentation
    push ax
    mov ax, readedstringsize
    push ax
    lea ax, readedstring
    push ax
    call strToWord
    cmp ax, 1
    je if_returned_false

    ; word to str
    lea ax, writeoutput_size
    push ax
    mov ax, wordrepresentation
    push ax
    lea ax, writeoutput
    push ax

    call wordToChar
    cmp ax, 1
    je if_returned_false

    ; write
    lea ax, outputfilepath
    push ax
    lea ax, filehandle
    push ax
    lea ax, writeoutput
    push ax
    mov ax, writeoutput_size
    push ax

    call writeToFile

    cmp ax, 0
    je if_returned_true
    jne if_returned_false
if_returned_true:
    lea dx, successmsg
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
