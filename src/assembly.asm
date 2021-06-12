.section .text
.global calculate_temperature
calculate_temperature:
.LCPI0_0:
        .quad   0x4071126666666666              # double 273.14999999999998
.LCPI0_1:
        .quad   0x3ff0000000000000              # double 1
.LCPI0_2:
        .quad   0x3e7788eb14170d19              # double 8.76741E-8
.LCPI0_3:
        .quad   0x3f527ffd6edeb890              # double 0.001129148
.LCPI0_4:
        .quad   0x3f2eafee6fb4c3c2              # double 2.3412500000000001E-4
.LCPI0_5:
        .quad   0x40c3880000000000              # double 1.0E+4
.LCPI0_6:
        .quad   0x40e01d0000000000              # double 33000
.LCPI0_7:
        .quad   0x408ff80000000000              # double 1023
.LCPI0_8:
        .quad   0x400a666666666666              # double 3.2999999999999998
square(double):                             # @square(double)
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $96, %rsp
        movsd   %xmm0, -8(%rbp)
        movsd   .LCPI0_8(%rip), %xmm0           # xmm0 = mem[0],zero
        movsd   %xmm0, -16(%rbp)
        movsd   .LCPI0_5(%rip), %xmm0           # xmm0 = mem[0],zero
        movsd   %xmm0, -24(%rbp)
        movsd   .LCPI0_7(%rip), %xmm0           # xmm0 = mem[0],zero
        movsd   %xmm0, -32(%rbp)
        movsd   .LCPI0_3(%rip), %xmm0           # xmm0 = mem[0],zero
        movsd   %xmm0, -40(%rbp)
        movsd   .LCPI0_4(%rip), %xmm0           # xmm0 = mem[0],zero
        movsd   %xmm0, -48(%rbp)
        movsd   .LCPI0_2(%rip), %xmm0           # xmm0 = mem[0],zero
        movsd   %xmm0, -56(%rbp)
        movsd   .LCPI0_8(%rip), %xmm0           # xmm0 = mem[0],zero
        mulsd   -8(%rbp), %xmm0
        movsd   .LCPI0_7(%rip), %xmm1           # xmm1 = mem[0],zero
        divsd   %xmm1, %xmm0
        movsd   %xmm0, -64(%rbp)
        movsd   .LCPI0_6(%rip), %xmm0           # xmm0 = mem[0],zero
        divsd   -64(%rbp), %xmm0
        movsd   .LCPI0_5(%rip), %xmm1           # xmm1 = mem[0],zero
        subsd   %xmm1, %xmm0
        movsd   %xmm0, -72(%rbp)
        movsd   -72(%rbp), %xmm0                # xmm0 = mem[0],zero
        callq   log
        movsd   .LCPI0_4(%rip), %xmm1           # xmm1 = mem[0],zero
        mulsd   %xmm0, %xmm1
        movsd   .LCPI0_3(%rip), %xmm0           # xmm0 = mem[0],zero
        addsd   %xmm1, %xmm0
        movsd   %xmm0, -88(%rbp)                # 8-byte Spill
        movsd   -72(%rbp), %xmm0                # xmm0 = mem[0],zero
        callq   log
        movl    $3, %edi
        callq   __gnu_cxx::__promote_2<double, int, __gnu_cxx::__promote<double, std::__is_integer<double>::__value>::__type, __gnu_cxx::__promote<int, std::__is_integer<int>::__value>::__type>::__type std::pow<double, int>(double, int)
        movsd   -88(%rbp), %xmm1                # 8-byte Reload
        movaps  %xmm0, %xmm2
        movsd   .LCPI0_2(%rip), %xmm0           # xmm0 = mem[0],zero
        mulsd   %xmm2, %xmm0
        addsd   %xmm0, %xmm1
        movsd   .LCPI0_1(%rip), %xmm0           # xmm0 = mem[0],zero
        divsd   %xmm1, %xmm0
        movsd   %xmm0, -80(%rbp)
        movsd   -80(%rbp), %xmm0                # xmm0 = mem[0],zero
        movsd   .LCPI0_0(%rip), %xmm1           # xmm1 = mem[0],zero
        subsd   %xmm1, %xmm0
        movsd   %xmm0, -80(%rbp)
        cvttsd2si       -80(%rbp), %eax
        addq    $96, %rsp
        popq    %rbp
        retq