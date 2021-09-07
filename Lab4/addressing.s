@ addressing.s
@ Marisa Diaz

@ ---------------------------------------
@   Data Section
@ ---------------------------------------
.data
.balign 4	
string1: .asciz "\nMemory location: %x\n"
string2: .asciz "\nContent: %x\n"
y:		.word 33
a:      .word 0xAAAAAAAA
b:      .word 0xBBBBBBBB
c:      .word 0xCCCCCCCC
	
@ ---------------------------------------
@   Code Section
@ ---------------------------------------
.text
.global main
.extern printf

main:
        push {ip, lr}
        
        @ Print initial values
        ldr  r0, =string2
        ldr  r1, =y 
        ldr  r1, [r1]   @ get y into r1
        bl   printf
        
        ldr  r0, =string1       @ get address of string2 into r0
        ldr  r1, =y     @ get address of y into r1
        bl   printf     @ print string2 and r1 as param

        @ Addressing mode reg0, [reg1]
        ldr  r2, =a 
        ldr  r2, [r2]
        ldr  r1, =y
        str  r2, [r1] @ store r2 into y
        
        @ Print values
        ldr  r0, =string2
        ldr  r1, =y 
        ldr  r1, [r1]   
        bl   printf

        ldr  r0, =string1      
        ldr  r1, =y     
        bl   printf     
        
        @ Addressing mode reg0, [reg1,#offset]
        ldr  r2, =b
        ldr  r2, [r2]
        ldr  r1,=y
        str  r2, [r1,#0]
        
        @ Print values
        ldr  r0, =string2
        ldr  r1, =y 
        ldr  r1, [r1]   
        bl   printf

        ldr  r0, =string1       
        ldr  r1, =y     
        bl   printf   
        
        @ Addressing mode reg0, [reg1], #numberToAdd
        ldr  r2, =c
        ldr  r2, [r2]
        ldr  r1,=y
        str  r2, [r1], #0
        
        @ Print values
        ldr  r0, =string2
        ldr  r1, =y 
        ldr  r1, [r1]   
        bl   printf

        ldr  r0, =string1       
        ldr  r1, =y     
        bl   printf 
        
        pop  {ip, pc}
