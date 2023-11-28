// from chatgpt. free version, so most likely wrong.
#include <algorithm> // for sort
#include <iostream>
#include <iomanip> // for setprecision()
#include <numeric> // for iota()
#include <vector>
#include <cmath>

using namespace std;

double calculateMean(const vector<int>& arr)
{
    int sum = 0;
    for (int num : arr) {
        sum += num;
    }
    return static_cast<double>(sum) / arr.size();
}

double calculateSpearmanCorrelation(const vector<int>& arr1, const vector<int>& arr2)
{
    // Create vectors to store ranks
    vector<int> rank1(arr1.size());
    vector<int> rank2(arr2.size());

    // Assign ranks to the vectors
    iota(rank1.begin(), rank1.end(), 1);
    iota(rank2.begin(), rank2.end(), 1);

    // Sort the vectors based on the values in arr1 and arr2
    sort(rank1.begin(), rank1.end(), [&arr1](int i, int j) { return arr1[i - 1] < arr1[j - 1]; });
    sort(rank2.begin(), rank2.end(), [&arr2](int i, int j) { return arr2[i - 1] < arr2[j - 1]; });

    // Calculate the differences between ranks
    double sumSquaredDiff = 0.0;
    for (size_t i = 0; i < arr1.size(); i++) {
        int diff = rank1[i] - rank2[i];
        sumSquaredDiff += diff * diff;
    }

    // Calculate Spearman correlation coefficient
    double correlation = 1.0 - (6.0 * sumSquaredDiff) / (arr1.size() * (arr1.size() * arr1.size() - 1));

    return correlation;
}

int main()
{
    // Example sequences, replace with your own data
    vector<int> sequence1 = {1, 2, 3, 4, 5};
    vector<int> sequence2 = {3, 5, 4, 1, 1};

    // Calculate Spearman correlation
    double spearmanCorrelation = calculateSpearmanCorrelation(sequence1, sequence2);

    // Display the result
    cout << "Spearman Correlation: " << fixed << setprecision(4) << spearmanCorrelation << endl;

    return 0;
}
