#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Two dimensional matrix representing resource allocation for each process
// Proccesses * Resource allocation per process
vector<vector<int>> allocationMatrix;

// Two dimensional matrix representing the maximum resources needed for each process
// Processes * Maximum resources per process
vector<vector<int>> maxMatrix;

// One dimensional vector representing available resources within the system
vector<int> availableResources;

// Initialize these varibles to keep track of processes and resources in the system respectively
int numOfProcesses = 0;
int numOfResources = 0;

int main(int argc, char** argv) {
    if(argc != 2) { return 1; }     // Ensure we have an input file to read

    ifstream inputFile(argv[1]);    // Initialize file stream to be read from

    string line;    // Initialize string variable to store each line of the input file

    // Intialize one dimensional vectors to be concatenated into a two dimensional matrix
    vector<int> maxTemp, allocTemp;

    while(getline(inputFile, line)) {   // Reads in lines from the file

        cout << line;   // Output the current line

        // I'm hardcoding how the txt file is being read and interpreted
        // Since the number locations will be in constant positions I will be looking in constant positions
        //
        // The format is:
        // AV XXX
        // P0 XXX XXX
        // ...
        // Pn XXX XXX
        //

        if(line[0] == 'A') {                // If true, we are looking at available resources
            for(int i = 3; i < 6; i++) {
                availableResources.push_back(line[i] - '0');    // Subtract '0' to get integer values of ascii char
                numOfResources++;                               // Increment resource count
            }
        } else if(line[0] == 'P') {         // Othewise, we are looking at process resource allocation and maximums per each process
            numOfProcesses++;               // Increment process count
            for(int i = 3; i < 6; i++) {
                allocTemp.push_back(line[i] - '0');     // Subtract '0' to get integer values of ascii char
            }
            for(int i = 7; i < 10; i++) {
                maxTemp.push_back(line[i] - '0');       // Subtract '0' to get integer values of ascii char
            }
        }

        // Store vector in matrix
        allocationMatrix.push_back(allocTemp);     
        maxMatrix.push_back(maxTemp);

        // Clear vectors for next loop
        allocTemp.clear();
        maxTemp.clear();

        cout << endl;   // Cleans up outputs when reading through the file
    }
    
    // After the while loop we are done with input file
    inputFile.close();

    // Initialize arrays to track finished processes and the safe sequence
    // I elected to use arrays rather than vectors since the size is calculated and constant
    int finished[numOfProcesses], safe[numOfProcesses], posIndex = 0;

    for(int i = 0; i < numOfProcesses; i++) {
        finished[i] = 0;    // Initialize entire array to 0, meaning no processes are finished at this point
    }

    cout << endl;

    // Two dimensional array to track resource needs of each processe
    // Processes * Resources needs per process
    int need[numOfProcesses][numOfResources];

    for(int i = 1; i < numOfProcesses + 1; i++) {       // Calculate resource needs for each process
        for(int j = 0; j < numOfResources; j++) {
            need[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];  // Subtract alloction by max to calculate resource needs
        }
    }

    int resourceIndex = 0;

    for(int i = 1; i < numOfProcesses + 1; i++) {               // Checks safety for each process
        for(int j = 1; j < numOfProcesses + 1; j++) {           // Two dimensional arrays require two dimensional loops
            if(finished[j] == 0) {  // If a process isn't finished...

                int flag = 0;

                for(int k = 0; k < numOfResources; k++) {
                    if(need[j][k] > availableResources[k]) {    // If needs exceed available resouces...
                        flag = 1;                               // Then process unsafe set flag to 1 to reflect this
                        break;                                  // If process is unsafe exit loop
                    }
                }

                if(flag == 0) {                 // If process is safe after check, add it to the safe sequence

                    safe[posIndex++] = j - 1;   // Store process number

                    for(resourceIndex = 0; resourceIndex < numOfResources; resourceIndex++) {
                        availableResources[resourceIndex] += allocationMatrix[j][resourceIndex];    // Releases resources
                    }

                    finished[j] = 1;            // Marks process as finished
                }
            }
        }
    }

    int flag = 1;   // Flag to track safety

    for(int i = 1; i < numOfProcesses + 1; i++) {       // Checks if all processes are finished
        if(finished[i] == 0) {
            flag = 0;                                   // If any process isn't finished, state is unsafe, set flag to 0 to reflect this
            cout << "Sequence is unsafe." << endl;
            break;
        }
    }

    if(flag == 1) {                                     // If processes are finsihed, and deamed safe...
        cout << "The safe sequence is: ";
        for(int i = 0; i < numOfProcesses - 1; i++) {   // Then print the safe sequence
            cout << "P" << safe[i] << " -> ";
        }
        cout << "P" << safe[numOfProcesses - 1] << endl;
    }

    return 0;
}