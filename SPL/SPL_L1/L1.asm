stack segment para stack 'stack'
        db 100h dup(?)
stack ends

data segment para public 'data'
        input_array DD -1, -2, -3, -4, -5, 5, 0, 6, -14, 2, 13, -15, 32, 5
        output_array DD 14 dup(?)
        input_array_size EQU 0038h
        output_array_size DB 0h
data ends

code segment para public 'code'
        assume cs:code, ds:data, ss:stack
start:
        mov AX, data
        mov ds, AX

        xor BX, BX

        mov AX, offset input_array ; const address of last element
        add AX, input_array_size
        mov DI, offset input_array ; DI - address of first element
        mov CX, 0 ; number of negative elements
push_negative_elements:
        mov SI, [DI] ; SI - value of elements
        cmp SI, 0
        jl negative ; push to stack

        add DI, 4
        cmp DI, AX
        je start_push_positive_elements ; go forward
        jmp push_negative_elements ; go back

negative:
        push SI
        inc CX
        jmp move_forward_1
move_forward_1:
        add DI, 4
        cmp DI, AX
        jne push_negative_elements ; go back
        jmp start_push_positive_elements ; go forward

start_push_positive_elements:
        mov DI, offset input_array
        xor SI, SI
push_positive_elements:
        mov SI, [DI]
        cmp SI, 0
        jge positive

        add DI, 4
        cmp DI, AX
        je start_pop_elements
        jmp push_positive_elements
positive:
        push SI
        jmp move_forward_2
move_forward_2:
        add DI, 4
        cmp DI, AX
        jne push_positive_elements
        jmp start_pop_elements

start_pop_elements:
        mov BX, input_array_size
        mov DI, AX
        sub DI, 4
pop_elements:
        sub BX, 4
        cmp BX, 0
        jge pop_element

        mov DI, offset input_array
        rol CX, 1
        rol CX, 1
        sub CX, 4
        add CX, DI
        jmp sort_negative
pop_element:
        pop SI
        mov [DI], SI
        sub DI, 4
        jmp pop_elements

sort_negative:
        cmp DI, CX
        je get_av_arithm

        mov SI, [DI]
        mov BX, [DI+4]
        cmp SI, BX
        jg  swap_elements
        add DI, 4
        jmp sort_negative
swap_elements:
        mov [DI], BX
        mov [DI+4], SI
        mov DI, offset input_array
        jmp sort_negative
get_av_arithm:
        mov DI, AX
        sub DI, 4
        mov CX, [DI] ; CX = last element
        mov DI, offset input_array
        mov SI, [DI] ; SI = first element
        add DI, 4
get_max_element:
        cmp SI, [DI]
        jl  set_new_max
        add DI, 4
        cmp DI, AX
        jne get_max_element
        jmp prepare_to_get_result
set_new_max:
        mov SI, [DI]
        add DI, 4
        cmp DI, AX
        jne get_max_element
        jmp prepare_to_get_result
prepare_to_get_result:
        mov DI, offset input_array
        add SI, CX ; SI = average arithmetical
        rcr SI, 1
        mov BP, 0 ; BP - first element of result array
        jmp get_result
get_result:
        cmp [DI], SI
        jg add_element_to_result
        jmp move_forward_3
add_element_to_result:
        mov DX, [DI]
        cwd
        mov output_array[BP], DX
        add BP, 4
        inc output_array_size
        jmp move_forward_3
move_forward_3:
        add DI, 4
        cmp DI, AX
        je result_end
        jmp get_result
result_end:
        mov AX,4C00h
        int 21h
code ends
end start