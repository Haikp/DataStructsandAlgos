/******************************************
 * takes in a given dictionary
 * takes in two words of which are in the dictionary
 * attempt to make a connection between the two words by finding another word that differs by one letter
 * constantly change the word by one letter until the final word is achieved
 * if a list of solution is found, cout the entire list of words to get from point A to point B
 * else, notify that there is no solution
******************************************/
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

bool wordLadder(string, string, const vector<string>&, vector<string>&);
int similar(string, string);
bool notUniqueWord(string, vector<string>&);

int main(int argc, char * argv[]){
    
    //open word dictionary
    ifstream inFile;
    inFile.open(argv[1]);

    //insert the starting word
    string word;
    //insert the final word
    string wordFinal;

    cin >> word;
    cin >> wordFinal;

    vector<string> words;
    vector<string> ladder;
    string tempStr;

    //insert dictionary in to words vector
    while(!inFile.eof()){
        inFile >> tempStr;
        if (inFile.eof()){
            break;
        }

        words.push_back(tempStr);
    }

    //edge case: push in first word to the ladder
    ladder.push_back(word);

    //call recursive function wordLadder
    bool solution = wordLadder(word, wordFinal, words, ladder);

    //if a solution is found by the function
    if (solution){
        //cout the entire list for the answer
        for (int i = 0; i < ladder.size(); i++){
            cout << ladder[i] << endl;
        }
    }
    //else cout no solution
    else{
        cout << "Solution Does Not Exist" << endl;
    }
}

/**********************************************
 *  wordLadder
 *      recursive function
 *      find a solution given a dictionary of words
 *      with the starting word, attempt to find the wordFinal by only swapping one letter at a time
 *      if a path of words lead to a dead end, backtrack the ladder to find another path of words
 *      if a solution is found, return the list of correct words
 *      if a solution is not found, or when the ladder is empty meaning no possible solutions, return false
**********************************************/ 
bool wordLadder(string word, string wordFinal, const vector<string>& words, vector<string>& ladder){
    string currentWord;
    string pointless;

    //loop through dictionary of words with one letter different
    for (int i = 0; i < words.size(); i++){
        currentWord = words[i];

        //if the word found is similar to the previous word by 4 letters...
        if (similar(word, currentWord) >= 4){

            //cin >> pointless;

            //if wordFinal has been found, return
            if (currentWord == wordFinal){
                ladder.push_back(wordFinal);
                return true;
            }

            //check if the word is unique within the ladder
            if (notUniqueWord(currentWord, ladder)){
                continue;
            }

            //insert the word into the ladder solution
            ladder.push_back(currentWord);

            //call the recursive function for the next word
            bool solution = wordLadder (currentWord, wordFinal, words, ladder);

            //if the solution is found, end case where wordFinal is found...
            if (solution){
                //continuously return true until recursive function ends
                return true;
            }

            //if the solution is false...
            if (solution == false){
                //if the ladder is empty, break out of the function
                if (ladder.size() == 0){
                    break;
                }

                //move back the ladder iterator back once
                ladder.pop_back();
                //attempt to look for a different word for the solution
                continue;
            }
        }
    }

    //return false as there are no possible words left in the dictionary
    return false;
}

/**********************************************
 *  similar
 *      parameters of a word, and the currentWord being compared
 *      every word is five letters long
 *      compare the two words, incrementing similarLetters if they have the same letter in the same location
 *      return the amount of similar letters
**********************************************/ 
int similar(string word, string currentWord){
    int similarLetters = 0;
    const int wordSize = 5;

    //compare word to the currentWord
    for (int i = 0; i < wordSize; i++){
        //if the word has the same letter in the same location of the word...
        if (currentWord[i] == word[i]){
            //increment the amount of similarLetters
            similarLetters++;
        }
    }

    //return amount of similarLetters
    return similarLetters;
}

/**********************************************
 *  notUniqueWord
 *      iterate through the current solution list, or the ladder
 *      check if the currentWord already exists in the ladder
 *      if it does, return true, else return false
**********************************************/ 
bool notUniqueWord(string currentWord, vector<string>& ladder){
    //iterate through the ladder
    for (int i = 0; i < ladder.size(); i++){
        //if the currentWord already exists in the ladder...
        if (currentWord == ladder[i]){
            //return true
            return true;
        }
    }

    //else return false
    return false;
}
