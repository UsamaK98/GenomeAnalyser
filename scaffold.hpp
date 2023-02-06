#include<string>
using namespace std;

struct scaffold {
    int size;
    string header;

    scaffold(){
        size=0;
    }

    void operator = (const scaffold &s ) { 
        size=s.size;
        header=s.header;
    }
};