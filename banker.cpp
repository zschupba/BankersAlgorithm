// Zachary Schupbach
// 11/23/25
// This program implements bankers algorithm to print if a process
// is completable with given resources in a file.


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    ifstream fin("processAllocation.txt");
    if (!fin) {
        cout << "File didnt open yo\n";
        return 1;
    }

    int numProcess = 5; 
    int numResources = 3; 
    int numRoutines = 3;
        
    for(int q = 0; q < numRoutines; q++){
        bool notFound = false;
        // Vectors for the resources numbers
        vector<vector<int>> alloc(numProcess, vector<int>(numResources));
        vector<vector<int>> maxm(numProcess, vector<int>(numResources));
        vector<vector<int>> need(numProcess, vector<int>(numResources));
        vector<int> avail(numResources);

        string line;

        //Gets rid of file headers used for human readability
        getline(fin, line);
        getline(fin, line);
        getline(fin, line);

        // Format: P0 0 1 0  7 5 3
        for (int i = 0; i < numProcess; i++) {
            getline(fin, line);
            stringstream ss(line);

            string pname;   
            ss >> pname;
            ss >> alloc[i][0] >> alloc[i][1] >> alloc[i][2];
            ss >> maxm[i][0] >> maxm[i][1] >> maxm[i][2];
        }

        getline(fin, line);
        getline(fin, line);

        getline(fin, line);
        stringstream avs(line);
        avs >> avail[0] >> avail[1] >> avail[2];


        for (int i = 0; i < numProcess; i++)
            for (int j = 0; j < numResources; j++)
                need[i][j] = maxm[i][j] - alloc[i][j];

        vector<bool> finished(numProcess, false);   
        vector<int> safe;

        int count = 0;
        while (count < numProcess) {
            bool found = false;

            for (int i = 0; i < numProcess; i++) {
                if (!finished[i]) {
                    bool canRun = true;

                    for (int j = 0; j < numResources; j++) {
                        if (need[i][j] > avail[j]) {
                            canRun = false;
                            break;
                        }
                    }
                    if (canRun) {
                        for (int j = 0; j < numResources; j++)
                            avail[j] += alloc[i][j];

                        finished[i] = true;
                        safe.push_back(i);
                        count++;
                        found = true;
                    }
                }
            }

            if (!found) {
                cout << "Systems not safe\n\n";
                notFound = true;
                break;
            }
        }
        if (notFound == false){
            cout << "Systems in a safe state \n Safe sequence: ";
            for (int p : safe)
                cout << "P" << p << " ";

            cout << endl << "\n";
        }
    }
    return 0;
}
