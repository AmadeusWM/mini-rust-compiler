	.text
	.file	"2avma1vvoc4c81oj"
	.section	.text._ZN3std10sys_common9backtrace28__rust_begin_short_backtrace17hbbb535049446789dE,"ax",@progbits
	.p2align	4, 0x90
	.type	_ZN3std10sys_common9backtrace28__rust_begin_short_backtrace17hbbb535049446789dE,@function
_ZN3std10sys_common9backtrace28__rust_begin_short_backtrace17hbbb535049446789dE:
.Lfunc_begin0:
	.file	1 "/rustc/e51e98dde6a60637b6a71b8105245b629ac3fe77/library/std/src/sys_common" "backtrace.rs"
	.loc	1 151 0
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
.Ltmp0:
	.file	2 "/rustc/e51e98dde6a60637b6a71b8105245b629ac3fe77/library/core/src" "hint.rs"
	.loc	2 333 27 prologue_end
	movq	%rdi, 16(%rsp)
.Ltmp1:
	.loc	1 155 18
	callq	_ZN4core3ops8function6FnOnce9call_once17h6582b4174c52c6ebE
.Ltmp2:
	.loc	2 334 5
	#APP
	#NO_APP
.Ltmp3:
	.loc	1 161 2 epilogue_begin
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Ltmp4:
.Lfunc_end0:
	.size	_ZN3std10sys_common9backtrace28__rust_begin_short_backtrace17hbbb535049446789dE, .Lfunc_end0-_ZN3std10sys_common9backtrace28__rust_begin_short_backtrace17hbbb535049446789dE
	.cfi_endproc

	.section	.text._ZN3std2rt10lang_start17h459ab148060cdfb6E,"ax",@progbits
	.hidden	_ZN3std2rt10lang_start17h459ab148060cdfb6E
	.globl	_ZN3std2rt10lang_start17h459ab148060cdfb6E
	.p2align	4, 0x90
	.type	_ZN3std2rt10lang_start17h459ab148060cdfb6E,@function
_ZN3std2rt10lang_start17h459ab148060cdfb6E:
.Lfunc_begin1:
	.file	3 "/rustc/e51e98dde6a60637b6a71b8105245b629ac3fe77/library/std/src" "rt.rs"
	.loc	3 159 0
	.cfi_startproc
	subq	$56, %rsp
	.cfi_def_cfa_offset 64
	movl	%ecx, %eax
	movq	%rdx, %rcx
	movq	%rsi, %rdx
	movq	%rdi, 16(%rsp)
	movq	%rdx, 24(%rsp)
	movq	%rcx, 32(%rsp)
	movb	%al, 47(%rsp)
.Ltmp5:
	.loc	3 166 10 prologue_end
	movq	%rdi, 8(%rsp)
	.loc	3 165 17
	leaq	8(%rsp), %rdi
	leaq	.L__unnamed_1(%rip), %rsi
	movzbl	%al, %r8d
	callq	*_ZN3std2rt19lang_start_internal17h892a9bd9313ca5d1E@GOTPCREL(%rip)
	movq	%rax, (%rsp)
	.loc	3 165 12 is_stmt 0
	movq	(%rsp), %rax
	movq	%rax, 48(%rsp)
	.loc	3 172 2 epilogue_begin is_stmt 1
	addq	$56, %rsp
	.cfi_def_cfa_offset 8
	retq
.Ltmp6:
.Lfunc_end1:
	.size	_ZN3std2rt10lang_start17h459ab148060cdfb6E, .Lfunc_end1-_ZN3std2rt10lang_start17h459ab148060cdfb6E
	.cfi_endproc

	.section	".text._ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h59b2a4c65a5ce27aE","ax",@progbits
	.p2align	4, 0x90
	.type	_ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h59b2a4c65a5ce27aE,@function
_ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h59b2a4c65a5ce27aE:
.Lfunc_begin2:
	.loc	3 166 0
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, 8(%rsp)
.Ltmp7:
	.loc	3 166 77 prologue_end
	movq	(%rdi), %rdi
	.loc	3 166 18 is_stmt 0
	callq	_ZN3std10sys_common9backtrace28__rust_begin_short_backtrace17hbbb535049446789dE
	callq	_ZN54_$LT$$LP$$RP$$u20$as$u20$std..process..Termination$GT$6report17ha69a6472a92175f8E
	movb	%al, 7(%rsp)
.Ltmp8:
	.file	4 "/rustc/e51e98dde6a60637b6a71b8105245b629ac3fe77/library/std/src" "process.rs"
	.loc	4 1959 9 is_stmt 1
	leaq	7(%rsp), %rax
	movq	%rax, 16(%rsp)
.Ltmp9:
	.file	5 "/rustc/e51e98dde6a60637b6a71b8105245b629ac3fe77/library/std/src/sys/unix/process" "process_common.rs"
	.loc	5 639 9
	movzbl	7(%rsp), %eax
.Ltmp10:
	.loc	3 166 100 epilogue_begin
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Ltmp11:
.Lfunc_end2:
	.size	_ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h59b2a4c65a5ce27aE, .Lfunc_end2-_ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h59b2a4c65a5ce27aE
	.cfi_endproc

	.section	.text._ZN4core3fmt9Arguments9new_const17hb3c5b26150c6cd24E,"ax",@progbits
	.p2align	4, 0x90
	.type	_ZN4core3fmt9Arguments9new_const17hb3c5b26150c6cd24E,@function
_ZN4core3fmt9Arguments9new_const17hb3c5b26150c6cd24E:
.Lfunc_begin3:
	.file	6 "/rustc/e51e98dde6a60637b6a71b8105245b629ac3fe77/library/core/src/fmt" "mod.rs"
	.loc	6 321 0
	.cfi_startproc
	subq	$104, %rsp
	.cfi_def_cfa_offset 112
	movq	%rdx, 8(%rsp)
	movq	%rsi, 16(%rsp)
	movq	%rdi, 24(%rsp)
	movq	%rdi, 32(%rsp)
	movq	%rsi, 88(%rsp)
	movq	%rdx, 96(%rsp)
.Ltmp12:
	.loc	6 322 12 prologue_end
	cmpq	$1, %rdx
	ja	.LBB3_2
	.loc	6 0 12 is_stmt 0
	movq	32(%rsp), %rax
	movq	24(%rsp), %rcx
	movq	8(%rsp), %rdx
	movq	16(%rsp), %rsi
	.loc	6 325 9 is_stmt 1
	movq	%rsi, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	.L__unnamed_2(%rip), %rsi
	movq	.L__unnamed_2+8(%rip), %rdx
	movq	%rsi, 32(%rcx)
	movq	%rdx, 40(%rcx)
	leaq	.L__unnamed_3(%rip), %rdx
	movq	%rdx, 16(%rcx)
	movq	$0, 24(%rcx)
	.loc	6 326 6 epilogue_begin
	addq	$104, %rsp
	.cfi_def_cfa_offset 8
	retq
.LBB3_2:
	.cfi_def_cfa_offset 112
	.loc	6 323 13
	leaq	.L__unnamed_4(%rip), %rsi
	leaq	40(%rsp), %rdi
	movq	%rdi, (%rsp)
	movl	$1, %edx
	callq	_ZN4core3fmt9Arguments9new_const17hb3c5b26150c6cd24E
	movq	(%rsp), %rdi
	leaq	.L__unnamed_5(%rip), %rsi
	movq	_ZN4core9panicking9panic_fmt17h3f2350d70561f7cbE@GOTPCREL(%rip), %rax
	callq	*%rax
.Ltmp13:
.Lfunc_end3:
	.size	_ZN4core3fmt9Arguments9new_const17hb3c5b26150c6cd24E, .Lfunc_end3-_ZN4core3fmt9Arguments9new_const17hb3c5b26150c6cd24E
	.cfi_endproc

	.section	".text._ZN4core3ops8function6FnOnce40call_once$u7b$$u7b$vtable.shim$u7d$$u7d$17h0d12a47bdff8cb5fE","ax",@progbits
	.p2align	4, 0x90
	.type	_ZN4core3ops8function6FnOnce40call_once$u7b$$u7b$vtable.shim$u7d$$u7d$17h0d12a47bdff8cb5fE,@function
