#include <iostream>
#include <stdlib.h> 
using namespace std;

template <class T> class JaggedArray {
    public:
    // CONSTRUCTORS, ASSIGNMNENT OPERATOR, & DESTRUCTOR
    JaggedArray(int num_b);
    JaggedArray(const JaggedArray& ja) { this->copy(ja); }
    JaggedArray& operator=(const JaggedArray& ja); 
    ~JaggedArray(); 

    // ACCESSORS
    int numElements() const;
    int numBins() const;
    int numElementsInBin(int n);
    T getElement(int e, int b);
    bool isPacked() const;

    // MODIFIERS
    void addElement(int n, T c);
    void removeElement(int e, int b);
    void unpack();
    void pack();
    void clear();
    void print();

    private:
    void copy(const JaggedArray<T>& ja);
    void delete_things();

    int num_elements;
    int num_bins;
    int* counts;
    T** unpacked;
    int* offsets;
    T* packed;
};

template <class T> JaggedArray<T>::JaggedArray(int num_b) {
    num_bins = num_b;
    num_elements = 0;
    unpacked = new T*[num_b];
    counts = new int[num_b];
    for (int i=0; i<num_b; i++) {
        counts[i]=0;
    }
    packed=NULL;
    offsets=NULL;
}

template <class T> void JaggedArray<T>::copy(const JaggedArray& ja) {
  num_bins = ja.num_bins;
  num_elements = ja.num_elements;
  if (ja.isPacked()) {
    counts = NULL;
    unpacked = NULL;
    offsets = new int[num_bins];
    packed =  new T[num_elements];
    for (int i=0; i<num_bins; i++) {
        offsets[i] = ja.offsets[i];
    }
    for (int i=0; i<num_elements; i++) {
        packed[i] = ja.packed[i];
    }
  } else {
    packed = NULL;
    offsets = NULL;
    counts = new int[num_bins];
    unpacked = new T*[num_bins];
    for (int i=0; i<num_bins; i++) {
        counts[i] = ja.counts[i];
    }
    for (int j=0; j<num_bins; j++) {
        if (counts[j]>0) {
            unpacked[j] = new T[counts[j]];
            for (int k=0; k<counts[j]; k++) {
                unpacked[j][k] = ja.unpacked[j][k];
            }
        } else {
            unpacked[j] = NULL;
        }
    }
  }
}

template <class T> JaggedArray<T>& JaggedArray<T>::operator=(const JaggedArray& ja) {
    if (this != &ja) {
        delete_things();
        copy(ja);
    }
    return *this;
}

template <class T> JaggedArray<T>::~JaggedArray() {
    delete_things();
}

template <class T> void JaggedArray<T>::delete_things() {
     if (!this -> isPacked()) {
        for (int i=0; i<num_bins; i++) {
            if (counts[i]>0) {
            delete[] unpacked[i];
            }
        }
        delete [] counts;
        delete[] unpacked;
    } else {
        delete [] offsets;
        delete [] packed;
    }
}

template <class T> int JaggedArray<T>::numElements() const { return num_elements; }
template <class T> int JaggedArray<T>::numBins() const { return num_bins; }

template <class T> int JaggedArray<T>::numElementsInBin(int n) { 
    if (!this -> isPacked()) { // if unpacked just access counts at the bin number
        return counts[n];
    } 
    this -> unpack(); // otherwise unpack, get counts[n], and repack
    int x = counts[n];
    this -> pack();
    return x;
} 

template <class T> T JaggedArray<T>::getElement(int e, int b) { // same ideology as numElementsInBin
    if (!this -> isPacked()) {
        return unpacked[e][b]; 
    } 
    this -> unpack();
    T y = unpacked[e][b];
    this -> pack();
    return y;
} 

template <class T> bool JaggedArray<T>::isPacked() const{
    return (unpacked == NULL); 
}

template <class T> void JaggedArray<T>::addElement(int n, T c) {
    if (this -> isPacked()) {
        cerr << "Cant edit while packed";
        exit(1);
    }
    int size = counts[n];
    T *new_unpacked = new T[size+1];
    num_elements+=1;
    counts[n]+=1;
    for (int i=0; i<counts[n]-1; i++) { // putting all elements into new array in heap
        new_unpacked[i] = unpacked[n][i];
    }
    new_unpacked[counts[n]-1] = c; // adding new element
    if (counts[n]>1) {
        delete [] unpacked[n]; // delete old array pointer
    }
    unpacked[n] = new_unpacked;
}
    
