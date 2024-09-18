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

vector< vector<int> > read(string filename) {
	vector< vector<int> > A;
	string line;
	ifstream infile;
	infile.open(filename.c_str());

	int i = 0;
	while (getline(infile, line)) {
		istringstream iss(line);
		A.resize(A.size() + 1);
		int a;
		while (iss >> a) {
			A[i].push_back(a);
		}
		i++;
	}

	infile.close();
	return A;
}

// Perform 2D convolution with a 3x3 kernel
vector< vector<int> > convolution2D(vector< vector<int> > A, vector< vector<float> > kernel) {
	int n = A.size();
	int m = A[0].size();

	// Initialize output matrix C with the same size as A
	vector<int> tmp(m, 0);
	vector< vector<int> > C(n, tmp);

	int kernelSize = kernel.size();
	int offset = kernelSize / 2;

	// Perform convolution
	for (int i = offset; i < n - offset; i++) {
		for (int j = offset; j < m - offset; j++) {
			float sum = 0.0;
			// Convolution operation
			for (int ki = 0; ki < kernelSize; ki++) {
				for (int kj = 0; kj < kernelSize; kj++) {
					int ni = i + (ki - offset); // Neighbor index for matrix A
					int nj = j + (kj - offset); // Neighbor index for matrix A
					sum += A[ni][nj] * kernel[ki][kj];
				}
			}
			C[i][j] = static_cast<int>(sum); // Store the result in C
		}
	}

	return C;
}

void printMatrix(vector< vector<int> > matrix) {
	vector< vector<int> >::iterator it;
	vector<int>::iterator inner;
	for (it = matrix.begin(); it != matrix.end(); it++) {
		for (inner = it->begin(); inner != it->end(); inner++) {
			cout << *inner;
			if (inner + 1 != it->end()) {
				cout << "\t";
			}
		}
		cout << endl;
	}
}

int main(int argc, char* argv[]) {
	string filename;
	if (argc < 3) {
		filename = "2000.in";
	} else {
		filename = argv[2];
	}

	// Read matrix A from file
	vector< vector<int> > A = read(filename);

	// Define a 3x3 Gaussian kernel
	vector< vector<float> > gaussianKernel = {
		{1 / 16.0, 2 / 16.0, 1 / 16.0},
		{2 / 16.0, 4 / 16.0, 2 / 16.0},
		{1 / 16.0, 2 / 16.0, 1 / 16.0}
	};

	// Perform convolution on matrix A
	parsec_roi_begin();
	vector< vector<int> > C = convolution2D(A, gaussianKernel);
	parsec_roi_end();

	// Uncomment the following line to print the result
	// printMatrix(C);

	return 0;
}
