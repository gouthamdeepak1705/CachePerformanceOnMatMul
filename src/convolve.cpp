#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

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

// Function to read matrix from a file
Result read(string filename) {
	vector< vector<int> > A;
	Result ab;
	string line;
	ifstream infile;
	infile.open(filename.c_str());

	int i = 0;
	while (getline(infile, line) && !line.empty()) {
		istringstream iss(line);
		A.resize(A.size() + 1);
		int a;
		while (iss >> a) {
			A[i].push_back(a);
		}
		i++;
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

// Perform convolution
vector<vector<int>> convolve(const vector<vector<int>>& matrix, const vector<vector<int>>& kernel) {
    int n = matrix.size();
    int k = kernel.size();
    int outputSize = (n - k) + 1;
    
    // If the matrix is too small for the kernel, return an empty output
    if (outputSize <= 0) {
        cout << "Error: Input matrix is too small for the kernel size." << endl;
        exit(1);
    }

    vector<vector<int>> output(outputSize, vector<int>(outputSize, 0));

    for (int i = 0; i <= n - k; i++) {
        for (int j = 0; j <= n - k; j++) {
            int sum = 0;
            for (int ki = 0; ki < k; ++ki) {
                for (int kj = 0; kj < k; ++kj) {
                    sum += matrix[i + ki][j + kj] * kernel[ki][kj];
                }
            }
            output[i][j] = sum;
        }
    }

    return output;
}

// Function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
	for (const auto& row : matrix) {
		for (const auto& elem : row) {
			cout << elem << "\t";
		}
		cout << endl;
	}
}

int main (int argc, char* argv[]) {
	string filename;
	if (argc < 2) {
		filename = "2000.in";
	} else {
		filename = argv[1];  // Corrected argument indexing
	}
    
    // Read input matrix from file
	Result result = read(filename);

    // Use Gaussian kernel (size 7x7)
    vector<vector<int>> kernel = gaussianKernel7x7(); 
    
    parsec_roi_begin();
    
    // Perform convolution
	vector<vector<int>> C = convolve(result.A, kernel);
    
    parsec_roi_end();

    // Uncomment to print the resulting matrix
    // printMatrix(C);

	return 0;
}
