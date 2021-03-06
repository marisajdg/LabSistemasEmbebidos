@ add.s
@ Marisa Diaz

@ ---------------------------------------
@   Data Section
@ ---------------------------------------
.data
.balign 4

string1: .asciz "\nGive me the first operand: "
string2: .asciz "\nGive me the second operand: "
string3: .asciz "\nThe result of %d + %d is: %d\n"

format: .asciz "%d"

c:	.int 0
a:  .int 33
b:	.int 44
	
@ ---------------------------------------
@   Code Section
@ ---------------------------------------
.text
.global main
.extern printf
.extern scanf

main:
        push {ip, lr}
        ldr  r0, =string1
        bl   printf
        
        ldr r0, =format
        ldr r1, =a
        bl scanf
        
        ldr  r0, =string2
        bl   printf
        
        ldr r0, =format
        ldr r1, =b
        bl scanf
        
        ldr r1, =a
        ldr r1, [r1]
        ldr r2, =b
        ldr r2, [r2]
        add r1, r1, r2 
        ldr r2, =c
        str r1, [r2] 
        
        ldr  r0, =string3
        ldr	r1, =a           
        ldr	r1, [r1]
        ldr	r2, =b           
        ldr	r2, [r2]
        ldr	r3, =c          
        ldr	r3, [r3] 
        bl   printf
        
        pop  {ip, pc}