_ZN4core3ops8function6FnOnce40call_once$u7b$$u7b$vtable.shim$u7d$$u7d$17h0d12a47bdff8cb5fE:
.Lfunc_begin4:
	.file	7 "/rustc/e51e98dde6a60637b6a71b8105245b629ac3fe77/library/core/src/ops" "function.rs"
	.loc	7 250 0
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, 16(%rsp)
.Ltmp14:
	.loc	7 250 5 prologue_end
	movq	(%rdi), %rdi
	callq	_ZN4core3ops8function6FnOnce9call_once17h83681d2563d97d84E
	.loc	7 250 5 epilogue_begin is_stmt 0
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Ltmp15:
.Lfunc_end4:
	.size	_ZN4core3ops8function6FnOnce40call_once$u7b$$u7b$vtable.shim$u7d$$u7d$17h0d12a47bdff8cb5fE, .Lfunc_end4-_ZN4core3ops8function6FnOnce40call_once$u7b$$u7b$vtable.shim$u7d$$u7d$17h0d12a47bdff8cb5fE
	.cfi_endproc

	.section	.text._ZN4core3ops8function6FnOnce9call_once17h6582b4174c52c6ebE,"ax",@progbits
	.p2align	4, 0x90
	.type	_ZN4core3ops8function6FnOnce9call_once17h6582b4174c52c6ebE,@function
_ZN4core3ops8function6FnOnce9call_once17h6582b4174c52c6ebE:
.Lfunc_begin5:
	.loc	7 250 0 is_stmt 1
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, 16(%rsp)
.Ltmp16:
	.loc	7 250 5 prologue_end
	callq	*%rdi
	.loc	7 250 5 epilogue_begin is_stmt 0
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Ltmp17:
.Lfunc_end5:
	.size	_ZN4core3ops8function6FnOnce9call_once17h6582b4174c52c6ebE, .Lfunc_end5-_ZN4core3ops8function6FnOnce9call_once17h6582b4174c52c6ebE
	.cfi_endproc

	.section	.text._ZN4core3ops8function6FnOnce9call_once17h83681d2563d97d84E,"ax",@progbits
	.p2align	4, 0x90
	.type	_ZN4core3ops8function6FnOnce9call_once17h83681d2563d97d84E,@function
_ZN4core3ops8function6FnOnce9call_once17h83681d2563d97d84E:
.Lfunc_begin6:
	.loc	7 250 0 is_stmt 1
	.cfi_startproc
	.cfi_personality 155, DW.ref.rust_eh_personality
	.cfi_lsda 27, .Lexception0
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%rdi, 8(%rsp)
.Ltmp18:
	leaq	8(%rsp), %rdi
.Ltmp21:
	.loc	7 250 5 prologue_end
	callq	_ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h59b2a4c65a5ce27aE
.Ltmp19:
	movl	%eax, 4(%rsp)
	jmp	.LBB6_3
.LBB6_1:
	movq	24(%rsp), %rdi
	callq	_Unwind_Resume@PLT
.LBB6_2:
.Ltmp20:
	.loc	7 0 5 is_stmt 0
	movq	%rax, %rcx
	movl	%edx, %eax
	movq	%rcx, 24(%rsp)
	movl	%eax, 32(%rsp)
	jmp	.LBB6_1
.LBB6_3:
	movl	4(%rsp), %eax
	.loc	7 250 5 epilogue_begin
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	retq
.Ltmp22:
.Lfunc_end6:
	.size	_ZN4core3ops8function6FnOnce9call_once17h83681d2563d97d84E, .Lfunc_end6-_ZN4core3ops8function6FnOnce9call_once17h83681d2563d97d84E
	.cfi_endproc
	.section	.gcc_except_table._ZN4core3ops8function6FnOnce9call_once17h83681d2563d97d84E,"a",@progbits
	.p2align	2, 0x0
GCC_except_table6:
.Lexception0:
	.byte	255
	.byte	255
	.byte	1
	.uleb128 .Lcst_end0-.Lcst_begin0
.Lcst_begin0:
	.uleb128 .Ltmp18-.Lfunc_begin6
	.uleb128 .Ltmp19-.Ltmp18
	.uleb128 .Ltmp20-.Lfunc_begin6
	.byte	0
	.uleb128 .Ltmp19-.Lfunc_begin6
	.uleb128 .Lfunc_end6-.Ltmp19
	.byte	0
	.byte	0
.Lcst_end0:
	.p2align	2, 0x0

	.section	".text._ZN4core3ptr85drop_in_place$LT$std..rt..lang_start$LT$$LP$$RP$$GT$..$u7b$$u7b$closure$u7d$$u7d$$GT$17he833ba5414404f82E","ax",@progbits
	.p2align	4, 0x90
	.type	_ZN4core3ptr85drop_in_place$LT$std..rt..lang_start$LT$$LP$$RP$$GT$..$u7b$$u7b$closure$u7d$$u7d$$GT$17he833ba5414404f82E,@function
_ZN4core3ptr85drop_in_place$LT$std..rt..lang_start$LT$$LP$$RP$$GT$..$u7b$$u7b$closure$u7d$$u7d$$GT$17he833ba5414404f82E:
.Lfunc_begin7:
	.file	8 "/rustc/e51e98dde6a60637b6a71b8105245b629ac3fe77/library/core/src/ptr" "mod.rs"
	.loc	8 507 0 is_stmt 1
	.cfi_startproc
	movq	%rdi, -8(%rsp)
.Ltmp23:
	.loc	8 507 1 prologue_end
	retq
.Ltmp24:
.Lfunc_end7:
	.size	_ZN4core3ptr85drop_in_place$LT$std..rt..lang_start$LT$$LP$$RP$$GT$..$u7b$$u7b$closure$u7d$$u7d$$GT$17he833ba5414404f82E, .Lfunc_end7-_ZN4core3ptr85drop_in_place$LT$std..rt..lang_start$LT$$LP$$RP$$GT$..$u7b$$u7b$closure$u7d$$u7d$$GT$17he833ba5414404f82E
	.cfi_endproc

	.section	".text._ZN54_$LT$$LP$$RP$$u20$as$u20$std..process..Termination$GT$6report17ha69a6472a92175f8E","ax",@progbits
	.p2align	4, 0x90
	.type	_ZN54_$LT$$LP$$RP$$u20$as$u20$std..process..Termination$GT$6report17ha69a6472a92175f8E,@function
_ZN54_$LT$$LP$$RP$$u20$as$u20$std..process..Termination$GT$6report17ha69a6472a92175f8E:
.Lfunc_begin8:
	.cfi_startproc
	.loc	4 2333 6 prologue_end
	xorl	%eax, %eax
	retq
.Ltmp25:
.Lfunc_end8:
	.size	_ZN54_$LT$$LP$$RP$$u20$as$u20$std..process..Termination$GT$6report17ha69a6472a92175f8E, .Lfunc_end8-_ZN54_$LT$$LP$$RP$$u20$as$u20$std..process..Termination$GT$6report17ha69a6472a92175f8E
	.cfi_endproc

	.section	.text._ZN11hello_world4main17h842f481536ab1aa2E,"ax",@progbits
	.p2align	4, 0x90
	.type	_ZN11hello_world4main17h842f481536ab1aa2E,@function
_ZN11hello_world4main17h842f481536ab1aa2E:
.Lfunc_begin9:
	.file	9 "/home/amadeusw/university/master1/compilers/mini-rust-compiler/test/hello_world" "src/main.rs"
	.loc	9 1 0
	.cfi_startproc
	subq	$56, %rsp
	.cfi_def_cfa_offset 64
.Ltmp26:
	.loc	9 2 5 prologue_end
	leaq	8(%rsp), %rdi
	leaq	.L__unnamed_6(%rip), %rsi
	movl	$1, %edx
	callq	_ZN4core3fmt9Arguments9new_const17hb3c5b26150c6cd24E
	leaq	8(%rsp), %rdi
	callq	*_ZN3std2io5stdio6_print17hfb5fdd73d3d2794dE@GOTPCREL(%rip)
	.loc	9 3 2 epilogue_begin
	addq	$56, %rsp
	.cfi_def_cfa_offset 8
	retq
.Ltmp27:
.Lfunc_end9:
	.size	_ZN11hello_world4main17h842f481536ab1aa2E, .Lfunc_end9-_ZN11hello_world4main17h842f481536ab1aa2E
	.cfi_endproc

	.section	.text.main,"ax",@progbits
	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:
.Lfunc_begin10:
	.cfi_startproc
	pushq	%rax
	.cfi_def_cfa_offset 16
	movq	%rsi, %rdx
	movq	__rustc_debug_gdb_scripts_section__@GOTPCREL(%rip), %rax
	movb	(%rax), %al
	movslq	%edi, %rsi
	leaq	_ZN11hello_world4main17h842f481536ab1aa2E(%rip), %rdi
	xorl	%ecx, %ecx
	callq	_ZN3std2rt10lang_start17h459ab148060cdfb6E
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end10:
	.size	main, .Lfunc_end10-main
	.cfi_endproc

	.type	.L__unnamed_1,@object
	.section	.data.rel.ro..L__unnamed_1,"aw",@progbits
	.p2align	3, 0x0
