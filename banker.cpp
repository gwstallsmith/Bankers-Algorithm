#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> allocationMatrix;

vector<vector<int>> maxMatrix;

vector<int> availableResources;

int numOfProcesses = 0;
int numOfResources = 0;

int main(int argc, char** argv) {
    if(argc != 2) { return 1; }

    ifstream inputFile(argv[1]);

    string line;

    vector<int> maxTemp, allocTemp;

    while(getline(inputFile, line)) {

        cout << line;


        // I'm hardcoding how it reaches into the file
        // Since the number locations will be in constant positions I will be looking in constant positions
        //
        // The format is:
        // AV XXX
        // P0 XXX XXX
        // ...
        // Pn XXX XXX
        //

        if(line[0] == 'A') {            // If true, we are looking at available resources
            // Store available resources in vector
            for(int i = 3; i < 6; i++) {
                // Subtract '0' to get integer values
                availableResources.push_back(line[i] - '0');
                numOfResources++;
            }
        } else if(line[0] == 'P') {    // Othewise, we are looking at process stuff
            numOfProcesses++;
            for(int i = 3; i < 6; i++) {
                allocTemp.push_back(line[i] - '0');
            }
            for(int i = 7; i < 10; i++) {
                maxTemp.push_back(line[i] - '0');
            }

        }

        allocationMatrix.push_back(allocTemp);
        maxMatrix.push_back(maxTemp);

        allocTemp.clear();
        maxTemp.clear();

        cout << endl;

    }
    // After while loop we are done with input file
    inputFile.close();



    int finished[numOfProcesses], safe[numOfProcesses], posIndex = 0;
    for(int i = 0; i < numOfProcesses; i++) {
        finished[i] = 0;
    }

    
    cout << endl;

    int need[numOfProcesses][numOfResources];

    for(int i = 1; i < numOfProcesses + 1; i++) {
        for(int j = 0; j < numOfResources; j++) {
            need[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];
        }
    }


    int resourceIndex = 0;

    for(int i = 1; i < numOfProcesses + 1; i++) {

        for(int j = 1; j < numOfProcesses + 1; j++) {

            if(finished[j] == 0) {

                int flag = 0;

                for(int k = 0; k < numOfResources; k++) {

                    if(need[j][k] > availableResources[k]) {
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0) {

                    safe[posIndex++] = j - 1;

                    for(resourceIndex = 0; resourceIndex < numOfResources; resourceIndex++) {
                        availableResources[resourceIndex] += allocationMatrix[j][resourceIndex];
                    }

                    finished[j] = 1;
                }
            }
        }
    }

    int flag = 1;


    for(int i = 1; i < numOfProcesses + 1; i++) {
        if(finished[i] == 0) {
            flag = 0;
            cout << "Sequence is unsafe." << endl;
            break;
        }
    }

    if(flag == 1) {
        cout << "The safe sequence is: ";
        for(int i = 0; i < numOfProcesses - 1; i++) {
            cout << "P" << safe[i] << " -> ";
        }
        cout << "P" << safe[numOfProcesses - 1] << endl;
    }


    return 0;
}