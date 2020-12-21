#include <exception>
#include <iostream>

#include "Application.h"

int main() {
  try {
    Application application;
    application.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
