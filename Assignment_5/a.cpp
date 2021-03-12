#include <iostream>
#include <string>

using namespace std;

struct node{
    int sum;
};

struct segtree {
    node s[10005] = {};
    int size;
    node single(int v) {
        return {v};
    }
    node mer(node p, node q) {
        return {p.sum+q.sum};
    }
    void init(int n) {
        size=1;
        while(size<n) size *= 2;
    }

    void set(int i, int v, int x, int lx, int rx) {
        if(rx-lx == 1) {
            s[x] = single(v);
            return;
        }

        int m=(lx+rx)/2;

        if(i < m)
            set(i, v, 2*x+1, lx, m);
        else
            set(i, v, 2*x+2, m, rx);
        s[x] = mer(s[2*x+1], s[2*x+2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }
    node sum(int l, int r, int x, int lx, int rx) {
        if(l>=rx || lx>=r) return {0};
        if(rx<=r && lx>=l) return s[x];
        int m = (lx+rx)/2;
        return mer(sum(l,r,2*x+1,lx,m), sum(l, r, 2*x+2, m, rx));
    }
    node sum(int l,int r) {
        return sum(l, r, 0, 0, size);
    }
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

    private:
        int* rooms;
        int occupancy;
        int numRooms;
};


BloomBrain:: BloomBrain(int n) {
    rooms = new int[n];
    for(int  i =0; i<n;i ++) {
        rooms[i] = 0;
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
    for(int i = 0; i < numRooms; i++) {
        cin >> rooms[i];
        if(rooms[i] != 0) {
            occupancy++;
        }
    }
    //cout << occupancy <<" ";
    segtree st;
    st.init(2002);
    long long int ans = 0;
    int count[2002] = {};
    for(int i = 0;i < numRooms; i++) {
        if(rooms[i] == 0) continue;
        ans+=st.sum(1000+rooms[i] + 1, 2001).sum;
        //cout << ans <<" ";
        count[1000+rooms[i]]++;
        st.set(1000+rooms[i], count[1000+rooms[i]]);
    }
    return ans;
}

void BloomBrain:: join() {
    int room, s;
    cin >> s;
    for(room = numRooms-1; room >=0; room--) {
        if(rooms[room] == 0) 
            break;
    }
    rooms[room] = s;
    occupancy++;
}

void BloomBrain:: leave() {
    int r;
    cin>>r;
    if(rooms[r] != 0) occupancy--;
    rooms[r] = 0;
}

int BloomBrain:: play() {
    int maxSum = 0, currentMax = 0, maxSeraph = INT32_MIN;
    for(int i = 0; i < numRooms; i++) {
        currentMax = max(currentMax + rooms[i], 0);
        maxSum = max(maxSum, currentMax);
        maxSeraph = max(maxSeraph, rooms[i]);
    }
    if(maxSum == 0) maxSum = maxSeraph;
    return maxSum;
}

int BloomBrain:: occupied() {
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