.L__unnamed_1:
	.quad	_ZN4core3ptr85drop_in_place$LT$std..rt..lang_start$LT$$LP$$RP$$GT$..$u7b$$u7b$closure$u7d$$u7d$$GT$17he833ba5414404f82E
	.asciz	"\b\000\000\000\000\000\000\000\b\000\000\000\000\000\000"
	.quad	_ZN4core3ops8function6FnOnce40call_once$u7b$$u7b$vtable.shim$u7d$$u7d$17h0d12a47bdff8cb5fE
	.quad	_ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h59b2a4c65a5ce27aE
	.quad	_ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h59b2a4c65a5ce27aE
	.size	.L__unnamed_1, 48

	.type	.L__unnamed_3,@object
	.section	.rodata..L__unnamed_3,"a",@progbits
	.p2align	3, 0x0
.L__unnamed_3:
	.size	.L__unnamed_3, 0

	.type	.L__unnamed_2,@object
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	3, 0x0
.L__unnamed_2:
	.zero	8
	.zero	8
	.size	.L__unnamed_2, 16

	.type	.L__unnamed_7,@object
	.section	.rodata..L__unnamed_7,"a",@progbits
.L__unnamed_7:
	.ascii	"invalid args"
	.size	.L__unnamed_7, 12

	.type	.L__unnamed_4,@object
	.section	.data.rel.ro..L__unnamed_4,"aw",@progbits
	.p2align	3, 0x0
.L__unnamed_4:
	.quad	.L__unnamed_7
	.asciz	"\f\000\000\000\000\000\000"
	.size	.L__unnamed_4, 16

	.type	.L__unnamed_8,@object
	.section	.rodata..L__unnamed_8,"a",@progbits
.L__unnamed_8:
	.ascii	"/rustc/e51e98dde6a60637b6a71b8105245b629ac3fe77/library/core/src/fmt/mod.rs"
	.size	.L__unnamed_8, 75

	.type	.L__unnamed_5,@object
	.section	.data.rel.ro..L__unnamed_5,"aw",@progbits
	.p2align	3, 0x0
.L__unnamed_5:
	.quad	.L__unnamed_8
	.asciz	"K\000\000\000\000\000\000\000C\001\000\000\r\000\000"
	.size	.L__unnamed_5, 24

	.type	.L__unnamed_9,@object
	.section	.rodata..L__unnamed_9,"a",@progbits
.L__unnamed_9:
	.ascii	"Hello, world!\n"
	.size	.L__unnamed_9, 14

	.type	.L__unnamed_6,@object
	.section	.data.rel.ro..L__unnamed_6,"aw",@progbits
	.p2align	3, 0x0
.L__unnamed_6:
	.quad	.L__unnamed_9
	.asciz	"\016\000\000\000\000\000\000"
	.size	.L__unnamed_6, 16

	.type	__rustc_debug_gdb_scripts_section__,@object
	.section	.debug_gdb_scripts,"aMS",@progbits,1,unique,1
	.weak	__rustc_debug_gdb_scripts_section__
