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

vector<vector<int>> scatter(vector<vector<int>>& A) {
    int rows = A.size();
    if (rows == 0) return A;  // Return if matrix is empty

    int cols = A[0].size();

    // Seed the random number generator
    srand(static_cast<unsigned>(time(0)));

    // Scatter: Assign random values to 100 random indices
    for (int i = 0; i < 1000; i++) {
        int x = rand() % rows;  // Random row index
        int y = rand() % cols;  // Random column index
        int new_value = (rand() % 1000) + 1;  // Random value between 1 and 100
        A[x][y] = new_value;  // Assign the random value to the random index
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
