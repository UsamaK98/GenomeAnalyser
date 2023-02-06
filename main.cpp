#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include "./nucleotides.hpp"
#include "./scaffold.hpp"
#include <chrono>
#include <vector>
using namespace std;

char* stringToCharArray(string str) {
  char* charArray = new char[str.length() + 1];
  strcpy(charArray, str.c_str());
  return charArray;
}

void readGenome(string fname, scaffold** s2, int* n, vector<char>& data){
    string line;
    //vector<char> data;
    ifstream file(fname);
    
    int c, i;
    c = 0;
    i = 0;
    scaffold* temp;
    scaffold* s = new scaffold[1];
    if (file.is_open()) {
      while (getline(file, line)) {
        if (line[0]=='>'){
          c=0;
          s[i].header=line;
          
          i++;
          
          temp = new scaffold[i];
          for (int j=0;j<i;j++)
            temp[j]=s[j];
          
          delete[] s;
          s = new scaffold[i+1];
          for (int j=0;j<i;j++)
            s[j]=temp[j];
          delete[] temp; 
          
        } else {
          char* temp = stringToCharArray(line);
          for (int k=0;k<81;k++)
            data.push_back(temp[k]);
          c++;
        }
        s[i-1].size=c;
        //cout << line << endl;
      }
      file.close();
  } else {
    cout << "Unable to open file" << endl;
  }


  *n=i;
  *s2=s;
  //return data;
}

void countNucleotides(vector<char>& str) {
  nucleotides c;
  for (unsigned long int i = 0; i<str.size(); ++i) {
    char t = str.at(i);
    switch (t) {
      case 'A':
        ++c.countA;
        break;
      case 'C':
        ++c.countC;
        break;
      case 'G':
        ++c.countG;
        break;
      case 'T':
        ++c.countT;
        break;
      default:
        break;
    }
  }
  c.printCount();
}

int main() {
    auto start = chrono::high_resolution_clock::now();
    string file = "human.txt";
    scaffold* scaffoldArray;
    int* numScaffolds = new int(0);
    vector<char> data; 
    readGenome(file, &scaffoldArray, numScaffolds, data);
    //char* charArray = stringToCharArray(line);
    //printf(charArray);
    countNucleotides(data);
    
    cout<<endl<<"The number of Scaffolds is: "<<*numScaffolds<<endl;
    for (int i=0; i<*numScaffolds;i++){
      cout<<"scaffold "<<i+1<<": "<<scaffoldArray[i].header<<"    size: "<<scaffoldArray[i].size<<endl;
    }

    //delete[] charArray;
    delete[] scaffoldArray;

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end - start);

    cout << "Total execution time: " << duration.count() << " seconds" << endl;

    return 0;
}
