*Условия
  MVK 92, A9   ; m2m1
  MVK 192, A8  ; 1m2m1

  MVK 7, A7  ; разница между порядками
  
m:
  CMPGT A7, 0, B0
  
  [B0] LDW *A9, A0 
  [B0] LDW *+A9[A7], A1
  NOP 4
  [B0] OR A0, A1, A2

  [B0] STW A2, *A8++[1]

  [B0] ADDK -2, A7
  [B0] ADDK +4, A9

  [B0] B m
  NOP 5