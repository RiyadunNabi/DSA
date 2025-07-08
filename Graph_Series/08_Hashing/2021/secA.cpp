#include <iostream>
#include <unordered_set>
#include <string>
#include <algorithm>
using namespace std;

// Function to get the reverse complement of a DNA sequence
string getReverseComplement(const string& dna) {
    string complement = "";
    for (char c : dna) {
        if (c == 'A') complement += 'T';
        else if (c == 'T') complement += 'A';
        else if (c == 'C') complement += 'G';
        else if (c == 'G') complement += 'C';
    }
    reverse(complement.begin(), complement.end());
    return complement;
}

int main() {
    int n, l;
    cin >> n >> l;

    string sequences[n];
    unordered_set<string> seen;
    unordered_set<string> printed;

    for (int i = 0; i < n; ++i) {
        cin >> sequences[i];
        seen.insert(sequences[i]);
    }

    for (int i = 0; i < n; ++i) {
        string revComp = getReverseComplement(sequences[i]);
        if (seen.count(revComp)) {
            // Ensure each pair is printed only once
            string a = sequences[i], b = revComp;
            if (a > b) swap(a, b); // order alphabetically
            string pairKey = a + " " + b;
            if (!printed.count(pairKey)) {
                cout << a << " " << b << endl;
                printed.insert(pairKey);
            }
        }
    }

    return 0;
}
