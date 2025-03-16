// from  chag 
// it's about perturbing a runif
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

vector<double> gensnv(int size) /* Generate Std Norm variates */
{
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> dist(0.0, 1.0);

    vector<double> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = dist(gen);
    }
    return vec;
}

vector<double> modvec1(const vector<double>& vec)
{
    vector<double> modified(vec.size());

    // Apply different scaling factors
    for (int i = 0; i < 5; i++)
        modified[i] = vec[i] * 1.0;
    for (int i = 5; i < 55; i++)
        modified[i] = vec[i] * 0.1;    // Next 50
    for (int i = 55; i < 330; i++)
        modified[i] = vec[i] * 0.001;  // Next 275
    for (size_t i = 330; i < vec.size(); i++)
        modified[i] = vec[i];    // Rest unchanged

    return modified;
}

vector<double> genvec2(const vector<double>& vec1)
{
    vector<double> vec2(vec1.size());

    // First 5 elements remain the same
    for (int i = 0; i < 5; i++)
        vec2[i] = vec1[i];

    // Next 50 elements: first 5 from vec1 + next 50 from vec1
    for (int i = 5; i < 55; i++)
        vec2[i] = vec2[i - 5] + vec1[i];

    // Next 275 elements: previous 55 from vec2 + next 275 from vec1
    for (int i = 55; i < 330; i++)
        vec2[i] = vec2[i - 55] + vec1[i];

    // Remaining values: Direct copy from vec1
    for (size_t i = 330; i < vec1.size(); i++)
        vec2[i] = vec1[i];

    return vec2;
}

void print_vector(const vector<double>& vec, int count = 10)
{
    for (int i = 0; i < count; i++) {
        cout << fixed << setprecision(6) << vec[i] << " ";
    }
    cout << "...\n";
}

int main()
{
    int size = 1000;
    // vector<int> vec1 = {2, 20, 160, 18gensnv(size);

    // Step 1: Generate standard normal variates
    vector<double> vec1 = gensnv(size);
    cout << "Vector 1 (first 10 values):\n";
    print_vector(vec1);
    vec1 = modvec1(vec1);

    // Step 2: Construct second vector
    vector<double> vec2 = genvec2(vec1);

    // Print first few values for verification
    cout << "Modified Vector 1 (first 10 values):\n";
    print_vector(vec1);

    cout << "\nVector 2 (first 10 values):\n";
    print_vector(vec2);

    return 0;
}