__rustc_debug_gdb_scripts_section__:
	.asciz	"\001gdb_load_rust_pretty_printers.py"
	.size	__rustc_debug_gdb_scripts_section__, 34

	.section	.debug_abbrev,"",@progbits
	.byte	1
	.byte	17
	.byte	1
	.byte	37
	.byte	14
	.byte	19
	.byte	5
	.byte	3
	.byte	14
	.byte	16
	.byte	23
	.byte	27
	.byte	14
	.byte	17
	.byte	1
	.byte	85
	.byte	23
	.byte	0
	.byte	0
	.byte	2
	.byte	52
	.byte	0
	.byte	3
	.byte	14
	.byte	73
	.byte	19
	.byte	2
	.byte	24
	.byte	0
	.byte	0
	.byte	3
	.byte	19
	.byte	1
	.byte	29
	.byte	19
	.byte	3
	.byte	14
	.byte	11
	.byte	11
	.ascii	"\210\001"
	.byte	15
	.byte	0
	.byte	0
	.byte	4
	.byte	13
	.byte	0
	.byte	3
	.byte	14
	.byte	73
	.byte	19
	.ascii	"\210\001"
	.byte	15
	.byte	56
	.byte	11
	.byte	0
	.byte	0
	.byte	5
	.byte	15
	.byte	0
	.byte	73
	.byte	19
	.byte	3
	.byte	14
	.byte	51
	.byte	6
	.byte	0
	.byte	0
	.byte	6
	.byte	36
	.byte	0
	.byte	3
	.byte	14
	.byte	62
	.byte	11
	.byte	11
	.byte	11
	.byte	0
	.byte	0
	.byte	7
	.byte	57
	.byte	1
	.byte	3
	.byte	14
	.byte	0
	.byte	0
	.byte	8
	.byte	19
	.byte	1
	.byte	3
	.byte	14
	.byte	11
	.byte	11
	.ascii	"\210\001"
	.byte	15
	.byte	0
	.byte	0
	.byte	9
	.byte	46
	.byte	1
	.byte	17
	.byte	1
	.byte	18
	.byte	6
	.byte	64
	.byte	24
	.byte	110
	.byte	14
	.byte	3
	.byte	14
	.byte	58
	.byte	11
	.byte	59
	.byte	11
	.byte	73
	.byte	19
	.byte	0
	.byte	0
	.byte	10
	.byte	52
	.byte	0
	.byte	2
	.byte	24
	.byte	3
	.byte	14
	.ascii	"\210\001"
	.byte	15
	.byte	58
	.byte	11
	.byte	59
	.byte	11
	.byte	73
	.byte	19
	.byte	0
	.byte	0
	.byte	11
	.byte	29
	.byte	1
	.byte	49
	.byte	19
	.byte	17
	.byte	1
	.byte	18
	.byte	6
	.byte	88
	.byte	11
	.byte	89
	.byte	11
	.byte	87
	.byte	11
	.byte	0
	.byte	0
	.byte	12
	.byte	11
	.byte	1
	.byte	17
	.byte	1
	.byte	18
	.byte	6
	.byte	0
	.byte	0
	.byte	13
	.byte	5
	.byte	0
	.byte	2
	.byte	24
	.byte	49
	.byte	19
	.byte	0
	.byte	0
	.byte	14
	.byte	29
	.byte	1
	.byte	49
	.byte	19
	.byte	17
	.byte	1
	.byte	18
	.byte	6
	.byte	88
	.byte	11
	.byte	89
	.byte	5
	.byte	87
	.byte	11
	.byte	0
	.byte	0
	.byte	15
	.byte	47
	.byte	0
	.byte	73
	.byte	19
	.byte	3
	.byte	14
	.byte	0
	.byte	0
	.byte	16
	.byte	5
	.byte	0
	.byte	2
	.byte	24
	.byte	3
	.byte	14
	.byte	58
	.byte	11
	.byte	59
	.byte	11
	.byte	73
	.byte	19
	.byte	0
	.byte	0
	.byte	17
	.byte	46
	.byte	1
	.byte	17
	.byte	1
	.byte	18
	.byte	6
	.byte	64
	.byte	24
	.byte	110
	.byte	14
	.byte	3
	.byte	14
	.byte	58
	.byte	11
	.byte	59
	.byte	11
	.byte	0
	.byte	0
	.byte	18
	.byte	11
	.byte	1
	.byte	85
	.byte	23
	.byte	0
	.byte	0
	.byte	19
	.byte	52
	.byte	0
	.byte	2
	.byte	24
	.byte	3
	.byte	14
	.byte	58
	.byte	11
	.byte	59
	.byte	11
	.byte	73
	.byte	19
	.byte	0
	.byte	0
	.byte	20
	.byte	29
	.byte	1
	.byte	49
	.byte	19
	.byte	85
	.byte	23
	.byte	88
	.byte	11
	.byte	89
	.byte	11
	.byte	87
	.byte	11
	.byte	0
	.byte	0
	.byte	21
	.byte	52
	.byte	0
	.byte	2
	.byte	24
	.byte	49
	.byte	19
	.byte	0
	.byte	0
	.byte	22
	.byte	19
	.byte	1
	.byte	3
	.byte	14
	.byte	11
	.byte	11
	.byte	50
	.byte	11
	.ascii	"\210\001"
	.byte	15
	.byte	0
	.byte	0
	.byte	23
	.byte	13
	.byte	0
	.byte	3
	.byte	14
	.byte	73
	.byte	19
	.ascii	"\210\001"
	.byte	15
	.byte	56
	.byte	11
	.byte	50
	.byte	11
	.byte	0
	.byte	0
	.byte	24
	.byte	46
	.byte	1
	.byte	110
	.byte	14
	.byte	3
	.byte	14
	.byte	58
	.byte	11
	.byte	59
	.byte	5
	.byte	73
	.byte	19
	.byte	60
	.byte	25
	.byte	0
	.byte	0
	.byte	25
	.byte	5
	.byte	0
	.byte	73
	.byte	19
	.byte	0
	.byte	0
	.byte	26
	.byte	46
	.byte	1
	.byte	17
	.byte	1
	.byte	18
	.byte	6
	.byte	64
	.byte	24
	.byte	110
	.byte	14
	.byte	3
	.byte	14
	.byte	58
	.byte	11
	.byte	59
	.byte	5
	.byte	73
	.byte	19
	.byte	0
	.byte	0
	.byte	27
	.byte	5
	.byte	0
	.byte	2
	.byte	24
	.byte	58
	.byte	11
	.byte	59
	.byte	5
	.byte	73
	.byte	19
	.byte	0
	.byte	0
	.byte	28
	.byte	52
	.byte	0
	.byte	2
	.byte	24
	.byte	3
	.byte	14
	.byte	58
	.byte	11
	.byte	59
	.byte	5
	.byte	73
	.byte	19
	.byte	0
	.byte	0
	.byte	29
	.byte	21
	.byte	0
	.byte	0
	.byte	0
	.byte	30
	.byte	4
	.byte	1
	.byte	73
	.byte	19
	.byte	109
	.byte	25
	.byte	3
	.byte	14
	.byte	11
	.byte	11
	.ascii	"\210\001"
	.byte	15
	.byte	0
	.byte	0
	.byte	31
	.byte	40
	.byte	0
	.byte	3
	.byte	14
	.byte	28
	.byte	15
	.byte	0
	.byte	0
	.byte	32
	.byte	51
	.byte	1
	.byte	21
	.byte	19
	.byte	0
	.byte	0
	.byte	33
	.byte	13
	.byte	0
	.byte	73
	.byte	19
	.ascii	"\210\001"
	.byte	15
	.byte	56
	.byte	11
	.byte	52
	.byte	25
	.byte	0
	.byte	0
	.byte	34
	.byte	25
	.byte	1
	.byte	22
	.byte	11
	.byte	0
	.byte	0
	.byte	35
	.byte	19
	.byte	0
	.byte	3
	.byte	14
	.byte	11
	.byte	11
	.byte	50
	.byte	11
	.ascii	"\210\001"
	.byte	15
	.byte	0
	.byte	0
	.byte	36
	.byte	19
	.byte	0
	.byte	3
	.byte	14
	.byte	11
	.byte	11
	.ascii	"\210\001"
	.byte	15
	.byte	0
	.byte	0
	.byte	37
	.byte	46
	.byte	1
	.byte	110
	.byte	14
	.byte	3
	.byte	14
	.byte	58
	.byte	11
	.byte	59
	.byte	5
	.byte	32
	.byte	11
	.byte	0
	.byte	0
	.byte	38
	.byte	11
	.byte	1
	.byte	0
	.byte	0
	.byte	39
	.byte	52
	.byte	0
	.byte	3
	.byte	14
	.byte	58
	.byte	11
	.byte	59
	.byte	5
	.byte	73
	.byte	19
	.byte	0
	.byte	0
	.byte	40
	.byte	25
	.byte	1
	.byte	0
	.byte	0
	.byte	41
	.byte	5
	.byte	0
	.byte	2
	.byte	24
	.byte	58
	.byte	11
	.byte	59
	.byte	11
	.byte	73
	.byte	19
	.byte	0
	.byte	0
	.byte	42
	.byte	46
	.byte	1
	.byte	17
	.byte	1
	.byte	18
	.byte	6
	.byte	64
	.byte	24
	.byte	110
	.byte	14
	.byte	3
	.byte	14
	.byte	58
	.byte	11
	.byte	59
	.byte	5
	.byte	0
	.byte	0
	.byte	43
	.byte	46
	.byte	1
	.byte	71
	.byte	19
	.byte	32
	.byte	11
	.byte	0
	.byte	0
	.byte	44
	.byte	5
	.byte	0
	.byte	3
	.byte	14
	.byte	58
	.byte	11
	.byte	59
	.byte	5
	.byte	73
	.byte	19
	.byte	0
	.byte	0
	.byte	45
	.byte	15
	.byte	0
	.byte	73
	.byte	19
	.byte	51
	.byte	6
	.byte	0
	.byte	0
	.byte	46
	.byte	21
	.byte	1
	.byte	73
	.byte	19
	.byte	0
	.byte	0
	.byte	47
	.byte	1
	.byte	1
	.byte	73
	.byte	19
	.byte	0
	.byte	0
	.byte	48
	.byte	33
	.byte	0
	.byte	73
	.byte	19
	.byte	34
	.byte	13
	.byte	55
	.byte	11
	.byte	0
	.byte	0
	.byte	49
	.byte	36
	.byte	0
	.byte	3
	.byte	14
	.byte	11
	.byte	11
	.byte	62
	.byte	11
	.byte	0
	.byte	0
	.byte	50
	.byte	46
	.byte	1
	.byte	17
	.byte	1
	.byte	18
	.byte	6
	.byte	64
	.byte	24
	.byte	71
	.byte	19
	.byte	0
	.byte	0
	.byte	51
	.byte	5
	.byte	0
	.byte	2
	.byte	24
	.byte	3
	.byte	14
	.byte	58
	.byte	11
	.byte	59
	.byte	5
	.byte	73
	.byte	19
	.byte	0
	.byte	0
	.byte	52
	.byte	46
	.byte	0
	.byte	17
	.byte	1
	.byte	18
	.byte	6
	.byte	64
	.byte	24
	.byte	110
	.byte	14
	.byte	3
	.byte	14
	.byte	58
	.byte	11
	.byte	59
	.byte	11
	.byte	106
	.byte	25
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_info,"",@progbits
.Lcu_begin0:
	.long	.Ldebug_info_end0-.Ldebug_info_start0
