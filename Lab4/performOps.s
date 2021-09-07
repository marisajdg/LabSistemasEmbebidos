@ performOps.s
@ Marisa Diaz

@ ---------------------------------------
@   Data Section
@ ---------------------------------------

.data
.balign 4

string1: .asciz "\nGive me the first operand: "
string2: .asciz "\nGive me the second operand: "
string3: .asciz "\n%d %c %d "
string4: .asciz "\nGive me the operation: "
string5: .asciz "\nGive me the third operand: "
format: .asciz "%d"
output: .asciz  "%c %d = %d\n"
sign: .asciz " %c"


a:  .int 0
b:	.int 0
c:  .int 0
d:	.int 0
s:  .word 44
s2: .word 55

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

        ldr r0, =string4
        bl printf
        
        ldr r0, =sign 
        ldr r1, =s
        bl scanf
        
        ldr  r0, =string2
        bl   printf
        
        ldr r0, =format
        ldr r1, =b
        bl scanf
        
        ldr r0, =string4
        bl printf
        
        ldr r0, =sign 
        ldr r1, =s2
        bl scanf
        
        ldr  r0, =string5
        bl   printf
        
        ldr r0, =format
        ldr r1, =c
        bl scanf
        
        ldr r1, =a
        ldr r1, [r1]
        
        ldr r2, =b
        ldr r2, [r2]
        
        ldr r3, =s
        ldr r3, [r3]
        
        ldr r4, =c
        ldr r4, [r4]
        
        ldr r5, =s2
        ldr r5, [r5]       
        
        
        cmp r3,#43 @if char == +
        beq addition
        cmp r3,#45 @if char == -
        beq subtraction
        cmp r3,#42 @if char == *
        beq mult
        cmp r3,#47 @if char == /
        beq division
        
    addition: 
        add r3, r1, r2  
        ldr r6, =d
        str r3, [r6]
        b next
    subtraction: 
        sub r3, r1, r2  
        ldr r6, =d
        str r3, [r6]
        b next
    mult: 
        mul r3, r1, r2  
        ldr r6, =d
        str r3, [r6]
        b next
    division: 
        sdiv r3, r1, r2  
        ldr r6, =d
        str r3, [r6]
        b next
        
    next:
        cmp r5,#43 @if char == +
        beq addition2
        cmp r5,#45 @if char == -
        beq subtraction2
        cmp r5,#42 @if char == *
        beq mult2
        cmp r5,#47 @if char == /
        beq division2
        
    addition2:
        ldr r6, =d
        ldr r6, [r6]
        add r3, r6, r4 
        ldr r4, =d
        str r3, [r4]
        b prints
    subtraction2: 
        ldr r6, =d
        ldr r6, [r6]
        sub r3, r6, r4  
        ldr r4, =d
        str r3, [r4]
        b prints
    mult2:
        ldr r6, =d
        ldr r6, [r6]
        mul r3, r6, r4  
        ldr r4, =d
        str r3, [r4]
        b prints
    division2:
        ldr r6, =d
        ldr r6, [r6]
        sdiv r3, r6, r4 
        ldr r4, =d
        str r3, [r4]
        b prints
        
    prints:        
        ldr r1, =a          
        ldr r1, [r1]
        ldr r2, =s			 
        ldr r2, [r2]
        ldr r3, =b           
        ldr r3, [r3]
        ldr r0, =string3 
        bl printf
        
        ldr r0,=output
        ldr r1, =s2        
        ldr r1, [r1]
        ldr r2, =c        
        ldr r2, [r2]
        ldr r3, =d           
        ldr r3, [r3]
        bl printf
        
        pop  {ip, pc}
