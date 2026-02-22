        .text
        .globl main

main:   li      $t0, -4

        addiu   $a0, $t0, 0

        li      $v0, 1
        syscall

        li      $v0, 10
        syscall