.Ldebug_info_start0:
	.short	4
	.long	.debug_abbrev
	.byte	8
	.byte	1
	.long	.Linfo_string0
	.short	28
	.long	.Linfo_string1
	.long	.Lline_table_start0
	.long	.Linfo_string2
	.quad	0
	.long	.Ldebug_ranges3
	.byte	2
	.long	.Linfo_string3
	.long	61
	.byte	9
	.byte	3
	.quad	.L__unnamed_1
	.byte	3
	.long	181
	.long	.Linfo_string19
	.byte	48
	.byte	8
	.byte	4
	.long	.Linfo_string4
	.long	139
	.byte	8
	.byte	0
	.byte	4
	.long	.Linfo_string7
	.long	159
	.byte	8
	.byte	8
	.byte	4
	.long	.Linfo_string9
	.long	159
	.byte	8
	.byte	16
	.byte	4
	.long	.Linfo_string10
	.long	139
	.byte	8
	.byte	24
	.byte	4
	.long	.Linfo_string11
	.long	139
	.byte	8
	.byte	32
	.byte	4
	.long	.Linfo_string12
	.long	139
	.byte	8
	.byte	40
	.byte	0
	.byte	5
	.long	152
	.long	.Linfo_string6
	.long	0
	.byte	6
	.long	.Linfo_string5
	.byte	7
	.byte	0
	.byte	6
	.long	.Linfo_string8
	.byte	7
	.byte	8
	.byte	7
	.long	.Linfo_string13
	.byte	7
	.long	.Linfo_string14
	.byte	7
	.long	.Linfo_string15
	.byte	8
	.long	.Linfo_string18
	.byte	8
	.byte	8
	.byte	4
	.long	.Linfo_string16
	.long	736
	.byte	8
	.byte	0
	.byte	0
	.byte	9
	.quad	.Lfunc_begin2
	.long	.Lfunc_end2-.Lfunc_begin2
	.byte	1
	.byte	87
	.long	.Linfo_string111
	.long	.Linfo_string112
	.byte	3
	.byte	166
	.long	1857
	.byte	10
	.byte	3
	.byte	145
	.byte	8
	.byte	6
	.long	.Linfo_string16
	.byte	1
	.byte	3
	.byte	160
	.long	736
	.byte	11
	.long	1864
	.quad	.Ltmp8
	.long	.Ltmp10-.Ltmp8
	.byte	3
	.byte	166
	.byte	92
	.byte	12
	.quad	.Ltmp8
	.long	.Ltmp10-.Ltmp8
	.byte	13
	.byte	2
	.byte	145
	.byte	7
	.long	1871
	.byte	14
	.long	1898
	.quad	.Ltmp9
	.long	.Ltmp10-.Ltmp9
	.byte	4
	.short	1959
	.byte	16
	.byte	12
	.quad	.Ltmp9
	.long	.Ltmp10-.Ltmp9
	.byte	13
	.byte	2
	.byte	145
	.byte	16
	.long	1905
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	15
	.long	152
	.long	.Linfo_string29
	.byte	0
	.byte	0
	.byte	9
	.quad	.Lfunc_begin1
	.long	.Lfunc_end1-.Lfunc_begin1
	.byte	1
	.byte	87
	.long	.Linfo_string108
	.long	.Linfo_string109
	.byte	3
	.byte	159
	.long	2297
	.byte	16
	.byte	2
	.byte	145
	.byte	16
	.long	.Linfo_string16
	.byte	3
	.byte	160
	.long	736
	.byte	16
	.byte	2
	.byte	145
	.byte	24
	.long	.Linfo_string126
	.byte	3
	.byte	161
	.long	2297
	.byte	16
	.byte	2
	.byte	145
	.byte	32
	.long	.Linfo_string127
	.byte	3
	.byte	162
	.long	2304
	.byte	16
	.byte	2
	.byte	145
	.byte	47
	.long	.Linfo_string130
	.byte	3
	.byte	163
	.long	1850
	.byte	15
	.long	152
	.long	.Linfo_string29
	.byte	0
	.byte	0
	.byte	7
	.long	.Linfo_string33
	.byte	7
	.long	.Linfo_string34
	.byte	17
	.quad	.Lfunc_begin0
	.long	.Lfunc_end0-.Lfunc_begin0
	.byte	1
	.byte	87
	.long	.Linfo_string106
	.long	.Linfo_string107
	.byte	1
	.byte	151
	.byte	16
	.byte	2
	.byte	145
	.byte	16
	.long	.Linfo_string125
	.byte	1
	.byte	151
	.long	736
	.byte	18
	.long	.Ldebug_ranges0
	.byte	19
	.byte	2
	.byte	145
	.byte	15
	.long	.Linfo_string77
	.byte	1
	.byte	155
	.long	152
	.byte	20
	.long	1205
	.long	.Ldebug_ranges1
	.byte	1
	.byte	158
	.byte	5
	.byte	18
	.long	.Ldebug_ranges2
	.byte	21
	.byte	2
	.byte	145
	.byte	14
	.long	1228
	.byte	0
	.byte	0
	.byte	0
	.byte	15
	.long	736
	.long	.Linfo_string105
	.byte	15
	.long	152
	.long	.Linfo_string29
	.byte	0
	.byte	0
	.byte	0
	.byte	7
	.long	.Linfo_string35
	.byte	22
	.long	.Linfo_string40
	.byte	1
	.byte	1
	.byte	1
	.byte	23
	.long	.Linfo_string36
	.long	688
	.byte	1
	.byte	0
	.byte	3
	.byte	24
	.long	.Linfo_string41
	.long	.Linfo_string42
	.byte	4
	.short	1958
	.long	1857

	.byte	25
	.long	561
	.byte	0
	.byte	0
	.byte	7
	.long	.Linfo_string103
	.byte	26
	.quad	.Lfunc_begin8
	.long	.Lfunc_end8-.Lfunc_begin8
	.byte	1
	.byte	87
	.long	.Linfo_string122
	.long	.Linfo_string123
	.byte	4
	.short	2331
	.long	561
	.byte	27
	.byte	2
	.byte	145
	.byte	127
	.byte	4
	.short	2331
	.long	152
	.byte	28
	.byte	2
	.byte	145
	.byte	126
	.long	.Linfo_string44
	.byte	4
	.short	2331
	.long	152
	.byte	0
	.byte	0
	.byte	0
	.byte	7
	.long	.Linfo_string37
	.byte	7
	.long	.Linfo_string38
	.byte	7
	.long	.Linfo_string35
	.byte	7
	.long	.Linfo_string39
	.byte	22
	.long	.Linfo_string40
	.byte	1
	.byte	1
	.byte	1
	.byte	23
	.long	.Linfo_string36
	.long	1850
	.byte	1
	.byte	0
	.byte	3
	.byte	24
	.long	.Linfo_string45
	.long	.Linfo_string46
	.byte	5
	.short	638
	.long	1857

	.byte	25
	.long	1885
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	5
	.long	749
	.long	.Linfo_string17
	.long	0
	.byte	29
	.byte	7
	.long	.Linfo_string20
	.byte	7
	.long	.Linfo_string21
	.byte	7
	.long	.Linfo_string14
	.byte	30
	.long	1850

	.long	.Linfo_string27
	.byte	1
	.byte	1
	.byte	31
	.long	.Linfo_string23
	.byte	0
	.byte	31
	.long	.Linfo_string24
	.byte	1
	.byte	31
	.long	.Linfo_string25
	.byte	2
	.byte	31
	.long	.Linfo_string26
	.byte	3
	.byte	0
	.byte	22
	.long	.Linfo_string67
	.byte	56
	.byte	1
	.byte	8
	.byte	23
	.long	.Linfo_string56
	.long	159
	.byte	8
	.byte	32
	.byte	1
	.byte	23
	.long	.Linfo_string57
	.long	2043
	.byte	4
	.byte	40
	.byte	1
	.byte	23
	.long	.Linfo_string9
	.long	765
	.byte	1
	.byte	48
	.byte	1
	.byte	23
	.long	.Linfo_string59
	.long	2050
	.byte	4
	.byte	44
	.byte	1
	.byte	23
	.long	.Linfo_string61
	.long	882
	.byte	8
	.byte	0
	.byte	1
	.byte	23
	.long	.Linfo_string66
	.long	882
	.byte	8
	.byte	16
	.byte	1
	.byte	0
	.byte	22
	.long	.Linfo_string65
	.byte	16
	.byte	1
	.byte	8
	.byte	32
	.long	895
	.byte	33
	.long	1997
	.byte	8
	.byte	0

	.byte	34
	.byte	0
	.byte	4
	.long	.Linfo_string62
	.long	945
	.byte	8
	.byte	0
	.byte	0
	.byte	34
	.byte	1
	.byte	4
	.long	.Linfo_string63
	.long	966
	.byte	8
	.byte	0
	.byte	0
	.byte	34
	.byte	2
	.byte	4
	.long	.Linfo_string64
	.long	987
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	22
	.long	.Linfo_string62
	.byte	16
	.byte	1
	.byte	8
	.byte	23
	.long	.Linfo_string36
	.long	159
	.byte	8
	.byte	8
	.byte	1
	.byte	0
	.byte	22
	.long	.Linfo_string63
	.byte	16
	.byte	1
	.byte	8
	.byte	23
	.long	.Linfo_string36
	.long	159
	.byte	8
	.byte	8
	.byte	1
	.byte	0
	.byte	35
	.long	.Linfo_string64
	.byte	16
	.byte	1
	.byte	8
	.byte	0
	.byte	22
	.long	.Linfo_string94
	.byte	16
	.byte	1
	.byte	8
	.byte	23
	.long	.Linfo_string72
	.long	2096
	.byte	8
	.byte	0
	.byte	3
	.byte	23
	.long	.Linfo_string76
	.long	2109
	.byte	8
	.byte	8
	.byte	3
	.byte	0
	.byte	7
	.long	.Linfo_string73
	.byte	36
	.long	.Linfo_string74
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	22
	.long	.Linfo_string96
	.byte	48
	.byte	1
	.byte	8
	.byte	23
	.long	.Linfo_string48
	.long	1919
	.byte	8
	.byte	0
	.byte	3
	.byte	23
	.long	.Linfo_string21
	.long	1248
	.byte	8
	.byte	32
	.byte	3
	.byte	23
	.long	.Linfo_string71
	.long	2057
	.byte	8
	.byte	16
	.byte	3
	.byte	24
	.long	.Linfo_string97
	.long	.Linfo_string98
	.byte	6
	.short	321
	.long	1043

	.byte	25
	.long	1919
	.byte	0
	.byte	0
	.byte	35
	.long	.Linfo_string79
	.byte	0
	.byte	1
	.byte	1
	.byte	22
	.long	.Linfo_string91
	.byte	64
	.byte	1
	.byte	8
	.byte	23
	.long	.Linfo_string59
	.long	2050
	.byte	4
	.byte	52
	.byte	3
	.byte	23
	.long	.Linfo_string57
	.long	2043
	.byte	4
	.byte	48
	.byte	3
	.byte	23
	.long	.Linfo_string9
	.long	765
	.byte	1
	.byte	56
	.byte	3
	.byte	23
	.long	.Linfo_string66
	.long	1345
	.byte	8
	.byte	0
	.byte	3
	.byte	23
	.long	.Linfo_string61
	.long	1345
	.byte	8
	.byte	16
	.byte	3
	.byte	23
	.long	.Linfo_string84
	.long	2151
	.byte	8
	.byte	32
	.byte	3
	.byte	0
	.byte	0
	.byte	7
	.long	.Linfo_string28
	.byte	37
	.long	.Linfo_string30
	.long	.Linfo_string31
	.byte	2
	.short	333
	.byte	1
	.byte	15
	.long	152
	.long	.Linfo_string29
	.byte	38
	.byte	39
	.long	.Linfo_string32
	.byte	2
	.short	333
	.long	152
	.byte	0
	.byte	0
	.byte	0
	.byte	7
	.long	.Linfo_string53
	.byte	22
	.long	.Linfo_string70
	.byte	16
	.byte	1
	.byte	8
	.byte	32
	.long	1261
	.byte	33
	.long	1997
	.byte	8
	.byte	0

	.byte	34
	.byte	0
	.byte	4
	.long	.Linfo_string55
	.long	1296
	.byte	8
	.byte	0
	.byte	0
	.byte	40
	.byte	4
	.long	.Linfo_string69
	.long	1314
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	22
	.long	.Linfo_string55
	.byte	16
	.byte	1
	.byte	8
	.byte	15
	.long	2004
	.long	.Linfo_string29
	.byte	0
	.byte	22
	.long	.Linfo_string69
	.byte	16
	.byte	1
	.byte	8
	.byte	15
	.long	2004
	.long	.Linfo_string29
	.byte	23
	.long	.Linfo_string36
	.long	2004
	.byte	8
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	22
	.long	.Linfo_string83
	.byte	16
	.byte	1
	.byte	8
	.byte	32
	.long	1358
	.byte	33
	.long	1997
	.byte	8
	.byte	0

	.byte	34
	.byte	0
	.byte	4
	.long	.Linfo_string55
	.long	1394
	.byte	8
	.byte	0
	.byte	0
	.byte	34
	.byte	1
	.byte	4
	.long	.Linfo_string69
	.long	1412
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	22
	.long	.Linfo_string55
	.byte	16
	.byte	1
	.byte	8
	.byte	15
	.long	159
	.long	.Linfo_string29
	.byte	0
	.byte	22
	.long	.Linfo_string69
	.byte	16
	.byte	1
	.byte	8
	.byte	15
	.long	159
	.long	.Linfo_string29
	.byte	23
	.long	.Linfo_string36
	.long	159
	.byte	8
	.byte	8
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	7
	.long	.Linfo_string77
	.byte	22
	.long	.Linfo_string82
	.byte	1
	.byte	1
	.byte	1
	.byte	32
	.long	1462
	.byte	33
	.long	1850
	.byte	1
	.byte	0

	.byte	34
	.byte	0
	.byte	4
	.long	.Linfo_string78
	.long	1498
	.byte	1
	.byte	0
	.byte	0
	.byte	34
	.byte	1
	.byte	4
	.long	.Linfo_string81
	.long	1537
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	22
	.long	.Linfo_string78
	.byte	1
	.byte	1
	.byte	1
	.byte	15
	.long	152
	.long	.Linfo_string29
	.byte	15
	.long	1110
	.long	.Linfo_string80
	.byte	23
	.long	.Linfo_string36
	.long	152
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	22
	.long	.Linfo_string81
	.byte	1
	.byte	1
	.byte	1
	.byte	15
	.long	152
	.long	.Linfo_string29
	.byte	15
	.long	1110
	.long	.Linfo_string80
	.byte	23
	.long	.Linfo_string36
	.long	1110
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	7
	.long	.Linfo_string99
	.byte	7
	.long	.Linfo_string100
	.byte	7
	.long	.Linfo_string101
	.byte	9
	.quad	.Lfunc_begin4
	.long	.Lfunc_end4-.Lfunc_begin4
	.byte	1
	.byte	87
	.long	.Linfo_string115
	.long	.Linfo_string116
	.byte	7
	.byte	250
	.long	1857
	.byte	41
	.byte	2
	.byte	145
	.byte	16
	.byte	7
	.byte	250
	.long	2330
	.byte	41
	.byte	2
	.byte	145
	.byte	15
	.byte	7
	.byte	250
	.long	152
	.byte	15
	.long	181
	.long	.Linfo_string113
	.byte	15
	.long	152
	.long	.Linfo_string114
	.byte	0
	.byte	17
	.quad	.Lfunc_begin5
	.long	.Lfunc_end5-.Lfunc_begin5
	.byte	1
	.byte	87
	.long	.Linfo_string117
	.long	.Linfo_string118
	.byte	7
	.byte	250
	.byte	41
	.byte	2
	.byte	145
	.byte	16
	.byte	7
	.byte	250
	.long	736
	.byte	41
	.byte	2
	.byte	145
	.byte	15
	.byte	7
	.byte	250
	.long	152
	.byte	15
	.long	736
	.long	.Linfo_string113
	.byte	15
	.long	152
	.long	.Linfo_string114
	.byte	0
	.byte	9
	.quad	.Lfunc_begin6
	.long	.Lfunc_end6-.Lfunc_begin6
	.byte	1
	.byte	87
	.long	.Linfo_string119
	.long	.Linfo_string116
	.byte	7
	.byte	250
	.long	1857
	.byte	41
	.byte	2
	.byte	145
	.byte	8
	.byte	7
	.byte	250
	.long	181
	.byte	41
	.byte	2
	.byte	145
	.byte	23
	.byte	7
	.byte	250
	.long	152
	.byte	15
	.long	181
	.long	.Linfo_string113
	.byte	15
	.long	152
	.long	.Linfo_string114
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	7
	.long	.Linfo_string102
	.byte	42
	.quad	.Lfunc_begin7
	.long	.Lfunc_end7-.Lfunc_begin7
	.byte	1
	.byte	87
	.long	.Linfo_string120
	.long	.Linfo_string121
	.byte	8
	.short	507
	.byte	27
	.byte	2
	.byte	145
	.byte	120
	.byte	8
	.short	507
	.long	2330
	.byte	15
	.long	181
	.long	.Linfo_string29
	.byte	0
	.byte	0
	.byte	0
	.byte	6
	.long	.Linfo_string22
	.byte	7
	.byte	1
	.byte	6
	.long	.Linfo_string43
	.byte	5
	.byte	4
	.byte	43
	.long	581
	.byte	1
	.byte	38
	.byte	44
	.long	.Linfo_string44
	.byte	4
	.short	1958
	.long	561
	.byte	0
	.byte	0
	.byte	5
	.long	688
	.long	.Linfo_string47
	.long	0
	.byte	43
	.long	708
	.byte	1
	.byte	38
	.byte	44
	.long	.Linfo_string44
	.byte	5
	.short	638
	.long	1885
	.byte	0
	.byte	0
	.byte	8
	.long	.Linfo_string52
	.byte	16
	.byte	8
	.byte	4
	.long	.Linfo_string49
	.long	1949
	.byte	8
	.byte	0
	.byte	4
	.long	.Linfo_string50
	.long	159
	.byte	8
	.byte	8
	.byte	0
	.byte	45
	.long	1958
	.long	0
	.byte	8
	.long	.Linfo_string51
	.byte	16
	.byte	8
	.byte	4
	.long	.Linfo_string49
	.long	1988
	.byte	8
	.byte	0
	.byte	4
	.long	.Linfo_string50
	.long	159
	.byte	8
	.byte	8
	.byte	0
	.byte	45
	.long	1850
	.long	0
	.byte	6
	.long	.Linfo_string54
	.byte	7
	.byte	8
	.byte	8
	.long	.Linfo_string68
	.byte	16
	.byte	8
	.byte	4
	.long	.Linfo_string49
	.long	2034
	.byte	8
	.byte	0
	.byte	4
	.long	.Linfo_string50
	.long	159
	.byte	8
	.byte	8
	.byte	0
	.byte	45
	.long	801
	.long	0
	.byte	6
	.long	.Linfo_string58
	.byte	16
	.byte	4
	.byte	6
	.long	.Linfo_string60
	.byte	7
	.byte	4
	.byte	8
	.long	.Linfo_string95
	.byte	16
	.byte	8
	.byte	4
	.long	.Linfo_string49
	.long	2087
	.byte	8
	.byte	0
	.byte	4
	.long	.Linfo_string50
	.long	159
	.byte	8
	.byte	8
	.byte	0
	.byte	45
	.long	996
	.long	0
	.byte	5
	.long	1034
	.long	.Linfo_string75
	.long	0
	.byte	5
	.long	2122
	.long	.Linfo_string93
	.long	0
	.byte	46
	.long	1449
	.byte	25
	.long	2096
	.byte	25
	.long	2138
	.byte	0
	.byte	5
	.long	1118
	.long	.Linfo_string92
	.long	0
	.byte	8
	.long	.Linfo_string90
	.byte	16
	.byte	8
	.byte	4
	.long	.Linfo_string85
	.long	2181
	.byte	8
	.byte	0
	.byte	4
	.long	.Linfo_string87
	.long	2197
	.byte	8
	.byte	8
	.byte	0
	.byte	45
	.long	2190
	.long	0
	.byte	36
	.long	.Linfo_string86
	.byte	0
	.byte	1
	.byte	5
	.long	2210
	.long	.Linfo_string89
	.long	0
	.byte	47
	.long	159
	.byte	48
	.long	2223
	.byte	0
	.byte	3
	.byte	0
	.byte	49
	.long	.Linfo_string88
	.byte	8
	.byte	7
	.byte	50
	.quad	.Lfunc_begin3
	.long	.Lfunc_end3-.Lfunc_begin3
	.byte	1
	.byte	87
	.long	1087
	.byte	51
	.byte	3
	.byte	145
	.asciz	"\330"
	.long	.Linfo_string48
	.byte	6
	.short	321
	.long	1919
	.byte	0
	.byte	7
	.long	.Linfo_string104
	.byte	52
	.quad	.Lfunc_begin9
	.long	.Lfunc_end9-.Lfunc_begin9
	.byte	1
	.byte	87
	.long	.Linfo_string124
	.long	.Linfo_string16
	.byte	9
	.byte	1

	.byte	0
	.byte	6
	.long	.Linfo_string110
	.byte	5
	.byte	8
	.byte	5
	.long	2317
	.long	.Linfo_string129
	.long	0
	.byte	5
	.long	1850
	.long	.Linfo_string128
	.long	0
	.byte	5
	.long	181
	.long	.Linfo_string131
	.long	0
	.byte	0
