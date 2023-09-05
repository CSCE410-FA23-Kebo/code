# RISC-V system calls example
# Fibonacci Sequence
# This program calculates and prints the Fibonacci sequence up to a specified number of terms.

.data
limit: .word 10  # Number of Fibonacci terms to calculate
fib:   .space 40 # Buffer to store Fibonacci sequence

.text
.globl _start

# Syscall numbers
SYS_PRINT_INT = 1
SYS_EXIT = 93

_start:
    # Load the limit (number of terms) from memory
    lw   a0, limit

    # Initialize Fibonacci sequence
    li   t0, 0  # First term (F(0))
    li   t1, 1  # Second term (F(1))
    sw   t0, fib   # Store the first term
    sw   t1, fib+4 # Store the second term

    # Print the first two terms
    li   a7, SYS_PRINT_INT
    lw   a0, fib   # Load the first term
    ecall
    li   a7, SYS_PRINT_INT
    lw   a0, fib+4 # Load the second term
    ecall

    # Calculate and print the remaining terms
    addi a0, a0, 2  # Initialize counter (starting from 2)
loop:
    # Calculate the next term in the sequence (F(n) = F(n-1) + F(n-2))
    lw   t2, fib+a0-4  # Load F(n-1)
    lw   t3, fib+a0-8  # Load F(n-2)
    add  t4, t2, t3    # Calculate F(n)
    sw   t4, fib+a0    # Store F(n)

    # Print the calculated term
    li   a7, SYS_PRINT_INT
    lw   a0, fib+a0   # Load F(n)
    ecall

    # Check if we've reached the limit
    lw   t5, limit
    bge  a0, t5, exit

    # Increment the counter
    addi a0, a0, 1
    j    loop

exit:
    # Exit the program
    li   a7, SYS_EXIT
    ecall
