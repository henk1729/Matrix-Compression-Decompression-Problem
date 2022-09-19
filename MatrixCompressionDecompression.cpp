//HENK
#include<bits/stdc++.h>
#include<ctime>
#include<cstdlib>
using namespace std;

#define ll long long
#define forn(i, n) for(int i=0; i<(n); ++i)

//constants
#define MAX_SIZE 20
#define MIN_SIZE 0

void displayMatrix(vector<vector<ll>> matrix){
    //for empty vector
    if(matrix.size()==0){
        cout<<endl;
        return;
    }

    forn(i, matrix.size()){
        forn(j, matrix[0].size()){
            cout<<"  -- ";
        }
        cout<<" "<<endl<<"| ";
        forn(j, matrix[0].size()){
            cout<<matrix[i][j]<<" | ";
        }
        cout<<endl;
    }
    forn(j, matrix[0].size()){
        cout<<"  -- ";
    }
    cout<<endl;
}

bool sizeSubceeded(vector<vector<ll>> matrix, ll compressFactor){
    return (matrix.size()-compressFactor<MIN_SIZE);
}

bool sizeExceeded(vector<vector<ll>> matrix, ll decompressFactor){
    return (matrix.size()+decompressFactor>MAX_SIZE);
}

void compressMatrix(vector<vector<ll>> &matrix, ll compressFactor){
    ll newSize=matrix.size()-compressFactor;
    
    //deleting elements from current rows
    forn(i, newSize){
        forn(j, compressFactor){
            matrix[i].pop_back();
        }
    }

    //deleting current rows
    forn(i, compressFactor){
        matrix.pop_back();
    }
}

void decompressMatrix(vector<vector<ll>> &matrix, vector<vector<ll>> matrixRef, ll decompressFactor){
    ll oldSize=matrix.size(), newSize=matrix.size()+decompressFactor;

    //appending elements to current rows
    forn(i, oldSize){
        forn(index, decompressFactor){
            matrix[i].push_back(matrixRef[i][matrix.size()+index]);
        }
    }

    //appending new rows
    forn(i, decompressFactor){
        vector<ll> tempVector(newSize);
        forn(index, newSize) tempVector[index]=matrixRef[matrix.size()][index];
        matrix.push_back(tempVector);
    }
}

void generateMatrix(vector<vector<ll>> &matrix, vector<vector<ll>> &matrixRef){
    srand((signed)time(nullptr));

    //deleting old matrix
    matrix.clear();

    //random matrix initializer
    forn(i, MAX_SIZE){
        vector<ll> temp(MAX_SIZE);
        forn(j, MAX_SIZE){
            temp[j]=rand()%100;
            if(temp[j]<10) temp[j]+=10;
        }
        matrix.push_back(temp);
    }

    //matrix for reference
    matrixRef=matrix;
}

void choice(vector<vector<ll>> &matrix, vector<vector<ll>> matrixRef){
    cout<<"\nEnter your choice\n\n0. Generate matrix\n1. Display matrix\n2. Compress matrix\n3. Decompress matrix\n4. Exit\n\n";
    ll opt;
    cin>>opt;

    switch(opt){
        //generation
        case 0:
            generateMatrix(matrix, matrixRef);
            cout<<"\n>> Matrix generation complete.";
            cout<<"\n\nEnter 1 to view.\n";
            ll input;
            cin>>input;
            if(input==1) displayMatrix(matrix);
            break;
        //display
        case 1:
            displayMatrix(matrix);
            break;
        //compression
        case 2:
            cout<<"\nEnter compressing factor: ";
            ll cf;
            cin>>cf;
            if(sizeSubceeded(matrix, cf)){
                cout<<"\n!! Out of bound. Try entering a smaller factor.\n";
            }
            else{
                compressMatrix(matrix, cf);
                cout<<"\n>> Matrix compression complete.";
                cout<<"\n\nEnter 1 to view.\n";
                ll input;
                cin>>input;
                if(input==1) displayMatrix(matrix);
            }
            break;
        //decompression
        case 3:
            cout<<"\nEnter decompressing factor: ";
            ll df;
            cin>>df;
            if(sizeExceeded(matrix, df)){
                cout<<"\n!! Out of bound. Try entering a smaller factor.\n";
            }
            else{
                decompressMatrix(matrix, matrixRef, df);
                cout<<"\n>> Matrix decompression complete.";
                cout<<"\n\nEnter 1 to view.\n";
                ll input;
                cin>>input;
                if(input==1) displayMatrix(matrix);
            }
            break;
        //exit
        default:
            cout<<"\n>> Exit...";
            exit(0);
    }
    choice(matrix, matrixRef);
}

int main(){
    cout<<"^ ^ Welcome onboard ^ ^\n";

    vector<vector<ll>> matrix, matrixRef;
    generateMatrix(matrix, matrixRef);

    choice(matrix, matrixRef);
}