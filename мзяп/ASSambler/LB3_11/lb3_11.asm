*Операция 1
  MVK 0xA000, B1
  MVKLH 0x7100, B1
  MVK 0xC000, B0
  MVKLH 0x8100, B0
  MPYHU B1, B0, B2
  NOP

*Операция 2
  ABS B2, B3
  
*Операция 3
  ADDK 0x1, B3