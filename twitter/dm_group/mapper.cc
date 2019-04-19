#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]){
  int n = atoi(argv[1]);  //for n gram
  string line;

  while(!cin.eof()){
    if(!cin.fail()){
      getline(cin, line);
      size_t found = line.find("text");
      //tweet found
      if(found != string::npos){
        stringstream in(line);
        string id;
        string colon;
        string tweet;
        in >> id;
        in >> colon;
        getline(in, tweet);

        //clean up rest of punctuation
        for(int i = 0, len = tweet.size(); i < len; i++){
          if(ispunct(tweet[i])){
            tweet.erase(i--, 1);
            len = tweet.size();
          }
        }

        unordered_map<string, int> m;
        //put each word into a vector
        vector<string> words;
        istringstream is(tweet);
        for(string s; is >> s; ){
          words.push_back(s);
        }
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
        //cout << tweet << endl;
      }
      //cout << line << endl;
    }
    else{cout << "Error: failed to read input";}
  }
  return 0;
}
