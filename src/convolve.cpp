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
		int a, j = 0;
		while (iss >> a) {
			A[i].push_back(a);
			j++;
		}
		i++;
	}
	infile.close();
	ab.A = A;
	return ab;
}

vector<vector<int>> initializeIdentityKernel(int size) {
    vector<vector<int>> kernel(size, vector<int>(size, 0));
    for (int i = 0; i < size; ++i) {
        kernel[i][i] = 1; 
    }
    return kernel;
}

vector<vector<int>> convolve(const vector<vector<int>>& matrix, const vector<vector<int>>& kernel) {
    int matrixSize = matrix.size();
    int kernelSize = kernel.size();
    int outputSize = matrixSize - kernelSize + 1;
    
    vector<vector<int>> result(outputSize, vector<int>(outputSize, 0));

    for (int row = 0; row <= matrixSize - kernelSize; ++row) {
        for (int col = 0; col <= matrixSize - kernelSize; ++col) {
            int convSum = 0;
            for (int i = 0; i < kernelSize; ++i) {
                for (int j = 0; j < kernelSize; ++j) {
                    convSum += matrix[row + i][col + j] * kernel[i][j];
                }
            }
            result[row][col] = convSum;
        }
    }

    return result;
}

void printMatrix(vector< vector<int> > matrix) {
	vector< vector<int> >::iterator it;
	vector<int>::iterator inner;
	for (it = matrix.begin(); it != matrix.end(); ++it) {
		for (inner = it->begin(); inner != it->end(); ++inner) {
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
	Result result = read(filename);
    vector<vector<int>> kernel = initializeIdentityKernel(7); 
    parsec_roi_begin();
	vector< vector<int> > C = convolve(result.A, kernel);
    parsec_roi_end();
	return 0;
}
