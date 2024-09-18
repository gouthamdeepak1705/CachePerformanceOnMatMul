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

vector<int> gather(const vector<vector<int>>& A) {
    int n = A.size();  // Number of rows in the matrix
    int number_of_indices = 1000;  // Number of random elements to gather
    vector<int> indices(number_of_indices);  // Vector to store random indices
    vector<int> gathered_data(number_of_indices);  // Vector to store gathered elements
    
    // Generate 1,000 random indices and gather elements
    for (int i = 0; i < number_of_indices; i++) {
        int row, col;
        do {
            int random_index = rand() % (n * n);  // Random index within the flattened matrix
            row = random_index / n;  // Compute row index
            col = random_index % n;  // Compute column index
        } while (row >= A.size() || col >= A[row].size());  // Ensure indices are within bounds
        
        gathered_data[i] = A[row][col];  // Gather the element from the matrix
    }
    
    return gathered_data;  // Return the gathered data
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
    srand(time(0));
    string filename;
    if (argc < 3) {
        filename = "2000.in";
    } else {
        filename = argv[2];
    }
    Result result = read(filename);
    parsec_roi_begin();
    vector<int> C = gather(result.A);  // Gather random elements from the matrix
    parsec_roi_end();
    
    // Optionally print the gathered data as a 1D vector
    // printVector(C);
    
    return 0;
}
