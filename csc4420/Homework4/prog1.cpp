// Reverses the bytes of a file so that the last is first and the first is last
// Written by Caleb Latimer

#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<string>
using namespace std;

int main(){
ifstream in; // For reading the file
ofstream out; // For outputting the file reversed by bytes
vector<char> text;
vector<string> temptext;
string temp;
in.open("testtext.txt");
if(!(in.is_open())){
  cout << "Failed to open input file" << endl; // error checking for file opening
  exit(1);
}

else{
  while(in >> temp){
      temptext.push_back(temp); // read text word by word into a vector
    }
  }
  in.close(); // close input stream
    for(vector<string> :: iterator i = temptext.begin(); i!=temptext.end();++i){
      temp = *i; // set a temp string to a word from the vector
      for(int k =0; k < temp.length(); k++){
          text.insert(text.begin(),temp[k]); // reverse that word and store it character by character in a char vector, to reverse by byte
        }
	  text.insert(text.begin(), ' '); // insert a space after each word
      }
    out.open("testtext.txt", ios::trunc);
    if(!(out.is_open())){
      cout << "Failed to open output file \n";
      exit(2);
    }
    else{
      for(vector<char> :: iterator i = text.begin(); i!=text.end();++i){
          out << *i; // outputs to file the new text
    }
  }
    out.close();
    return 0;
}
