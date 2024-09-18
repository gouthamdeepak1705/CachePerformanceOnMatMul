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
    vector<vector<int>> A;
};

Result read(string filename) {
    vector<vector<int>> A;
    Result ab;
    string line;
    ifstream infile;
    infile.open(filename.c_str());

    if (!infile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return ab;
    }

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

vector<int> gather(const vector<vector<int>>& A) {
    int n = A.size();
    vector<int> gathered_data(1000);

    // Generate 1,000 random indices and gather values
    for (int i = 0; i < 1000; i++) {
        int row = rand() % n;  // Random row index
        int col = rand() % n;  // Random column index

        gathered_data[i] = A[row][col];  // Gather the value into the 1D vector
    }
    return gathered_data;
}

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
    srand(time(0));  // Seed the random number generator

    string filename;
    if (argc < 3) {
        filename = "2000.in";
    } else {
        filename = argv[2];
    }

    Result result = read(filename);
    if (result.A.empty()) {
        cerr << "Error: Matrix read unsuccessful or empty!" << endl;
        return 1;
    }

    parsec_roi_begin();
    vector<int> C = gather(result.A);
    parsec_roi_end();

    // Optionally print the gathered data as a 1D vector
    // printVector(C);

    return 0;
}
