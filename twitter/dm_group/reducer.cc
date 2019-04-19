////////////////////////////////////////////////////////////////////////////////////////
// Author: Marc Baltes
// File: reducer.cc
// Date: 04/16/2019
// Description: Takes the output from the mapper which is in the form: "key value".
//  Then for each key, it checks if it is in the new hashmap and if it is then that
//  key's value will be increased, if not it will be added into the map.
////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>  //lookup is O(n)
#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
// Function: findAndReplaceAll
// Parameters: the string you are using; substring to find; substring to replace
// Desc: Goes through the entire string and replaces all instances of the toSearch string
//  with the replaceStr
////////////////////////////////////////////////////////////////////////////////////////
void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
{
	// Get the first occurrence
	size_t pos = data.find(toSearch);

	// Repeat till end is reached
	while( pos != std::string::npos)
	{
		// Replace this occurrence of Sub String
		data.replace(pos, toSearch.size(), replaceStr);
		// Get the next occurrence from the current position
		pos =data.find(toSearch, pos + replaceStr.size());
	}
}

////////////////////////////////////////////////////////////////////////////////////////
// Function: main
// Parameters: standard parameters for reading command line arguments
// Desc: Takes all the key-value pairs from mapper.cc and combines all the same keys
//  into one pair with a total value for that key
////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]){
  string line;
  string n_gram;
  int count;
  unordered_map<string, int> m;
  while(!cin.eof()){
    getline(cin, line);
    if(!cin.fail()){
      istringstream in(line);
      in >> n_gram;
      //gets rid of special string that was
      //added in the mapper.cc file: more information
      //on that there
      findAndReplaceAll(n_gram, "&&&%%%$#", " ");

			//clean up rest of punctuation
			for(int i = 0, len = n_gram.size(); i < len; i++){
				if(ispunct(n_gram[i])){
					n_gram.erase(i--, 1);
					len = n_gram.size();
				}
			}
			n_gram.pop_back();	//delete extra space

      in >> count;
      unordered_map<string, int>::iterator it = m.find(n_gram);

      //if key exists then increase its count
      if(it != m.end()){
        int count = it -> second;
        count++;
        it -> second = count;
      }
      //else add it to the map
      else{
        m.insert(make_pair(n_gram, count));
      }
    }
  }

  //output map
  unordered_map<string, int>::iterator it = m.begin();
  for(it; it != m.end(); it++){
		string word = it -> first;
		//get rid of links
		if(word.find("http") != 0){
			cout << it -> first << "\t" << it -> second << endl;
		}
  }
  return 0;
}