.Ldebug_info_end0:
	.section	.data.rel.ro..L__unnamed_1,"aw",@progbits
.Lsec_end0:
	.section	.text._ZN3std10sys_common9backtrace28__rust_begin_short_backtrace17hbbb535049446789dE,"ax",@progbits
.Lsec_end1:
	.section	.text._ZN3std2rt10lang_start17h459ab148060cdfb6E,"ax",@progbits
.Lsec_end2:
	.section	".text._ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h59b2a4c65a5ce27aE","ax",@progbits
.Lsec_end3:
	.section	.text._ZN4core3fmt9Arguments9new_const17hb3c5b26150c6cd24E,"ax",@progbits
.Lsec_end4:
	.section	".text._ZN4core3ops8function6FnOnce40call_once$u7b$$u7b$vtable.shim$u7d$$u7d$17h0d12a47bdff8cb5fE","ax",@progbits
.Lsec_end5:
	.section	.text._ZN4core3ops8function6FnOnce9call_once17h6582b4174c52c6ebE,"ax",@progbits
.Lsec_end6:
	.section	.text._ZN4core3ops8function6FnOnce9call_once17h83681d2563d97d84E,"ax",@progbits
.Lsec_end7:
	.section	".text._ZN4core3ptr85drop_in_place$LT$std..rt..lang_start$LT$$LP$$RP$$GT$..$u7b$$u7b$closure$u7d$$u7d$$GT$17he833ba5414404f82E","ax",@progbits
