#include <iostream>

int main() {
  int rows = 8;
  int cols = 8;

  for (int i = 0; i < rows; i++) {
    std::cout << 8 - i << ' ';
    for(int j = 0; j < cols; j++) {  
      std::cout << ". "; 
 
    }
    std::cout << "\n";
  }
  std::cout << "  a b c d e f g h\n";

  return 0;
}
