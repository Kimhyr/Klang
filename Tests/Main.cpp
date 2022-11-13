#include <iostream>

struct Token {
  enum Flag {
   Error = 0x01,
   EoF = 0x02
  };
};

int main() {
  unsigned char flags = 0;
  flags |= Token::Flag::Error;
  std::cout << (Token::Flag)flags << '\n';
  return 0;
}
