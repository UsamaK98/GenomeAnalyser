#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdio.h>
#include "./nucleotides.hpp"
#include "./scaffold.hpp"
#include <chrono>
#include <vector>
using namespace std;

//function for converting a string to a character array after reading from file
char* stringToCharArray(string str) {
  char* charArray = new char[str.length() + 1];
  strcpy(charArray, str.c_str());
  return charArray;
}

//function for reading the genome file and storing data in a character array after analyzing the genome sequence
//... and scaffold structure
void analyzeGenome(string fname, scaffold** s2, int* n, vector<char>& data){
    string line;
    ifstream file(fname);
    
    int c, i;
    c = 0;
    i = 0;
    scaffold* temp;
    scaffold* s = new scaffold[1];
    if (file.is_open()) {
      while (getline(file, line)) {
        int lineSize = line.length();
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
          for (int k=0;k<lineSize;k++) {
            data.push_back(temp[k]);
          	c++  ;
          }
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
}

//a function which takes the genome sequence character array and counts the number of each type of nucleotide present
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
      case 'N':
        ++c.countN;
        break;
      default:
        break;
    }
  }
  c.printCount();
}

//function for finding largest scaffold
scaffold findLargest(scaffold* sArr, int s) {
  int max = 0;
  scaffold result;
  for (int i=0; i<s; i++) {
    if (sArr[i].size>max) {
      result=sArr[i];
      max=sArr[i].size;
    }
  }
  return result;
}

//function for finding smallest scaffold
scaffold findSmallest (scaffold* sArr, int s) {
  int min = 2147483646;
  scaffold result;
  for (int i=0; i<s; i++) {
    if (sArr[i].size<min) {
      result=sArr[i];
      min=sArr[i].size;
    }
  }
  return result;
}

//following function finds the average scaffold length
int findAvergeLength(scaffold* sArr, int s) {
  long int totalLen = 0;
  for (int i=0;i<s;++i){
    totalLen+=sArr[i].size;
  }
  return totalLen/(long double)s;
}

//following function finds the percentage of GC nucleotides present in the genome, index "0" correspons to "G"
void findPercentage(vector<char>& data, double* arr) {
  
  int totalG = 0;
  int totalC = 0;
  
  for (long unsigned int i = 0; i<data.size(); ++i) {
    char a = data.at(i);
    switch(a){
      case 'G': totalG++; break;
      case 'C': totalC++; break;
    };
  }

  arr[0]=((long double)totalG/data.size())*100;
  arr[1]=((long double)totalC/data.size())*100;

}

int main(int argc, char** argv) {
    
    //Variable declarations and assignments
    string file(argv[1]);
    string flag = argv[2];
    scaffold largest, smallest;
    scaffold* scaffoldArray;
    int* numScaffolds = new int(0);
    vector<char> data; 
    double* percents = new double [2];


    //calling the main file reading and genome analyzer function
    analyzeGenome(file, &scaffoldArray, numScaffolds, data);
    
    //Control structure for exectuing sub-problems based on flag provided
    if (flag=="a"||flag=="A") {

      //following segement finds the largest and smallest scaffolds
      largest = findLargest(scaffoldArray, *numScaffolds);
      smallest = findSmallest(scaffoldArray, *numScaffolds);

      //the following lines print numbers of scaffolds, largest and smallest scaffold headers and respective sizes
      cout<<endl<<"The number of Scaffolds is: "<<*numScaffolds<<endl;
      cout<<"The largest scaffold is: "<<largest.header<<" with size = "<<largest.size<<endl;
      cout<<"The smallest scaffold is: "<<smallest.header<<" with size = "<<smallest.size<<endl;

      //following line finds the average scaffold length and outputs it
      cout<<"The average scaffold size is: "<<findAvergeLength(scaffoldArray, *numScaffolds)<<endl;

    } else if (flag=="b"||flag=="B") {

      //following lines find and print the GC content of the genome sequence
      findPercentage(data, percents);
      cout<<"Percentage of G content is "<<percents[0]<<"% "<<endl;
      cout<<"Percentage of C content is "<<percents[1]<<"% "<<endl;

      //following codeblock counts the number of each type of nucleotides and finds the execution time of that function as well
      auto start = chrono::high_resolution_clock::now();
      countNucleotides(data);
      auto end = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::seconds>(end - start);
      cout << "Total execution time for funtion to count nucleotides was: " << duration.count() << " seconds" << endl;

    } else {
      cout<<endl<<"[ERROR] Invalid flag entered"<<endl;
    }
   
    /* //this loop prints all the scaffold headers and their sizes
    for (int i=0; i<*numScaffolds;i++){
      cout<<"scaffold "<<i+1<<": "<<scaffoldArray[i].header<<"    size: "<<scaffoldArray[i].size<<endl;
    } */

    //dynamic memory deallocation
    delete numScaffolds;
    delete[] scaffoldArray;

    return 0;
}
