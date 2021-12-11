#include <shared_ptr.hpp>
#include <iostream>

class Demo {
public:
  int demo;
  Demo(): demo(0) 
  {
  }
};

int main() {
  Demo* ref1 = new Demo;
  Demo* ref2 = new Demo;
  SharedPtr<Demo> ptr1(ref1);
  SharedPtr<Demo> ptr2(ref2);
  SharedPtr<Demo> ptr3(ptr1);
  SharedPtr<Demo> ptr4;
  std::cout << ptr1.use_count() << std::endl;
  std::cout << ptr2.use_count() << std::endl;
  ptr2 = ptr1;
  std::cout << ptr2.use_count() << std::endl;
  ptr4 = ptr2;
  
  std::cout << ptr2.use_count() << std::endl;
}