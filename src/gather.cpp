#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>  

using namespace std;

void parsec_roi_begin() 
{
    // Start of Region of Interest
}

void parsec_roi_end() 
{
    // End of Region of Interest
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

vector<int> gather(const vector< vector<int> >& A) {
    int n = A.size();
    vector<int> gathered_values; 

    for (int i = 0; i < 1000; i++) {
        int row = rand() % n;   
        int col = rand() % n;  

        gathered_values.push_back(A[row][col]);
    }

    return gathered_values;
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
    vector<int> gathered = gather(result.A);  
    parsec_roi_end();
    
    for (int value : gathered) {
        cout << value << " ";
    }
    cout << endl;
    
    return 0;
}
