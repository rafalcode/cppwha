//  std::ostringstream stringStream;
//   stringStream << "Hello";
//   std::string copyOfStr = stringStream.str();
// swapping ostringstream objects
// // seeming a way to also assign variables using stringstream
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

using namespace std;

int main(void)
{
  stringstream ss;

  int foo, bar;
  ss << 100 << ' ' << 200;
  ss >> foo >> bar;

  cout << "foo: " << foo << '\n';
  cout << "bar: " << bar << '\n';

  return 0;
}