.Lsec_end8:
	.section	".text._ZN54_$LT$$LP$$RP$$u20$as$u20$std..process..Termination$GT$6report17ha69a6472a92175f8E","ax",@progbits
.Lsec_end9:
	.section	.text._ZN11hello_world4main17h842f481536ab1aa2E,"ax",@progbits
.Lsec_end10:
	.section	.debug_aranges,"",@progbits
	.long	204
	.short	2
	.long	.Lcu_begin0
	.byte	8
	.byte	0
	.zero	4,255
	.quad	.L__unnamed_1
	.quad	.Lsec_end0-.L__unnamed_1
	.quad	.Lfunc_begin0
	.quad	.Lsec_end1-.Lfunc_begin0
	.quad	.Lfunc_begin1
	.quad	.Lsec_end2-.Lfunc_begin1
	.quad	.Lfunc_begin2
	.quad	.Lsec_end3-.Lfunc_begin2
	.quad	.Lfunc_begin3
	.quad	.Lsec_end4-.Lfunc_begin3
	.quad	.Lfunc_begin4
	.quad	.Lsec_end5-.Lfunc_begin4
	.quad	.Lfunc_begin5
	.quad	.Lsec_end6-.Lfunc_begin5
	.quad	.Lfunc_begin6
	.quad	.Lsec_end7-.Lfunc_begin6
	.quad	.Lfunc_begin7
	.quad	.Lsec_end8-.Lfunc_begin7
	.quad	.Lfunc_begin8
	.quad	.Lsec_end9-.Lfunc_begin8
	.quad	.Lfunc_begin9
	.quad	.Lsec_end10-.Lfunc_begin9
	.quad	0
	.quad	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.quad	.Ltmp0
	.quad	.Ltmp1
	.quad	.Ltmp2
	.quad	.Ltmp3
	.quad	0
	.quad	0
.Ldebug_ranges1:
	.quad	.Ltmp0
	.quad	.Ltmp1
	.quad	.Ltmp2
	.quad	.Ltmp3
	.quad	0
	.quad	0
.Ldebug_ranges2:
	.quad	.Ltmp0
	.quad	.Ltmp1
	.quad	.Ltmp2
	.quad	.Ltmp3
	.quad	0
	.quad	0
.Ldebug_ranges3:
	.quad	.Lfunc_begin0
	.quad	.Lfunc_end0
	.quad	.Lfunc_begin1
	.quad	.Lfunc_end1
	.quad	.Lfunc_begin2
	.quad	.Lfunc_end2
	.quad	.Lfunc_begin3
	.quad	.Lfunc_end3
	.quad	.Lfunc_begin4
	.quad	.Lfunc_end4
	.quad	.Lfunc_begin5
	.quad	.Lfunc_end5
	.quad	.Lfunc_begin6
	.quad	.Lfunc_end6
	.quad	.Lfunc_begin7
	.quad	.Lfunc_end7
	.quad	.Lfunc_begin8
	.quad	.Lfunc_end8
	.quad	.Lfunc_begin9
	.quad	.Lfunc_end9
	.quad	0
	.quad	0
	.section	.debug_str,"MS",@progbits,1
.Linfo_string0:
	.asciz	"clang LLVM (rustc version 1.77.0-nightly (e51e98dde 2023-12-31))"
.Linfo_string1:
	.asciz	"src/main.rs/@/2avma1vvoc4c81oj"
.Linfo_string2:
	.asciz	"/home/amadeusw/university/master1/compilers/mini-rust-compiler/test/hello_world"
.Linfo_string3:
	.asciz	"<std::rt::lang_start::{closure_env#0}<()> as core::ops::function::Fn<()>>::{vtable}"
.Linfo_string4:
	.asciz	"drop_in_place"
.Linfo_string5:
	.asciz	"()"
.Linfo_string6:
	.asciz	"*const ()"
.Linfo_string7:
	.asciz	"size"
.Linfo_string8:
	.asciz	"usize"
.Linfo_string9:
	.asciz	"align"
.Linfo_string10:
	.asciz	"__method3"
.Linfo_string11:
	.asciz	"__method4"
.Linfo_string12:
	.asciz	"__method5"
.Linfo_string13:
	.asciz	"std"
.Linfo_string14:
	.asciz	"rt"
.Linfo_string15:
	.asciz	"lang_start"
.Linfo_string16:
	.asciz	"main"
.Linfo_string17:
	.asciz	"fn()"
.Linfo_string18:
	.asciz	"{closure_env#0}<()>"
.Linfo_string19:
	.asciz	"<std::rt::lang_start::{closure_env#0}<()> as core::ops::function::Fn<()>>::{vtable_type}"
.Linfo_string20:
	.asciz	"core"
.Linfo_string21:
	.asciz	"fmt"
.Linfo_string22:
	.asciz	"u8"
