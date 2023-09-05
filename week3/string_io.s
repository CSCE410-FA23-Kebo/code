# RISC-V system calls example
# This program opens a file, writes a string to the file, closes the file, 
# It reads and prints the content of the file.

.data
filename:  .asciiz "example.txt"
text:      .asciiz "Hello, RISC-V Assembly!\n"
buffer:    .space  256

.text
.globl _start

# Syscall numbers
SYS_OPEN = 1024
SYS_CLOSE = 57
SYS_READ = 63
SYS_WRITE = 64
SYS_EXIT = 93

_start:
    # Open the file for writing (create if not exists)
    li   a0, SYS_OPEN
    la   a1, filename
    li   a2, 2     # O_WRONLY | O_CREAT
    li   a3, 0644  # File permissions
    ecall

    # Check if the file descriptor is valid (negative value on error)
    blt  a0, zero, exit

    # Write the string to the file
    li   a0, SYS_WRITE
    mv   a1, a0   # File descriptor (stdout)
    la   a2, text
    li   a3, 22   # Length of the text
    ecall

    # Close the file
    li   a0, SYS_CLOSE
    ecall

    # Open the file for reading
    li   a0, SYS_OPEN
    la   a1, filename
    li   a2, 0     # O_RDONLY
    li   a3, 0     # No file permissions needed
    ecall

    # Check if the file descriptor is valid
    blt  a0, zero, exit

    # Read and print the content of the file
    li   a0, SYS_READ
    mv   a1, a0   # File descriptor (stdin)
    la   a2, buffer
    li   a3, 256  # Maximum number of bytes to read
    ecall

    # Print the read content
    li   a0, SYS_WRITE
    mv   a1, a0   # File descriptor (stdout)
    mv   a2, buffer
    a3   a3, a0   # Number of bytes read
    ecall

exit:
    # Exit the program
    li   a0, SYS_EXIT
    ecall
