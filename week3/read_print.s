# RISC-V system calls example
# This program reads and prints an integer

.data
prompt:     .asciiz "Enter an integer: "
result_msg: .asciiz "The result is: "

.text
.globl _start

# Syscall numbers
SYS_READ_INT = 5
SYS_PRINT_INT = 1
SYS_EXIT = 10

_start:
    # Print the prompt
    li   a0, SYS_PRINT_INT
    la   a1, prompt
    li   a2, 18  # Length of the prompt string
    ecall

    # Read an integer from the user
    li   a0, SYS_READ_INT
    li   a2, 10  # Maximum number of digits for input
    ecall

    # Multiply the input integer by 2
    lw   t0, 0(a1)  # Load the integer from the buffer
    slli t0, t0, 1  # Multiply by 2

    # Print the result
    li   a0, SYS_PRINT_INT
    la   a1, result_msg
    li   a2, 15  # Length of the result message string
    ecall

    # Print the multiplied result
    li   a0, SYS_PRINT_INT
    mv   a1, t0   # Move the result to a1
    ecall

    # Exit the program
    li   a0, SYS_EXIT
    ecall
