/**************************************************************************
 *  
 *  File:    CS19B045_A4.cpp
 *
 *  Purpose:    Implement Vector using template
 *
 *  Author:    Vishnu
 *
 *  Created:    Mon 29-February-2021 10:05:34
 *
 *  Last Modified:    Mon 29-February-2021 16:25:12
 *
 *  Changes:    - 
 *
 **************************************************************************/
#include <iostream>
#include <string>
#include <utility>
#include <sstream>

using namespace std;


template <class T> class Vector {

    public:
        Vector(size_t);
        Vector(size_t, T);
        Vector();
        ~Vector();
        void push(T);
        size_t capacity();
        size_t size();
        void pop();
        T front();
        T back();
        T operator[] (size_t);
        void qsort(size_t, size_t);
        void sort();

    private:
        T* vec;
        size_t totCapacity;
        size_t currentSize;

    protected:
        size_t partition(size_t, size_t);                               // Protected member partition
};

template <class T> 
Vector<T>:: Vector(size_t s) {                                           // Constructor with one argument
    vec = new T[s];
    currentSize = 0;                                                // Initialization
    totCapacity = s;
}

template <class T> 
Vector<T>:: Vector(size_t s, T x) {                                  // Constructor overloading with 2 arguments
    vec = new T [s];
    for(size_t i = 0; i < s; i++) vec[i] = x;
    currentSize = s;
    totCapacity = s;
}

template <class T> 
Vector<T>:: Vector() {                                           // Constructor with no arguments
    vec = new T;
    currentSize = 0;
    totCapacity = 1;
}

template <class T> 
Vector<T>:: ~Vector() {                                      // Destructor for deallocating memory
    delete[] vec;
    vec = NULL;
    currentSize = 0;
    totCapacity = 0;
}

template <class T> 
void Vector<T>:: push(T x) {

    if(currentSize == totCapacity) {                    // Copying to larger array when size equals capacity

        T* temp = new T[2*totCapacity];

        for(size_t i = 0; i < currentSize; i++) {
            temp[i] = vec[i];
        }

        delete[] vec;                               // Deleting the old array
        vec = temp;
        temp = NULL;
        totCapacity *= 2;
    }
    vec[currentSize] = x;                                   // Pushing the new element
    currentSize++;
}

template <class T> 
void Vector<T>:: pop() {                                     // Pop
    if(currentSize)
    currentSize--;
}

template <class T> 
T Vector<T>:: front() {                                          // Front
    if(currentSize == 0) return -1;
    return vec[0];                                  // Returns the first element
}

template <class T> 
T Vector<T>:: back() {                                           // Back
    if(currentSize == 0) return -1; 
    return vec[currentSize-1];                      // Returns the last element
}

template <class T> 
T Vector<T>:: operator[](size_t s) {
    if(s >= currentSize) return -1;
    return vec[s];
}

template <class T> 
size_t Vector<T>:: capacity() {                         // Return capacity
    return totCapacity;
}

template <class T> 
size_t Vector<T>:: size() {                                     // Return size
    return currentSize;
}

template <class T> 
void Vector<T>:: sort() {
    if(currentSize>0) 
        qsort(0, currentSize-1);                // Call helper function qsort()

    for(size_t i = 0; i < currentSize; i++)             // Print the sorted array
        cout << vec[i] << " ";
    cout << endl;
}

template <class T> 
void Vector<T>:: qsort(size_t l, size_t r) {
    if(l>=r || l < 0 || r >= currentSize)                               // Return when out of bound
        return;               
    size_t pivot = partition(l, r);                         // Partition around the first element

    if(pivot-1>l) qsort(l, pivot-1);                    // Sort left subarray
    if(pivot+1<r) qsort(pivot+1, r);                    // Sort right subarray
}

template <class T> 
size_t Vector<T>:: partition(size_t l, size_t r) {
    size_t i = l+1, j;
    T pivot = vec[l];                                       // Pivot is the first element
    for(j = l+1; j <= r; j++) {
        if(vec[j] < pivot) {                                // Swap all inversions
            T temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
            i++;
        }
    }
    i--;                                
    vec[l] = vec[i];
    vec[i] = pivot;
    return i;                                   // Return position of partitioning element
}

template <class T>
void choice(Vector<T> &V) {                             // Function to get user choice

    int n;
    cin >> n;
    string s;
    T x;
    size_t siz;

    while(n--) {
        cin >> s;
        if(s == "push") {
            cin >> x;
            V.push(x);
        }
        else if(s == "pop") {
            V.pop();
        }
        else if(s == "front") {
            cout << V.front() << endl;
        }
        else if(s == "back") {
            cout << V.back() << endl;
        }
        else if(s == "capacity") {
            cout << V.capacity() << endl;
        }
        else if(s == "size") {
            cout << V.size() << endl;
        }
        else if(s == "sort") {
            V.sort();
        }
        else if(s == "element") {
            cin >> siz;
            cout << V[siz] << endl;
        }
    }
}

int main() {
    string s;
    size_t siz = 0;
    int x = -1;
    stringstream ss;
    char st[50];
    cin.getline(st, 50);                        // First line of input
    ss<<st;
    ss>>s>>siz>>x;
    if(siz > 0) {
        if(x < 0) {                             // If only size is given in input
            Vector<int> V(siz);
            choice(V);
        }
        else {
            Vector<int> V(siz, x);                  // If both size and element are given as inputs
            choice(V);
        }
    }
    else {
        Vector<int> V;                              // If no initial parameter is given
        choice(V);
    }
}