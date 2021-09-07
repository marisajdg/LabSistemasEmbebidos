@ performOp.s
@ Marisa Diaz

@ ---------------------------------------
@   Data Section
@ ---------------------------------------
.data
.balign 4

string1: .asciz "\nGive me the first operand: "
string2: .asciz "\nGive me the operation to be performed (+, -, *, /): "
string3: .asciz "\nGive me the second operand: "
string4: .asciz "\nThe result of %d + %d is: %d\n"

format: .asciz "%d"
output: .asciz  "%d\n"
sign: .asciz " %c"


a:  .int 22
b:	.int 33
s:  .word 44
c:	.int 0

@ ---------------------------------------
@   Code Section
@ ---------------------------------------
.text
.global main
.extern printf
.extern scanf

main:
        push {ip, lr}
        
        @ Get inputs
        ldr  r0, =string1
        bl   printf
        
        ldr r0, =format
        ldr r1, =a
        bl scanf

        ldr r0, =string2
        bl printf
        
        ldr r0, =sign 
        ldr r1, =s
        bl scanf
        
        ldr  r0, =string3
        bl   printf
        
        ldr r0, =format
        ldr r1, =b
        bl scanf
        
        @ Load inputs to regs
        ldr r1, =a
        ldr r1, [r1]
        
        ldr r2, =b
        ldr r2, [r2]
        
        ldr r3, =s
        ldr r3, [r3]       
  
        @ Compare operation and branch to subroutine
        cmp r3,#43 @if char == +
        beq addition
        cmp r3,#45 @if char == -
        beq substraction
        cmp r3,#42 @if char == *
        beq mult
        cmp r3,#47 @if char == /
        beq division
        
    addition: 
        add r3, r1, r2  
        ldr r4, =c
        str r3, [r4]
        b print
    substraction: 
        sub r3, r1, r2  
        ldr r4, =c
        str r3, [r4]
        b print
    mult: 
        mul r3, r1, r2  
        ldr r4, =c
        str r3, [r4]
        b print
    division: 
        sdiv r3, r1, r2  
        ldr r4, =c
        str r3, [r4]
        b print
    print:       
        ldr	r1, =a           
        ldr	r1, [r1]
        ldr r2, =s			
        ldr r2, [r2]
        ldr	r3, =b          
        ldr	r3, [r3]
        ldr  r0, =string3 
        bl   printf
        ldr r0,=output
        ldr	r1, =c           
        ldr	r1, [r1]
        bl printf

        pop  {ip, pc}
