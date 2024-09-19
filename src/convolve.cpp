#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void parsec_roi_begin() 
{

}

void parsec_roi_end() 
{
	
}

struct Result {
	vector< vector<int> > A;
};

// Function to read the matrix from a file (as specified in the bash script)
Result readMatrixFromFile(string filename) {
    vector< vector<int> > A;
    Result ab;
    string line;
    ifstream infile(filename);

    if (!infile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    while (getline(infile, line)) {
        istringstream iss(line);
        vector<int> row;
        int value;
        while (iss >> value) {
            row.push_back(value);
        }
        A.push_back(row);
    }
    infile.close();
    ab.A = A;
    return ab;
}

// Define the 7x7 Gaussian kernel
vector<vector<int>> gaussianKernel7x7() {
    return {
        {0, 0, 1, 2, 1, 0, 0},
        {0, 3, 13, 22, 13, 3, 0},
        {1, 13, 59, 97, 59, 13, 1},
        {2, 22, 97, 159, 97, 22, 2},
        {1, 13, 59, 97, 59, 13, 1},
        {0, 3, 13, 22, 13, 3, 0},
        {0, 0, 1, 2, 1, 0, 0}
    };
}

// Pad the matrix with zeros around the border (for 7x7 kernel)
vector<vector<int>> padMatrix(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> padded(rows + 6, vector<int>(cols + 6, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            padded[i + 3][j + 3] = matrix[i][j];  // Pad with 3 rows and columns (half of 7-1)
        }
    }
    return padded;
}

// Perform convolution using the 7x7 Gaussian kernel
vector<vector<int>> convolve(const vector<vector<int>>& matrix) {
    vector<vector<int>> kernel = gaussianKernel7x7();
    vector<vector<int>> padded = padMatrix(matrix);
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> result(rows, vector<int>(cols, 0));

    for (int i = 3; i < rows + 3; ++i) {  // Start at index 3 due to padding
        for (int j = 3; j < cols + 3; ++j) {
            int sum = 0;
            for (int ki = -3; ki <= 3; ++ki) {
                for (int kj = -3; kj <= 3; ++kj) {
                    sum += padded[i + ki][j + kj] * kernel[ki + 3][kj + 3];  // Shift by 3 for 7x7 kernel
                }
            }
            result[i - 3][j - 3] = sum;
        }
    }
    return result;
}

int main (int argc, char* argv[]) {
    srand(time(0));
    
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    string input_filename = argv[1];  // Use the input file specified in the command line
    Result result = readMatrixFromFile(input_filename);  // Read the matrix from the file
    parsec_roi_begin();
    vector< vector<int> > C = convolve(result.A);
    parsec_roi_end();

    // Optionally print the result
    // for (const auto& row : C) {
    //     for (const auto& elem : row) {
    //         cout << elem << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}
