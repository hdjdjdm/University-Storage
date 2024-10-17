*Исходное число
  MVK 0xC6A0, A4
  MVKLH 0x00E4, A4
  
*1 Условие
  MV A9, A10
  CMPEQ 0, A10, A1
  [A1] B operation1
  [!A1] B comanda2
  NOP 5
  
*2 Условие
comanda2:
  EXT A8, 0, 27, A2
  CMPEQ A2, 0, A2
  [A2] B operation2
  [!A2] B operation3
  NOP 5

*Операция 1
operation1:
  ABS A4, A5
  B end
  NOP 5

*Операция 2
operation2:
  SET A4, 0, 16, A5
  B end
  NOP 5
  
*Операция 3
operation3:
  MV A4, B4
  B end
  NOP 5
  
end:
  NOP