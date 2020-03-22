
start	
Add R4 		, 3002D


Mov	r1, R4 			 		 
CMP r1,r4 			
l1:jmp	l2		

hlt 	
L2	: Sub r1 ,r4
mul 0003H
mul 2787D
mul  0101B

mul r3
Loop L1
And r1, 0005H
Or r12 , 0101011101B		
nOT 	r21	
	jnz L2
	
loop3 :	
	
		Or r23,r30	
		loop4 :
end


