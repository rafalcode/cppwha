#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

using namespace std;

int main(void)
{
    stringstream ss;
    ss << "zdrastvui";
    string copystr = ss.str();

    cout << "string is : " << copystr << '\n';

    double d = 0.321566;
    ss << "%2.2f" << d << "\n";
    cout << ss.str();

    return 0;
}
