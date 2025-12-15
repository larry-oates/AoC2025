#include <fstream>
#include <iostream>
#include <set>

using namespace std;        

template <class T>
int numDigits(T number)
{
    int digits = 0;
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}

long long unsigned int invalidIDs(long long unsigned int min, long long unsigned int max) {
    set<long long unsigned int> invalidIDs;
    long long unsigned int total{0};

    // Outer loop: Length of the pattern (1 digit, 2 digits, etc.)
    for (int patternLength = 1; ; patternLength++) {
        long long unsigned int startPat = 1;
        for (int k = 0; k < patternLength - 1; k++) startPat *= 10;
        long long unsigned int endPat = startPat * 10;
        long long unsigned int shift = endPat; 

        if (startPat * shift + startPat > max) {
            break; 
        }

        // Loop through actual patterns (e.g., 1, 2... or 10, 11... 99)
        for (long long unsigned int pattern = startPat; pattern < endPat; pattern++) {
            long long unsigned int id = pattern;

            // Inner loop: Keep appending the pattern until we go out of bounds
            while (true) {
                // Safety check to prevent overflow before multiplication
                if (max / shift < id) break; 
                id = (id * shift) + pattern;
                if (id > max) break; 
                if (id >= min) {
                    invalidIDs.insert(id);
                }
            }
        }
    }
    for (long long unsigned int i : invalidIDs) {
        total += i;
        // cout << "Found ID: " << i << endl; // Optional debug
    }

    cout << "Total: " << total << endl;
    return total;
}


int main  () {
    ifstream input("input");

    long unsigned int min {};
    long unsigned int max {};
    char range{};
    char delimiter {};
    long long unsigned int total{0};

    while ((input >> min >> range >> max >> delimiter) && range == '-' && delimiter == ',') {
        total += invalidIDs(min, max);
    }

    cout << "Total of invalid IDs: " << total <<endl;
    return 0;
} 
