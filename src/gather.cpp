#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_set>

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
    int elements = 1000;
    vector<int> indices(elements), result(elements);
    unordered_set<int> unique_indices;
    
    for(int i = 0; i < elements; ++i) {
        int random_index;
        do {
            random_index = rand() % (n * n);
        } while(unique_indices.find(random_index) != unique_indices.end());
        
        indices[i] = random_index;
        unique_indices.insert(random_index);
    }

    int offset = 5;
    for(int idx = 0; idx < elements; ++idx) {
        int rowIndex = indices[idx] / n;
        int columnIndex = indices[idx] % n;
        result[idx] = A[rowIndex][columnIndex] + offset;
    }
    
    return result;
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
    vector<int> C = gather(result.A);
    parsec_roi_end();
    return 0;
}
