#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>  // For rand() and srand()

using namespace std;

void parsec_roi_begin() 
{
    // Placeholder for profiling region start
}

void parsec_roi_end() 
{
    // Placeholder for profiling region end
}

// Get matrix size from input file
int getMatrixSize(string filename) {
    string line;
    ifstream infile;
    infile.open (filename.c_str());
    getline(infile, line);
    return count(line.begin(), line.end(), '\t') + 1;
}

// Read matrices from input file
void read(string filename, vector< vector<int> > &A, vector< vector<int> > &B) {
    string line;
    FILE* matrixfile = freopen(filename.c_str(), "r", stdin);

    int i = 0, j, a;
    while (getline(cin, line) && !line.empty()) {
        istringstream iss(line);
        j = 0;
        while (iss >> a) {
            A[i][j] = a;
            j++;
        }
        i++;
    }

    i = 0;
    while (getline(cin, line)) {
        istringstream iss(line);
        j = 0;
        while (iss >> a) {
            B[i][j] = a;
            j++;
        }
        i++;
    }

    fclose (matrixfile);
}

// Matrix multiplication using IKJ algorithm
vector< vector<int> > ikjalgorithm(vector< vector<int> > A,
                                   vector< vector<int> > B,
                                   vector< vector<int> > &C, int n) {
    for (register int i = 0; i < n; i++) {
        for (register int k = 0; k < n; k++) {
            for (register int j = 0; j < n; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Print the matrix
void printMatrix(vector< vector<int> > matrix, int n) {
    for (int i=0; i < n; i++) {
        for (int j=0; j < n; j++) {
            if (j != 0) {
                cout << "\t";
            }
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

// Scatter operation: Generate 1,000 random indices and values, scatter them into matrix A
void scatter(vector< vector<int> > &A, int n) {
    srand(time(0));  // Seed for random number generation

    for (int i = 0; i < 1000; i++) {
        int row = rand() % n;   // Random row index
        int col = rand() % n;   // Random column index
        int value = rand();     // Random value without bounds

        // Scatter the random value into the matrix
        A[row][col] = value;
    }
}

int main (int argc, char* argv[]) {
    string filename;
    if (argc < 3) {
        filename = "2000.in";
    } else {
        filename = argv[2];
    }

    // Determine matrix size (should be 128 or 150 based on input file)
    int n = getMatrixSize(filename);
    vector<int> inner (n);
    vector< vector<int> > A(n, inner), B(n, inner), C(n, inner);
    read(filename, A, B);

    // Perform scatter operation before IKJ algorithm
    scatter(A, n);  // Scatter random values into matrix A

    parsec_roi_begin();
    ikjalgorithm(A, B, C, n);
    parsec_roi_end();

    // Optional: Print matrix C to verify results
    // printMatrix(C, n);

    return 0;
}
