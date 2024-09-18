#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void parsec_roi_begin() 
{
    // Mark the beginning of the region of interest
}

void parsec_roi_end() 
{
    // Mark the end of the region of interest
}

struct Result {
    vector<vector<int>> A;  // Corrected to store a 2D vector
};

// Function to read the matrix from a file
Result read(string filename) {
    vector<vector<int>> A;
    Result ab;
    string line;
    ifstream infile(filename.c_str());

    if (!infile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return ab;  // Return an empty Result
    }

    while (getline(infile, line) && !line.empty()) {
        istringstream iss(line);
        A.resize(A.size() + 1);
        int a;
        while (iss >> a) {
            A.back().push_back(a);  // Push back into the last row
        }
    }

    infile.close();
    ab.A = A;
    return ab;
}

// Gather function that returns a 1D vector of gathered data
vector<int> gather(const vector<vector<int>>& A) {
    int n = A.size();
    vector<int> B(1000);

    // Generate 1,000 random indices and gather values
    for (int i = 0; i < 1000; i++) {
        int row = rand() % n;   // Random row index
        int col = rand() % n;   // Random column index
        B[i] = A[row][col];     // Gather the value from the matrix
    }
    return B;
}

// Function to print a 1D vector
void printVector(const vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i + 1 != vec.size()) {
            cout << "\t";
        }
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    srand(time(0));  // Seed the random number generator

    string filename;
    if (argc < 3) {
        filename = "2000.in";  // Default filename
    } else {
        filename = argv[2];
    }

    Result result = read(filename);
    if (result.A.empty()) {  // Check if matrix read is successful
        cerr << "Error: Matrix read unsuccessful or empty!" << endl;
        return 1;
    }

    parsec_roi_begin();
    vector<int> C = gather(result.A);  // Gather values from the matrix
    parsec_roi_end();

    // Optionally print the gathered data as a 1D vector
    //printVector(C);

    return 0;
}
