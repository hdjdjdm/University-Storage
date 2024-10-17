*Условия
  MVK -4, A0	;R1
  MVK 2, A1		;h
  MVK -4, A2	;Sum
  
m:
  CMPLT A2, 14, B0
  [B0] B m
  [B0] ADD A0, A1, A0
  [B0] ADD A2, A0, A2
  NOP 3