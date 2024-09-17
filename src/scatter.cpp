#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>  // For rand() and srand()

using namespace std;

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

vector< vector<int> > scatter(vector< vector<int> > A) {
    int n = A.size();  // Assuming A is a square matrix (n x n)

    // Generate 1,000 random indices and 1,000 random values
    for (int i = 0; i < 1000; i++) {
        int row = rand() % n;   // Random row index
        int col = rand() % n;   // Random column index
        int value = rand();     // Random value without bounds

        // Scatter the random value into the matrix
        A[row][col] = value;
    }

    return A;
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

    vector< vector<int> > C = scatter(result.A);

    // Display or process matrix C as needed
    for (const auto& row : C) {
        for (const auto& val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
