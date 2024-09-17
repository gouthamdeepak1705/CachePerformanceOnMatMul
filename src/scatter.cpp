#include <iostream>
#include <vector>
#include <random>

using namespace std;

void parsec_roi_begin() 
{
    // Begin region of interest for performance measurement
}

void parsec_roi_end() 
{
    // End region of interest for performance measurement
}

// Function to generate random indices and data samples for scattering
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

// Function to perform scatter operation on a matrix
void scatter(vector<vector<int>>& matrix, const vector<pair<int, int>>& indices, const vector<int>& data) {
    for (size_t i = 0; i < indices.size(); i++) {  // Changed int to size_t to match indices.size() type
        int x = indices[i].first;
        int y = indices[i].second;
        matrix[x][y] = data[i];
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

    return 0;
}
