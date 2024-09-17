#include <iostream>
#include <vector>
#include <random>

using namespace std;

void parsec_roi_begin() 
{
    
}

void parsec_roi_end() 
{
   
}


void generateRandomIndicesAndData(int max_x, int max_y, vector<pair<int, int>>& indices, vector<int>& data) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis_x(0, max_x - 1);
    uniform_int_distribution<> dis_y(0, max_y - 1);
    uniform_int_distribution<> dis_data(1, 100);  // Random data between 1 and 100

    for (int i = 0; i < 1000; i++) {
        int x = dis_x(gen);
        int y = dis_y(gen);
        indices.push_back(make_pair(x, y));
        data.push_back(dis_data(gen));
    }
}


void scatter(vector<vector<int>>& matrix, const vector<pair<int, int>>& indices, const vector<int>& data) {
    for (int i = 0; i < indices.size(); i++) {
        int x = indices[i].first;
        int y = indices[i].second;
        matrix[x][y] = data[i];
    }
}


void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << "\t";
        }
        cout << endl;
    }
}

int main() {
    // Step 1: Initialize matrices of size 128x128 and 150x150
    vector<vector<int>> matrix_128(128, vector<int>(128, 0));
    vector<vector<int>> matrix_150(150, vector<int>(150, 0));

    // Step 2: Generate random indices and data samples for 128x128 matrix
    vector<pair<int, int>> indices_128;
    vector<int> data_128;
    generateRandomIndicesAndData(128, 128, indices_128, data_128);

    // Step 3: Generate random indices and data samples for 150x150 matrix
    vector<pair<int, int>> indices_150;
    vector<int> data_150;
    generateRandomIndicesAndData(150, 150, indices_150, data_150);

    // Step 4: Perform scatter operation on the matrices
    parsec_roi_begin();  // Start ROI
    scatter(matrix_128, indices_128, data_128);
    scatter(matrix_150, indices_150, data_150);
    parsec_roi_end();  // End ROI

    // Optional: Print the resulting matrices
    cout << "Scattered Matrix (128 x 128):" << endl;
    printMatrix(matrix_128);
    
    cout << "\nScattered Matrix (150 x 150):" << endl;
    printMatrix(matrix_150);

    return 0;
}
