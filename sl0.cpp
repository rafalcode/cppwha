#include <fstream>
#include <sstream>

using namespace std;

string slurp(const char *filename)
{
        ifstream in;
        in.open(filename, ifstream::in | ifstream::binary);
        stringstream sstr;
        sstr << in.rdbuf();
        in.close();
        return sstr.str();
}
