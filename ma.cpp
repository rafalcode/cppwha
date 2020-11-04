/* this is the example in 
 * https://en.cppreference.com/w/cpp/numeric/random/exponential_distribution
 * I'm just using it as a template.
 * Note that this webpage mentions point mutations on DNA as a possible application.
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

#define  SZ 12000

using namespace std;

int main()
{
    
    double *ma=(double*)malloc(SZ*sizeof(double));

    ma[3]= 4.04;

   cout << ma[3] << '\n';

   free(ma);

    return 0;
}
