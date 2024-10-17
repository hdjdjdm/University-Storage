*Операция 1
  MVK 0xC6A0, A1
  MVKLH 0x00E4, A1
  
*Операция 2
  MVK 0x50, A2
  
*Операция 3
  STW A1, *+A2[1]
  
*Операция 4
  LDHU *++A2[2], A3
  NOP 4
  
*Операция 5
  MV A3, A1