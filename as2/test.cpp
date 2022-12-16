#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

bool wordLadder(string, string, const vector<string>&, vector<string>&);
int similar(string, string);
bool notUniqueWord(string, vector<string>&);

int main(int argc, char * argv[]){
    
    ifstream inFile;
    inFile.open(argv[1]);

    string word = argv[2];
    string wordFinal = argv[3];

    vector<string> words;
    vector<string> ladder;
    string tempStr;

    while(!inFile.eof()){
        inFile >> tempStr;
        if (inFile.eof()){
            break;
        }

        words.push_back(tempStr);
    }

    ladder.push_back(word);

    bool solution = wordLadder(word, wordFinal, words, ladder);

    cout << "----------------------------------------------------------------------------" << endl << endl;

    if (solution){
        for (int i = 0; i < ladder.size(); i++){
            cout << ladder[i] << endl;
        }
    }
    else{
        cout << "Solution Does Not Exist" << endl;
    }
}

bool wordLadder(string word, string wordFinal, const vector<string>& words, vector<string>& ladder){
    string currentWord;
    string pointless;
    static int counter = 0;
    //counter ++;

    for (int i = 0; i < words.size(); i++){
        currentWord = words[i];

        if (currentWord == wordFinal){
            for(std::string word : ladder)
                std::cout << word << std::endl;
            cout << wordFinal << endl;
            counter=0;
            return true;
        }

        if (similar(word,currentWord) == 4 && notUniqueWord(currentWord,ladder)){
            continue;
        
            //cout << currentWord << endl;
            ladder.push_back(currentWord);
            //cout << "counter: " << counter << endl;

            //cin >> pointless;
            counter++;
        }

        if(wordLadder(currentWord, wordFinal, words, ladder) == false){

            if(counter >= ladder.size()){
                cout<< "There is No Solution\n";
                exit(1);
            }

            for(int i=0;i<counter;i++) {
                ladder.pop_back();
            }

            //makes sure no words are missed on another run through
            i = 0;

        } 

        break;

    }

    return false;
}

int similar(string word, string currWord){
    int similarLetters = 0;
    const int wordSize = 5;

    for (int i = 0; i < wordSize; i++){
        if (currWord[i] == word[i]){
            similarLetters++;
        }
    }

    return similarLetters;
}

bool notUniqueWord(string currentWord, vector<string>& ladder){
    for (int i = 0; i < ladder.size(); i++){
        if (currentWord == ladder[i]){
            return true;
        }
    }

    return false;
}
