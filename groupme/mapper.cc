#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]){
  int n = atoi(argv[1]);  //for n gram
  string message = "";
  int state = 0;
  char c = 'a';
  while(!cin.eof()){
    if(state == 0){
      c = cin.peek();
      if(c == '"'){state = 1;}
      cin.get();
    }
    if(state == 1){
      c = cin.peek();
      if(c == 't'){state = 2;}
      else{state = 0;}
      cin.get();
    }
    if(state == 2){
      c = cin.peek();
      if(c == 'e'){state = 3;}
      else{state = 0;}
      cin.get();
    }
    if(state == 3){
      c = cin.peek();
      if(c == 'x'){state = 4;}
      else{state = 0;}
      cin.get();
    }
    if(state == 4){
      c = cin.peek();
      if(c == 't'){state = 5;}
      else{state = 0;}
      cin.get();
    }
    //message found
    if(state == 5){
      cin.get();  //"
      cin.get();  //:
      state = 6;
    }
    //start parsing message
    if(state == 6){
      c = cin.peek();
      if(c == '"'){state = 7;}
      cin.get();
    }
    if(state == 7){
      c = cin.peek();
      if(c != '"'){message += c;}
      else{state = 8;}
      cin.get();
    }
    if(state == 8){
      c = cin.peek();
      if(c == '"'){message += c; state = 7;}
      else{state = 9;}
    }
    if(state == 9){
      //clean up rest of punctuation
      for(int i = 0, len = message.size(); i < len; i++){
        if(ispunct(message[i])){
          message.erase(i--, 1);
          len = message.size();
        }
      }

      unordered_map<string, int> m;
      //put each word into a vector
      vector<string> words;
      istringstream is(message);
      for(string s; is >> s; ){
        words.push_back(s);
      }
      //generate n_grams
      for(int i = 0; i < words.size(); i++){
        string n_gram = "";
        for(int j = i; j < i+n; j++){
          if(j < words.size()){
            //so I add this weird string so the reducer knows what
            //a space is because in the slides, juedes just does in >> text
            //but that checks for whitespace and there are spaces inbetween Words
            //if n > 1 so i replace them with this and then in the reducer
            //i find this sub string and replace it with a space
            n_gram += words[j] + "&&&%%%$#";
          }
        }
        //find key
        unordered_map<string, int>::iterator it = m.find(n_gram);
        int count = 1;
        if(it != m.end()){
          count++;
          it -> second = count;
        }
        else{
          m.insert(make_pair(n_gram, count));
        }
        cout << n_gram << "\t" << count << endl;
      }
      message = "";
      state = 0;
    }
  }
}
