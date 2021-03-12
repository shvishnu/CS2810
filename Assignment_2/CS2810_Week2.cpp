#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

class Matrix
{
protected:
    int n, m;
    int **M;

public:
    Matrix(int, int);
    ~Matrix();

    void GetMatrix();
    int binarySearch(int, int);
    int *matrixSearch(int);
};

Matrix::Matrix(int n, int m)
{
    this->n = n;
    this->m = m;
    M = new int *[n];
    for (int i = 0; i < n; i++)
    {
        M[i] = new int[m];
        for (int j = 0; j < m; j++)
            M[i][j] = 0;
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < n; ++i)
        delete[] M[i];
    delete[] M;
}

void Matrix::GetMatrix()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> M[i][j];
        }
    }
    return;
}

int Matrix::binarySearch(int x, int k)
{
    int index = -1;
    int low = 0, high = m - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (M[k][mid] <= x)
        {
            index = mid;
            low = mid + 1;
        }
        else
            high = mid - 1;
    }

    return index;
}

int *Matrix::matrixSearch(int x)
{
    int *arr = new int[2];
    arr[0] = -1;
    arr[1] = -1;

    for (int i = 0; i < n; i++)
    {
        int index = -1;
        int low = 0, high = m - 1, mid;
        while (low <= high)
        {
            mid = low + (high - low) / 2;
            if (M[i][mid] == x)
            {
                if (M[i][mid] == 0 || M[i][mid - 1] < x)
                {
                    index = mid;
                    break;
                }
                else
                {
                    high = mid - 1;
                }
            }
            else if (M[i][mid] < x)
                low = mid + 1;
            else
                high = mid - 1;
        }
        if (index != -1)
        {
            arr[0] = i;
            arr[1] = index;
            break;
        }
    }
    return arr;
}

class MatrixMedian : public Matrix
{
public:
    MatrixMedian(int, int);
    int upperBound(int, int);
    int findMedian();
};

MatrixMedian::MatrixMedian(int n, int m) : Matrix(n, m)
{
}

int MatrixMedian::upperBound(int x, int k)
{
    int index = binarySearch(x, k) + 1;
    if (index == m)
        index = -1;
    return index;
}

int MatrixMedian::findMedian()
{
    int minv = INT_MAX;
    int maxv = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        minv = min(M[i][0], minv);
        maxv = max(M[i][m - 1], maxv);
    }

    int mid, req_count = (n * m + 1) / 2;
    while (minv < maxv)
    {
        mid = minv + (maxv - minv) / 2;
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            int val = upperBound(mid, i);
            cnt += (val == -1) ? m : val;
        }
        if (cnt < req_count)
            minv = mid + 1;
        else
            maxv = mid;
    }
    return minv;
}

int main()
{
    int n, m, x, k, Q;
    string query;
    cin >> n >> m;

    MatrixMedian mat(n, m);
    mat.GetMatrix();

    cin >> Q;

    for (int i = 0; i < Q; i++)
    {
        cin >> query;
        if (query == "BS")
        {
            cin >> x >> k;
            cout << mat.binarySearch(x, k) << '\n';
        }
        else if (query == "MS")
        {
            cin >> x;
            int *arr = mat.matrixSearch(x);
            cout << arr[0] << ' ' << arr[1] << '\n';
        }
        else if (query == "Median")
        {
            x = mat.findMedian();
            cout << x << '\n';
        }
        else
            cout << "Invalid Query! \n";
    }

    return 0;
}