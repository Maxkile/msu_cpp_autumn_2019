 #include "ThreadPool.hpp"
 #include <iostream>

int main(int argc, char const *argv[])
 {
   ThreadPool pool(8);
      
   int a = 141219;
   auto task1 = [a](int c) { return a*c; };
  
   auto res = pool.exec(task1,2);

   std::cout << res.get() << std::endl;
    
   int b = 912141;
    
    
   auto task2 = [a,b]() { return a + b; };
    
   res = pool.exec(task2);

   std::cout << res.get() << std::endl;
   return 0;
 }
 