.Linfo_string23:
	.asciz	"Left"
.Linfo_string24:
	.asciz	"Right"
.Linfo_string25:
	.asciz	"Center"
.Linfo_string26:
	.asciz	"Unknown"
.Linfo_string27:
	.asciz	"Alignment"
.Linfo_string28:
	.asciz	"hint"
.Linfo_string29:
	.asciz	"T"
.Linfo_string30:
	.asciz	"_ZN4core4hint9black_box17h39491ddb69ec399bE"
.Linfo_string31:
	.asciz	"black_box<()>"
.Linfo_string32:
	.asciz	"dummy"
.Linfo_string33:
	.asciz	"sys_common"
.Linfo_string34:
	.asciz	"backtrace"
.Linfo_string35:
	.asciz	"process"
.Linfo_string36:
	.asciz	"__0"
.Linfo_string37:
	.asciz	"sys"
.Linfo_string38:
	.asciz	"unix"
.Linfo_string39:
	.asciz	"process_common"
.Linfo_string40:
	.asciz	"ExitCode"
.Linfo_string41:
	.asciz	"_ZN3std7process8ExitCode6to_i3217hc7d2c04b20416c1aE"
.Linfo_string42:
	.asciz	"to_i32"
.Linfo_string43:
	.asciz	"i32"
.Linfo_string44:
	.asciz	"self"
.Linfo_string45:
	.asciz	"_ZN3std3sys4unix7process14process_common8ExitCode6as_i3217h16f6aeba7eb04242E"
.Linfo_string46:
	.asciz	"as_i32"
.Linfo_string47:
	.asciz	"&std::sys::unix::process::process_common::ExitCode"
.Linfo_string48:
	.asciz	"pieces"
.Linfo_string49:
	.asciz	"data_ptr"
.Linfo_string50:
	.asciz	"length"
.Linfo_string51:
	.asciz	"&str"
.Linfo_string52:
	.asciz	"&[&str]"
.Linfo_string53:
	.asciz	"option"
.Linfo_string54:
	.asciz	"u64"
.Linfo_string55:
	.asciz	"None"
.Linfo_string56:
	.asciz	"position"
.Linfo_string57:
	.asciz	"fill"
.Linfo_string58:
	.asciz	"char"
.Linfo_string59:
	.asciz	"flags"
.Linfo_string60:
	.asciz	"u32"
.Linfo_string61:
	.asciz	"precision"
.Linfo_string62:
	.asciz	"Is"
.Linfo_string63:
	.asciz	"Param"
.Linfo_string64:
	.asciz	"Implied"
.Linfo_string65:
	.asciz	"Count"
.Linfo_string66:
	.asciz	"width"
.Linfo_string67:
	.asciz	"Placeholder"
.Linfo_string68:
	.asciz	"&[core::fmt::rt::Placeholder]"
.Linfo_string69:
	.asciz	"Some"
.Linfo_string70:
	.asciz	"Option<&[core::fmt::rt::Placeholder]>"
.Linfo_string71:
	.asciz	"args"
.Linfo_string72:
	.asciz	"value"
.Linfo_string73:
	.asciz	"{extern#0}"
.Linfo_string74:
	.asciz	"Opaque"
.Linfo_string75:
	.asciz	"&core::fmt::rt::{extern#0}::Opaque"
.Linfo_string76:
	.asciz	"formatter"
.Linfo_string77:
	.asciz	"result"
.Linfo_string78:
	.asciz	"Ok"
.Linfo_string79:
	.asciz	"Error"
.Linfo_string80:
	.asciz	"E"
.Linfo_string81:
	.asciz	"Err"
.Linfo_string82:
	.asciz	"Result<(), core::fmt::Error>"
.Linfo_string83:
	.asciz	"Option<usize>"
.Linfo_string84:
	.asciz	"buf"
.Linfo_string85:
	.asciz	"pointer"
.Linfo_string86:
	.asciz	"dyn core::fmt::Write"
.Linfo_string87:
	.asciz	"vtable"
.Linfo_string88:
	.asciz	"__ARRAY_SIZE_TYPE__"
.Linfo_string89:
	.asciz	"&[usize; 3]"
.Linfo_string90:
	.asciz	"&mut dyn core::fmt::Write"
.Linfo_string91:
	.asciz	"Formatter"
.Linfo_string92:
	.asciz	"&mut core::fmt::Formatter"
.Linfo_string93:
	.asciz	"fn(&core::fmt::rt::{extern#0}::Opaque, &mut core::fmt::Formatter) -> core::result::Result<(), core::fmt::Error>"
.Linfo_string94:
	.asciz	"Argument"
.Linfo_string95:
	.asciz	"&[core::fmt::rt::Argument]"
.Linfo_string96:
	.asciz	"Arguments"
.Linfo_string97:
	.asciz	"_ZN4core3fmt9Arguments9new_const17hb3c5b26150c6cd24E"
.Linfo_string98:
	.asciz	"new_const"
.Linfo_string99:
	.asciz	"ops"
.Linfo_string100:
	.asciz	"function"
.Linfo_string101:
	.asciz	"FnOnce"
.Linfo_string102:
	.asciz	"ptr"
.Linfo_string103:
	.asciz	"{impl#57}"
.Linfo_string104:
	.asciz	"hello_world"
.Linfo_string105:
	.asciz	"F"
.Linfo_string106:
	.asciz	"_ZN3std10sys_common9backtrace28__rust_begin_short_backtrace17hbbb535049446789dE"
.Linfo_string107:
	.asciz	"__rust_begin_short_backtrace<fn(), ()>"
.Linfo_string108:
	.asciz	"_ZN3std2rt10lang_start17h459ab148060cdfb6E"
.Linfo_string109:
	.asciz	"lang_start<()>"
.Linfo_string110:
	.asciz	"isize"
.Linfo_string111:
	.asciz	"_ZN3std2rt10lang_start28_$u7b$$u7b$closure$u7d$$u7d$17h59b2a4c65a5ce27aE"
.Linfo_string112:
	.asciz	"{closure#0}<()>"
.Linfo_string113:
	.asciz	"Self"
.Linfo_string114:
	.asciz	"Args"
.Linfo_string115:
	.asciz	"_ZN4core3ops8function6FnOnce40call_once$u7b$$u7b$vtable.shim$u7d$$u7d$17h0d12a47bdff8cb5fE"
.Linfo_string116:
	.asciz	"call_once<std::rt::lang_start::{closure_env#0}<()>, ()>"
.Linfo_string117:
	.asciz	"_ZN4core3ops8function6FnOnce9call_once17h6582b4174c52c6ebE"
.Linfo_string118:
	.asciz	"call_once<fn(), ()>"
.Linfo_string119:
	.asciz	"_ZN4core3ops8function6FnOnce9call_once17h83681d2563d97d84E"
.Linfo_string120:
	.asciz	"_ZN4core3ptr85drop_in_place$LT$std..rt..lang_start$LT$$LP$$RP$$GT$..$u7b$$u7b$closure$u7d$$u7d$$GT$17he833ba5414404f82E"
.Linfo_string121:
	.asciz	"drop_in_place<std::rt::lang_start::{closure_env#0}<()>>"
.Linfo_string122:
	.asciz	"_ZN54_$LT$$LP$$RP$$u20$as$u20$std..process..Termination$GT$6report17ha69a6472a92175f8E"
.Linfo_string123:
	.asciz	"report"
.Linfo_string124:
	.asciz	"_ZN11hello_world4main17h842f481536ab1aa2E"
.Linfo_string125:
	.asciz	"f"
.Linfo_string126:
	.asciz	"argc"
.Linfo_string127:
	.asciz	"argv"
.Linfo_string128:
	.asciz	"*const u8"
.Linfo_string129:
	.asciz	"*const *const u8"
.Linfo_string130:
	.asciz	"sigpipe"
.Linfo_string131:
	.asciz	"*mut std::rt::lang_start::{closure_env#0}<()>"
	.hidden	DW.ref.rust_eh_personality
	.weak	DW.ref.rust_eh_personality
	.section	.data.DW.ref.rust_eh_personality,"aGw",@progbits,DW.ref.rust_eh_personality,comdat
	.p2align	3, 0x0
	.type	DW.ref.rust_eh_personality,@object
	.size	DW.ref.rust_eh_personality, 8
DW.ref.rust_eh_personality:
	.quad	rust_eh_personality
	.ident	"rustc version 1.77.0-nightly (e51e98dde 2023-12-31)"
	.section	".note.GNU-stack","",@progbits
	.section	.debug_line,"",@progbits
.Lline_table_start0:
