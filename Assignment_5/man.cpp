#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class BloomBrain
{
    int *seraphic;
    int *roomStatus;
    int *filledRooms;
    int *temp_arr;
    int memcount;
    int roomcount;
    long long CalcTalk();
    long long mergeSort(int *, int *, int, int);
    long long merge(int *, int *, int, int, int);

public:
    BloomBrain(int);
    ~BloomBrain();
    long long Update(int);
    void Join(int);
    void Leave(int);
    int Occupied();
    int Play();
};

BloomBrain::BloomBrain(int n)
{
    seraphic = new int[n];
    roomStatus = new int[n];
    filledRooms = new int[n];
    temp_arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        seraphic[i] = 0;
        roomStatus[i] = 0;
    }
    memcount = 0;
    roomcount = n;
}

BloomBrain::~BloomBrain()
{
    delete[] seraphic;
    delete[] roomStatus;
    delete[] filledRooms;
    delete[] temp_arr;
    memcount = 0;
    roomcount = 0;
}

long long BloomBrain::CalcTalk()
{
    int j = 0;
    for (int i = 0; i < roomcount; i++)
        if (roomStatus[i] == 1)
        {
            filledRooms[j] = seraphic[i];
            temp_arr[j++] = 0;
        }

    long long res = mergeSort(filledRooms, temp_arr, 0, memcount - 1);

    return res;
}

long long BloomBrain::mergeSort(int *arr, int *temp_arr, int l, int r)
{
    int m = 0;
    long long talk = 0;
    if (r > l)
    {
        m = (r + l) / 2;
        talk += mergeSort(arr, temp_arr, l, m);
        talk += mergeSort(arr, temp_arr, m + 1, r);

        talk += merge(arr, temp_arr, l, m + 1, r);
    }

    return talk;
}

long long BloomBrain::merge(int *arr, int *temp_arr, int l, int m, int r)
{
    int x = l, y = m, z = l;
    long long talk = 0;

    while (x < m && y <= r)
    {
        if (arr[x] <= arr[y])
            temp_arr[z++] = arr[x++];
        else
        {
            temp_arr[z++] = arr[y++];
            talk += m - x;
        }
    }

    while (x < m)
        temp_arr[z++] = arr[x++];

    while (y <= r)
        temp_arr[z++] = arr[y++];

    for (int i = l; i <= r; i++)
        arr[i] = temp_arr[i];

    return talk;
}

long long BloomBrain::Update(int Q)
{
    for (int i = 0; i < roomcount; i++)
    {
        cin >> seraphic[i];
        if (Q == 0)
        {
            memcount++;
            roomStatus[i] = 1;
        }
    }

    return CalcTalk();
}

void BloomBrain::Join(int x)
{
    for (int i = roomcount - 1; i >= 0; i--)
        if (roomStatus[i] == 0)
        {
            seraphic[i] = x;
            memcount++;
            roomStatus[i] = 1;
            break;
        }
    return;
}

void BloomBrain::Leave(int i)
{
    if (roomStatus[i] == 1)
    {
        memcount--;
        roomStatus[i] = 0;
    }
    seraphic[i] = 0;
    return;
}

int BloomBrain::Occupied()
{
    return memcount;
}

int BloomBrain::Play()
{
    int guruVal = INT32_MIN, curVal = 0, maxSer = INT32_MIN;
    for (int i = 0; i < roomcount; i++)
    {
        curVal = max(curVal + seraphic[i], 0);
        guruVal = max(guruVal, curVal);
        maxSer = max(maxSer, seraphic[i]);
    }

    if (guruVal == 0)
        guruVal = maxSer;

    return guruVal;
}

int main()
{
    int N, Q, x;
    string s;

    cin >> N >> Q;
    BloomBrain Centre(N);

    for (int i = 0; i < Q; i++)
    {
        cin >> s;
        if (s == "update")
            cout << Centre.Update(i) << '\n';
        else if (s == "play")
            cout << Centre.Play() << '\n';
        else if (s == "leave")
        {
            cin >> x;
            Centre.Leave(x);
        }
        else if (s == "occupied")
            cout << Centre.Occupied() << '\n';
        else if (s == "join")
        {
            cin >> x;
            Centre.Join(x);
        }
    }

    return 0;
}