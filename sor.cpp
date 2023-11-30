// sort algorithm example: three types.
// from https://cplusplus.com/reference/algorithm/sort/
// // actually this is a bit unfair .. using an object which only has a function!
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector

bool cmpfunc (int i,int j)
{
    return (i<j);
}

struct myclass
{
  bool operator() (int i,int j) {
      return (i<j);
  }
} myobject;

int main ()
{
  int myints[] = {32,71,12,45,26,80,53,33};
  // std::cout << myints << "\n"; // just gives pointer.

  std::vector<int> myvector (myints, myints+8); // 32 71 12 45 26 80 53 33 ... i think the +8 is the end.
  // std::cout << myvector << "\n"; // doesn't work to save its life.

  // using default comparison (operator <):
  std::sort (myvector.begin(), myvector.begin()+4);           //(12 32 45 71)26 80 53 33

  // using function as comp
  std::sort (myvector.begin()+4, myvector.end(), cmpfunc); // 12 32 45 71(26 33 53 80)

  // using object as comp
  std::sort (myvector.begin(), myvector.end(), myobject);     //(12 26 32 33 45 53 71 80)

  // print out content:
  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
