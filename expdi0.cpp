/* this is the example in 
 * https://en.cppreference.com/w/cpp/numeric/random/exponential_distribution
 * I'm just using it as a template.
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>

using namespace std;

int main()
{
    random_device rd;
    mt19937 gen(rd());
 
    // if particles decay once per second on average,
    // how much time, in seconds, until the next one?
    exponential_distribution<> d(1);
 
    map<int, int> hist;
    for(int n=0; n<10000; ++n) {
        ++hist[2*d(gen)];
    }
    for(auto p : hist) {
        cout << fixed << setprecision(1) << p.first/2.0 << '-' << (p.first+1)/2.0 << ' ' << string(p.second/200, '*') << '\n';
    }

    return 0;
}
