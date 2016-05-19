	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.section	__TEXT,__literal8,8byte_literals
	.align	3
LCPI0_0:
	.quad	4607182418800017408     ## double 1
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_Lab7_Asm
	.align	4, 0x90
_Lab7_Asm:                              ## @Lab7_Asm
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$160, %rsp
	leaq	_Lab7_Asm.enter_start_x(%rip), %rdi
	xorps	%xmm0, %xmm0
	movsd	%xmm0, -16(%rbp)
	movsd	%xmm0, -24(%rbp)
	movsd	%xmm0, -32(%rbp)
	movsd	%xmm0, -40(%rbp)
	movsd	%xmm0, -48(%rbp)
	movsd	%xmm0, -56(%rbp)
	movsd	%xmm0, -64(%rbp)
	movsd	%xmm0, -72(%rbp)
	movsd	%xmm0, -80(%rbp)
	movb	$0, %al
	callq	_printf
	leaq	_Lab7_Asm.scanf_format(%rip), %rdi
	leaq	-8(%rbp), %rsi
	movl	%eax, -84(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_scanf
	leaq	_Lab7_Asm.enter_end_x(%rip), %rdi
	movl	%eax, -88(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	_Lab7_Asm.scanf_format(%rip), %rdi
	leaq	-16(%rbp), %rsi
	movl	%eax, -92(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_scanf
	leaq	_Lab7_Asm.enter_delta_x(%rip), %rdi
	movl	%eax, -96(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	_Lab7_Asm.scanf_format(%rip), %rdi
	leaq	-24(%rbp), %rsi
	movl	%eax, -100(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_scanf
	leaq	_Lab7_Asm.enter_precision(%rip), %rdi
	movl	%eax, -104(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	_Lab7_Asm.scanf_format(%rip), %rdi
	leaq	-32(%rbp), %rsi
	movl	%eax, -108(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_scanf
	movsd	-8(%rbp), %xmm0         ## xmm0 = mem[0],zero
	movsd	%xmm0, -80(%rbp)
	movl	%eax, -112(%rbp)        ## 4-byte Spill
LBB0_1:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_3 Depth 2
	movsd	-80(%rbp), %xmm0        ## xmm0 = mem[0],zero
	movsd	-16(%rbp), %xmm1        ## xmm1 = mem[0],zero
	ucomisd	%xmm0, %xmm1
	jb	LBB0_6
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	movsd	LCPI0_0(%rip), %xmm0    ## xmm0 = mem[0],zero
	movsd	%xmm0, -64(%rbp)
	movsd	%xmm0, -40(%rbp)
	movsd	-80(%rbp), %xmm1        ## xmm1 = mem[0],zero
	movsd	%xmm1, -48(%rbp)
	movsd	%xmm0, -72(%rbp)
	movsd	%xmm0, -56(%rbp)
LBB0_3:                                 ##   Parent Loop BB0_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movsd	LCPI0_0(%rip), %xmm0    ## xmm0 = mem[0],zero
	movsd	-64(%rbp), %xmm1        ## xmm1 = mem[0],zero
	mulsd	-80(%rbp), %xmm1
	mulsd	-80(%rbp), %xmm1
	movsd	%xmm1, -64(%rbp)
	movsd	-56(%rbp), %xmm1        ## xmm1 = mem[0],zero
	mulsd	-72(%rbp), %xmm1
	movsd	%xmm1, -56(%rbp)
	movsd	-56(%rbp), %xmm1        ## xmm1 = mem[0],zero
	movaps	%xmm0, %xmm2
	addsd	-72(%rbp), %xmm2
	mulsd	%xmm2, %xmm1
	movsd	%xmm1, -56(%rbp)
	movsd	-64(%rbp), %xmm1        ## xmm1 = mem[0],zero
	divsd	-56(%rbp), %xmm1
	movsd	%xmm1, -48(%rbp)
	movsd	-40(%rbp), %xmm1        ## xmm1 = mem[0],zero
	addsd	-48(%rbp), %xmm1
	movsd	%xmm1, -40(%rbp)
	movaps	%xmm0, %xmm1
	addsd	-72(%rbp), %xmm1
	movsd	%xmm1, -72(%rbp)
	addsd	-72(%rbp), %xmm0
	movsd	%xmm0, -72(%rbp)
## BB#4:                                ##   in Loop: Header=BB0_3 Depth=2
	movsd	-48(%rbp), %xmm0        ## xmm0 = mem[0],zero
	ucomisd	-32(%rbp), %xmm0
	ja	LBB0_3
## BB#5:                                ##   in Loop: Header=BB0_1 Depth=1
	movsd	-80(%rbp), %xmm0        ## xmm0 = mem[0],zero
	movsd	-40(%rbp), %xmm1        ## xmm1 = mem[0],zero
	movsd	-72(%rbp), %xmm2        ## xmm2 = mem[0],zero
	movsd	-80(%rbp), %xmm3        ## xmm3 = mem[0],zero
	movsd	%xmm0, -120(%rbp)       ## 8-byte Spill
	movaps	%xmm3, %xmm0
	movsd	%xmm2, -128(%rbp)       ## 8-byte Spill
	movsd	%xmm1, -136(%rbp)       ## 8-byte Spill
	callq	_cosh
	leaq	_Lab7_Asm.output_format(%rip), %rdi
	movsd	-120(%rbp), %xmm1       ## 8-byte Reload
                                        ## xmm1 = mem[0],zero
	movsd	%xmm0, -144(%rbp)       ## 8-byte Spill
	movaps	%xmm1, %xmm0
	movsd	-136(%rbp), %xmm1       ## 8-byte Reload
                                        ## xmm1 = mem[0],zero
	movsd	-128(%rbp), %xmm2       ## 8-byte Reload
                                        ## xmm2 = mem[0],zero
	movsd	-144(%rbp), %xmm3       ## 8-byte Reload
                                        ## xmm3 = mem[0],zero
	movb	$4, %al
	callq	_printf
	movsd	-24(%rbp), %xmm0        ## xmm0 = mem[0],zero
	addsd	-80(%rbp), %xmm0
	movsd	%xmm0, -80(%rbp)
	movl	%eax, -148(%rbp)        ## 4-byte Spill
	jmp	LBB0_1
LBB0_6:
	movl	$1, %eax
	addq	$160, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__const
	.align	4                       ## @Lab7_Asm.enter_start_x
_Lab7_Asm.enter_start_x:
	.asciz	"Enter start X: "

_Lab7_Asm.enter_end_x:                  ## @Lab7_Asm.enter_end_x
	.asciz	"Enter end X: "

_Lab7_Asm.enter_delta_x:                ## @Lab7_Asm.enter_delta_x
	.asciz	"Enter step: "

	.align	4                       ## @Lab7_Asm.enter_precision
_Lab7_Asm.enter_precision:
	.asciz	"Enter precision: "

	.align	4                       ## @Lab7_Asm.output_format
_Lab7_Asm.output_format:
	.asciz	"Current X: %lf Calculated: %lf N: %lf Internal function: %lf\n"

_Lab7_Asm.scanf_format:                 ## @Lab7_Asm.scanf_format
	.asciz	"%lf"


.subsections_via_symbols
