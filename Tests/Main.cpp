#include <iostream>

struct Token {
  enum Flag {
   Error = 0x01,
   EoF = 0x02
  };
};