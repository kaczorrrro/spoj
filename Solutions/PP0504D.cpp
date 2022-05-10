// PP0504D - Reprezentacja liczb typu float
#include <iostream>
#include <cstring>

void printfloat(float f) {
  uint8_t bytes [sizeof(float)];
  memcpy(bytes, &f, sizeof(float));
  // X86 uses little endian, we need to swap the order to match print spec
  std::cout << +bytes[3] << " " << +bytes[2] << " " << +bytes[1] << " " << +bytes[0] << std::endl;
}

int main() {
  {int n; std::cin >> n;}
  std::cout << std::hex;
  float f;
  while (std::cin >> f) {
    printfloat(f);
  }
}
