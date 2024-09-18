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

vector<int> gather(const vector<vector<int>>& A) {
    int n = A.size();
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
        gathered_data[i] = A[row][col];  // Gather the element
    }
    
    return gathered_data;  // Return the gathered data
}

// Updated to print a 1D vector
void printVector(const vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i + 1 != vec.size()) {
            cout << "\t";
        }
    }
    cout << endl;
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
    parsec_roi_begin();
    vector<int> C = gather(result.A);  // Corrected to vector<int>
    parsec_roi_end();
    
    // Optionally print the gathered data as a 1D vector
    //printVector(C);
    
    return 0;
}
