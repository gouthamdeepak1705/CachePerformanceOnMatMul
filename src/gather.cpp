// Updated code with additional checks

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void parsec_roi_begin() {}

void parsec_roi_end() {}

struct Result {
    vector< vector<int> > A;
};

Result read(string filename) {
    vector< vector<int> > A;
    Result ab;
    string line;
    ifstream infile;
    infile.open(filename.c_str());

    if (!infile.is_open()) { // Check if file opened successfully
        cerr << "Error opening file: " << filename << endl;
        return ab; // Return empty Result
    }

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

vector<int> gather(const vector<vector<int>>& A) {
    int n = A.size();
    if (n == 0) {
        cerr << "Error: Matrix is empty!" << endl;
        return {};
    }
    
    int number_of_indices = 1000;
    vector<int> indices(number_of_indices), gathered_data(number_of_indices);
    
    // Generate 1,000 random indices
    for(int i = 0; i < number_of_indices; i++) {
        indices[i] = rand() % (n * n);  // Random index within the flattened matrix
    }
    
    // Gather elements at the random indices
    for(int i = 0; i < number_of_indices; i++) {
        int row = indices[i] / n;  // Compute row
        int col = indices[i] % n;  // Compute column
        
        if (row < 0 || row >= n || col < 0 || col >= A[row].size()) { // Check bounds
            cerr << "Error: Index out of bounds at " << row << ", " << col << endl;
            continue;
        }
        
        gathered_data[i] = A[row][col];  // Gather the element
    }
    
    return gathered_data;  // Return the gathered data
}

int main (int argc, char* argv[]) {
    srand(time(0));
    string filename;
    if (argc < 3) {
        filename = "2000.in";
    } else {
        filename = argv[2];
    }
    Result result = read (filename);
    if (result.A.empty()) { // Check if matrix read is successful
        cerr << "Error: Matrix read unsuccessful or empty!" << endl;
        return 1;
    }

    parsec_roi_begin();
    vector<int> C = gather(result.A);  // Corrected to vector<int>
    parsec_roi_end();
    
    // Optionally print the gathered data as a 1D vector
    //printVector(C);
    
    return 0;
}
