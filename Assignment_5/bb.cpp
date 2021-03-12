#include <iostream>
#include <string>

using namespace std;

int numUpdate = 0;

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
        int midSum(int, int, int);
        int maxSum(int, int);

    private:
        int* rooms;
        int occupancy;
        int numRooms;
        int* occu;
        int* temp;
        int* a;
};


BloomBrain:: BloomBrain(int n) {
    rooms = new int[n];
    occu = new int[n];
    a = new int[n];
    temp = new int[n];
    for(int  i =0; i < n;i ++) {
        rooms[i] = 0;
        occu[i] = 0;
    }
    occupancy = 0;
    numRooms = n;
}

BloomBrain:: ~BloomBrain() {                                      // Destructor for deallocating memory
    delete[] rooms;
    occupancy = 0;
}

long long BloomBrain:: update() { 

    occupancy = 0;
    if(numUpdate == 0) {
        for(int i = 0; i < numRooms; i++) {
            cin >> rooms[i];
            occu[i] = 1;
        }
    }
    else {
        for(int i = 0; i < numRooms; i++) {
            cin >> rooms[i];
            if(occu[i] == 0&&rooms[i]) occu[i] = 1;
        }
    }

    numUpdate++;
    return inversion();
}
long long BloomBrain:: inversion() {
    int t = 0;
    for(int i = 0; i < numRooms; i++) {
        if(occu[i]) 
            temp[t++] = rooms[i];
    }
    return mergeSort(temp, a, 0, t-1);
}

long long BloomBrain:: mergeSort(int* temp, int* a, int l, int r) {
    if(r <= l) return 0;
    long long inv = 0;
    int mid;
    mid = (r+l)/2;
    inv += mergeSort(temp, a, l, mid);
    inv += mergeSort(temp, a, mid+1, r);
    int i = l, j = mid+1, k = l;

    while(i <= mid && j <= r) {
        if(temp[i] <= temp[j]) {
            a[k] = temp[i];
            k++, i++;
        }
        else {
            a[k] = temp[j];
            k++, j++;
            inv += mid-i+1;
        }
    }
    
    while(j <= r) {
        a[k] = temp[j];
        k++, j++;
    }
    while(i <= mid) {
        a[k] = temp[i];
        k++, i++;
    }
    for(i = l; i <= r; i++) temp[i] = a[i];

    return inv;
}
void BloomBrain:: join() {
    int room, s;
    cin >> s;
    for(room = numRooms-1; room >=0; room--) {
        if(rooms[room] == 0) 
            break;
    }
    rooms[room] = s;
    occu[room]++;
}

void BloomBrain:: leave() {
    int r;
    cin>>r;
    occu[r]=0;
    rooms[r] = 0;
}

int BloomBrain:: play() {
    return maxSum(0, numRooms-1);
}

int BloomBrain:: maxSum(int l, int r) {
    if(l == r) return rooms[l];
    int mid = (r+l)/2;
    return max(maxSum(l, mid), max(midSum(l, mid, r), maxSum(mid+1, r)));
}

int BloomBrain:: midSum(int l, int mid, int r) {
    int leftSum = INT32_MIN, rightSum = INT32_MIN;
    int i = mid, curSum = 0;
    while(i >= l) {
        curSum+=rooms[i];
        i--;
        leftSum = max(leftSum, curSum);
    }
    i = mid+1, curSum = 0;
    while(i <= r) {
        curSum+=rooms[i];
        i++;
        rightSum = max(rightSum, curSum);
    }
    return max(leftSum, max(rightSum, rightSum+leftSum));
}

int BloomBrain:: occupied() {
    occupancy = 0;
    for(int i = 0; i < numRooms; i++) 
        if(occu[i]) occupancy++;
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