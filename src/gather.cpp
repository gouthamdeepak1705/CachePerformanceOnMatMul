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
	infile.open (filename.c_str());

	int i = 0;
	while (getline(infile, line) && !line.empty()) {
		istringstream iss(line);
		A.resize(A.size() + 1);
		int a, j = 0;
		while (iss >> a) 
        {
			A[i].push_back(a);
			j++;
		}
		i++;
	}

	infile.close();
	ab.A = A;
	return ab;
}

vector< vector<int> > scatter(vector< vector<int> > A) 
{
    int n = A.size();
    vector<int > B(1000);

    // Generate 1,000 random indices and 1,000 random values
    for (int i = 0; i < 1000; i++) {
        int row = rand() % n;   // Random row index
        int col = rand() % n;   // Random column index

        // Scatter the random value into the matrix
        B[i] = A[row][col];
    }
    return A;
}


void printMatrix(vector< vector<int> > matrix) {
	vector< vector<int> >::iterator it;
	vector<int>::iterator inner;
	for (it=matrix.begin(); it != matrix.end(); it++) {
		for (inner = it->begin(); inner != it->end(); inner++) {
			cout << *inner;
			if(inner+1 != it->end()) {
				cout << "\t";
			}
		}
		cout << endl;
	}
}

int main (int argc, char* argv[]) {
	string filename;
	if (argc < 3) {
		filename = "2000.in";
	} else {
		filename = argv[2];
	}
	Result result = read (filename);
    parsec_roi_begin();
	vector< vector<int> > C = scatter(result.A);
    parsec_roi_end();
	//printMatrix(C);
	return 0;
}
