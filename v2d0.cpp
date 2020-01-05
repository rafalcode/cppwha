/* Examples 
*/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main (int argc, char *argv[])
{
    if(argc!=2) {
        printf("One arg pls: file name with matrix\n"); 
        exit(EXIT_FAILURE);
    }

    ifstream inFile;
    inFile.open(argv[1]);

    if (inFile.fail())
        cerr << "Could not find file" << endl;

    vector<vector<float>> array;
    string line;
    float x;

    /* this is the dkws code: */
    for(i = 0; getline(inFile, line); i ++) {
        istringstream stream(line);
        for(j = 0; stream >> x; j ++) {
            array[i][j] = x;
        }
    }
    for(vector<float> v : array)
        cout << v << endl; // can't do that ... cout only strings.

    return 0; 
}
