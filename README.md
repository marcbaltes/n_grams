# N-Gram Finder
This program uses the MapReduce method to output n-grams in key-value pairs.  
- Map takes each n-gram in each message and creates a key-value pair for it and then outputs it to stdout.  
- Reduce takes the output from the map and combines the pairs with matching keys and updates their value accordingly. 

An n-gram "is a contiguous sequence of *n* items from a given sample of text or speech." 
--[Wikipedia](https://en.wikipedia.org/wiki/N-gram)  
This is currently implemented for:
- Twitter
	- Single tweets
	- Group messages
- GroupMe

## Twitter Implementation
After downloading your data you will have two files, one named **tweet.js** and the other named **direct-message-group.js**. 
Put the corresponding file into either the **tweets** folder or the **dm_group** folder.

## GroupMe Implementation
After downloading your data you should have a folder and in the folder there will be a file named **message.json**. 
Put this file in the **groupme** folder.

## Compiling
In terminal type:
```
g++ -o map mapper.cc  
g++ -o red reducer.cc  
cat filename.js(or.json) | ./map n | sort | ./red | sort -n -k n+1
```
> n is the number of n items you want to be displayed in the n-gram.  
> -n is just a compiler flag and should not be changed, but n+1 should be changed for n  

This will display the output of you n-grams in order from most used to least used
