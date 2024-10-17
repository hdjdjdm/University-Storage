*Условия
  CMPLT A8, 0, B0	;1 условие
  MVK 1, A1
  XOR B0, A1, B1
  CMPEQ A8, A9, A0	;2 условие
  AND B1, A0, B2
  
  [B2] B operation1
  [!B2] B operation2_3
  NOP 5

*Операция 1
operation1:
  MVK 0xC7A6, A1
  MVKLH 0x000E, A1
  ABS A1, A2
  B end
  NOP 5
  
operation2_3:
*Операция 2
  MVK 0x8600, B1
  MVKLH 0x4C5A, B1
  MVK 0x5D03, B2
  MVKLH 0x78B0, B2
  ADD B1, B2, B3
  
*Операция 3
  ABS B3, B4
  B end
  NOP 5
  
end:
  NOP