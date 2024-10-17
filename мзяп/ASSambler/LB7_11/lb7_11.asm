*Условия
  MVK -4, A1	;R1
  MVK 228, A2	;R2
  MVK 9, B0		;Счётчик проходов
  MVK 2, A6		;h1
  MVK 28, A7	;h2
  
m:
  ADDK -1, B0
  STW A1, *A2
  LDB *A2--[A7], A3
  NOP 4
  [B0] B m
  [B0] ADD A1, A6, A1
  NOP 4