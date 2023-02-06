#include<iostream>
using namespace std;

struct nucleotides {
    int countA;
    int countC;
    int countG;
    int countT;

    nucleotides(){
        countA=countC=countG=countT=0;
    }

    void printCount(){
        cout << endl << "A: " << countA << endl;
        cout << "C: " << countC << endl;
        cout << "G: " << countG << endl;
        cout << "T: " << countT << endl;
    }
};