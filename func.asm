section .data
    c1 dd 1.0
    c2 dd 2.0
    c3 dd 3.0
    c4 dd 5.0
    c5 dd -8.0
section .text
       
global f1
f1:
    push ebp
    mov ebp,esp
    finit
    fldl2e      
    fld dword[ebp+8]
    fmulp  
    fld1
    fldl2e      
    fld dword[ebp+8]
    fmulp   
    fprem   
    fsub st2, st0
    f2xm1  
    faddp 
    fscale
    fld dword[c2]
    faddp     
    leave
    ret
    
global f2
f2:
    push ebp
    mov ebp,esp
    finit
    fld dword[ebp+8]
    fld dword[c2]
    fmulp
    fld dword[c5]
    faddp
    fchs
    leave
    ret
global f3
f3:
    push ebp
    mov ebp,esp
    finit
    fld dword[c4]
    fld dword[ebp+8]  
    fdivp
    fchs
    leave
    ret   
    
