/**************************************************************************
 *  
 *  File:    CS19B045_A5.cpp
 *
 *  Purpose:    -
 *
 *  Author:    Vishnu
 *
 *  Created:    Mon 08-March-2021 10:01:40
 *
 *  Last Modified:    Mon 09-February-2021 12:50:12
 *
 *  Changes:    1) Changed O(nlogn) divide and conquer to O(n) - Vishnu
 *              2) Changed int occu to bool occu to save space - Vishnu
 *
 **************************************************************************/
#include <iostream>

using namespace std;

int numUpdate = 0;          // Variable to store number of update commands

// Structure for finding maximum subarray sum using divide and conquer
struct Sum {
    int prefSum;                    // Prefix Sum
    int sufSum;                     // Suffix Sum
    int fulSum;                     // Whole Sum of subarray
    int maxSum;                     // Maximum subarray sum
};

class BloomBrain {

    public:
        BloomBrain(int);
        ~BloomBrain();
        long long update();
        void join();
        void leave();
        int occupied();
        int play();
        long long inversion();
        long long mergeSort(int*, int*, int, int);
        Sum maxSum(int, int);

    private:
        int* rooms;
        int numRooms;               // To store number of rooms
        bool* occu;              // Stores 1 if rooms[i] is occupied
        int* temp1;
        int* temp2;
};


BloomBrain:: BloomBrain(int n) {            // Constructor for allocating memory
    rooms = new int[n];
    occu = new bool[n];

    temp2 = new int[n];                     // dummy arrays for mergesort
    temp1 = new int[n];

    for(int  i = 0; i < n; i++) {
        rooms[i] = 0;
        occu[i] = 0;
    }
    numRooms = n;
}

BloomBrain:: ~BloomBrain() {                                      // Destructor for deallocating memory
    delete[] rooms;
    delete[] temp1;
    delete[] occu;
    delete[] temp2;
}

long long BloomBrain:: update() { 

    if(numUpdate == 0) {                            // For the first update command
        for(int i = 0; i < numRooms; i++) {
            cin >> rooms[i];
            occu[i] = 1;
        }
    }

    else {                                              // For subsequenet update commands
        for(int i = 0; i < numRooms; i++) {
            cin >> rooms[i];
            if(occu[i] == 0&&rooms[i]) occu[i] = 1;     // If new element is added
        }
    }

    numUpdate++;                // Increment numUpdate
    return inversion();
}

long long BloomBrain:: inversion() {                // Function to find the number of inversions in an array

    int t = 0;
    for(int i = 0; i < numRooms; i++) {
        if(occu[i])                         // Copy only occupied rooms
            temp1[t++] = rooms[i];           
    }

    return mergeSort(temp1, temp2, 0, t-1);          // Find number of inversions using mergesort
}

long long BloomBrain:: mergeSort(int* temp1, int* temp2, int l, int r) {
    if(r <= l) return 0;
    long long inv = 0;
    int mid = l+(r-l)/2;

    inv += mergeSort(temp1, temp2, l, mid);              // Recurse for left subarray
    inv += mergeSort(temp1, temp2, mid+1, r);            // Recurse for right subarray

    int i = l, j = mid+1, k = l;            

    // Merging begins
    while(i <= mid && j <= r) {                 // When both arrays have not yet run out
        if(temp1[i] <= temp1[j]) {
            temp2[k] = temp1[i];
            k++, i++;
        }
        else {
            temp2[k] = temp1[j];
            k++, j++;
            inv += mid-i+1;
        }
    }
    
    while(j <= r) {                     // When left array has run out
        temp2[k] = temp1[j];
        k++, j++;
    }

    while(i <= mid) {                   // When right array has run out
        temp2[k] = temp1[i];
        k++, i++;
    }
    // Merging ends

    for(i = l; i <= r; i++) 
        temp1[i] = temp2[i];                     // Replace original array with sorted one

    return inv;             // Return number of inversions
}

void BloomBrain:: join() {
    int room, s;
    cin >> s;                                   // New seraphic number

    for(room = numRooms-1; room >=0; room--) {
        if(rooms[room] == 0)                                // Highest unoccupied room
            break;
    }

    rooms[room] = s;                    // Fill the new searaphic number
    occu[room] = 1;                       // Change occupancy
}

void BloomBrain:: leave() {
    int r;
    cin>>r;
    occu[r] = 0;                               // Change occupancy to false
    rooms[r] = 0;
}

int BloomBrain:: play() {
    return maxSum(0, numRooms-1).maxSum;
}

Sum BloomBrain:: maxSum(int l, int r) {
    if(l == r) 
        return {rooms[l], rooms[l], rooms[l], rooms[l]};            // If the subarray is a single element
    int mid = l+(r-l)/2;

    Sum left = maxSum(l, mid);              // Recurse for left and right subarrays
    Sum right = maxSum(mid+1, r);

    Sum tot = {
        // tot.ps = max(l.ps, l.fs+r.ps, l.fs+r.fs)
        max(left.prefSum, max(left.fulSum+right.prefSum, left.fulSum+right.fulSum)), 
        // tot.ss = max(r.ss, r.fs+l.ss, r.fs+l.fs)
        max(right.sufSum, max(right.fulSum+left.sufSum, right.fulSum+left.fulSum)), 
        // tot.fs = l.fs+r.fs
        left.fulSum+right.fulSum,
        // tot.ms = max(l.ss+r.ss, l.ms, r.ms)
        max(left.sufSum+right.prefSum, max(left.maxSum, right.maxSum))
    };

    return tot;
}

int BloomBrain:: occupied() {
    int occupancy = 0;
    for(int i = 0; i < numRooms; i++) 
        if(occu[i]) occupancy++;                // Count number of occupied rooms
    return occupancy;
}

int main() {
    int n, q;
    string s;
    cin >> n >> q;
    BloomBrain B(n);
    while(q--) {
        cin >> s;
        if(s == "update") {
            cout << B.update() << endl;
        }
        else if(s == "play") {
            cout << B.play() << endl;
        }
        else if(s == "leave") {
            B.leave();
        }
        else if(s == "occupied") {
            cout << B.occupied() << endl;
        }
        else if(s == "join") {
            B.join();
        }
    }
}