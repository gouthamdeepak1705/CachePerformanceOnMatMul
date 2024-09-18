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

// Function to read the matrix from a file
Result read(string filename) {
    vector<vector<int>> A;
    Result ab;
    string line;
    ifstream infile;
    infile.open(filename.c_str());

    if (!infile) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
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

    // Debugging: Print the matrix size and content
    cout << "Matrix read from file: " << filename << " (" << A.size() << " rows)" << endl;
    for (const auto& row : A) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return ab;
}

// Function to gather random elements from the matrix
vector<int> gather(const vector<vector<int>>& A) {
    size_t n = A.size();  // Number of rows in the matrix

    // Check if matrix is empty
    if (n == 0) {
        cerr << "Error: Matrix is empty." << endl;
        exit(1);
    }

    int number_of_indices = 1000;  // Number of random elements to gather
    vector<int> indices(number_of_indices);  // Vector to store random indices
    vector<int> gathered_data(number_of_indices);  // Vector to store gathered elements

    // Generate 1,000 random indices and gather elements
    for (int i = 0; i < number_of_indices; i++) {
        size_t row, col;  // Changed to size_t to match the type of vector size
        do {
            int random_index = rand() % (n * n);  // Random index within the flattened matrix

            // Check for potential division by zero error
            if (n == 0) {
                cerr << "Error: Division by zero in index calculation. Matrix size is zero." << endl;
                exit(1);
            }

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

    // Debugging: Print arguments received
    cout << "Program arguments received: ";
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl;

    string filename;
    if (argc < 3) {
        filename = "2000.in";
        cout << "No filename provided, using default: " << filename << endl;
    } else {
        filename = argv[2];
        cout << "Filename provided: " << filename << endl;
    }

    Result result = read(filename);
    parsec_roi_begin();
    vector<int> C = gather(result.A);  // Gather random elements from the matrix
    parsec_roi_end();
    
    // Optionally print the gathered data as a 1D vector
    // printVector(C);

    return 0;
}