template <class T> void JaggedArray<T>::removeElement(int e, int b) {
    if (this -> isPacked()) {
        cerr << "Cant edit while packed";
        exit(1);
    }
    int size = counts[b];
    if (size==1) {
        delete [] unpacked[b];
    } else {
        T *new_unpacked = new T[size-1];
        num_elements-=1;
        int index=0;
        int i=0;
        while (i<counts[b]) { // putting elements into new array except the called element
            if (i!=e) {
                new_unpacked[index] = unpacked[b][i];
                index++;  
            }
            i++;
        }
        delete [] unpacked[b]; // delete old array pointer
        unpacked[b] = new_unpacked;
    }
    counts[b]=size-1;
}

template <class T> void JaggedArray<T>::clear() {
    num_elements=0;
    if (!this -> isPacked()) {
        for (int i=0; i<num_bins; i++) {
            if (counts[i]>0) {
            delete[] unpacked[i];
            unpacked[i]=NULL;
            }
        }
        for (int i=0; i<num_bins; i++) {
            counts[i]=0;
        }
    } else {
        delete[] packed;
        delete[] offsets;
        packed=new T[0];
        offsets=new int[num_bins];
    }
} 

template <class T> void JaggedArray<T>::print() {
    if (!this -> isPacked()) {
        int max=0;
        for (int x=0; x<num_bins; x++) {
            if (max < counts[x]) {
                max = counts[x];
            }
        }
        cout << "unpacked JaggedArray" << endl;
        cout << "  num_bins: " << to_string(num_bins) << endl;
        cout << "  num_elements: " << to_string(num_elements) << endl;
        cout << "  counts:  ";
        for (int i=0; i<num_bins; i++) {
            cout << to_string(counts[i]) << " ";
        }
        cout << endl << "  values:  ";
        for (int j=0; j<max; j++) {
            if (j != 0) {
                cout << "           ";
            }
            for (int k=0; k<num_bins; k++) {
                if(counts[k]==0) {
                    cout << "  ";
                } else {
                    if (counts[k] > j) {
                        cout << unpacked[k][j] << " ";
                    } else if (counts[k] <= j) {
                        cout << "  ";
                    }
                }
            }
            cout << endl;
        }
        cout << endl;
    } else {
        cout << "packed JaggedArray" << endl;
        cout << "  num_bins: " << numBins() << endl;
        cout << "  num_elements: " << numElements() << endl;
        cout << "  offsets:  ";
        for (int i=0; i<num_bins; i++) {
            cout << offsets[i] << " ";
        }
        cout << endl << "  values:   ";
        for (int j=0; j<num_elements; j++) {
            cout <<packed[j]<< " ";
        }
        cout << endl;
    } 
}

template <class T> void JaggedArray<T>::pack() {
    if (this -> isPacked()) {
        cerr << "Cant pack while packed";
        exit(1);
    }
    int x = 0;
    packed = new T[num_elements];
    for (int i=0; i<num_bins; i++) {
        if (counts[i]!=0) {
            for (int j=0; j<counts[i]; j++) {
                packed[x]=unpacked[i][j];
                x++;
            }
        }
    }
    x = 0;
    offsets = new int[num_bins];
    for (int i=0; i<num_bins; i++) {
        if (i==0) {
            offsets[i]=0;
        } else {
            x = counts[i-1];
            offsets[i]=offsets[i-1]+x;
        }
    }
    for (int i=0; i<num_bins; i++) {
        if (counts[i]>0) {
            delete[] unpacked[i];
        }
    }
    delete [] counts;
    delete [] unpacked;
    unpacked = NULL;
    counts = NULL;
}

template <class T> void JaggedArray<T>::unpack() {
    if (!this -> isPacked()) {
        cerr << "Cant unpack while unpacked";
        exit(1);
    }
    int x=0;
    int index=0;
    unpacked = new T*[num_bins];
    counts = new int[num_bins];
    for (int i=0; i<num_bins; i++) {
        if (i!=num_bins-1) {
            x = offsets[i+1]-offsets[i];
        } else {
            x=num_elements-offsets[i]; 
        }  
        counts[i] = x; 
        if (x!=0) {
            unpacked[i] = new T[x];
        }
    }
    for (int j=0; j<num_bins; j++) {
        if (counts[j]!=0) {
            for (int k=0; k<counts[j]; k++) {
                unpacked[j][k]=packed[index];
                index++;
            }
        }
    }    
    delete [] packed;
    delete [] offsets;
    packed = NULL;
    offsets = NULL;
}