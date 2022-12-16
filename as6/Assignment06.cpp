/******************************************
 * My Name is   : Kelvin Do
 * My NSHEID is : 2001770482
 * My Email is  : dok7@unlv.nevada.edu
 * Assignment06.cpp Does the Following: 
 * Open up a binder of recipes
 * determine the budget avaliable, and what recipes can be made within the budget
 * cout recipes that can be made within a binder in order from cheapest to most expensive
******************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
using namespace std;

void uppercaseBinder(string &);

int main()
{
    ifstream inFile;
    string binderName;
    cout << "Enter binder name: ";
    cin >> binderName;
    cout << endl;
    inFile.open(binderName);

    string fileData;
    getline(inFile, fileData);
    //determine the amount of binders of recipes
    int totalBinders = stoi(fileData);

    //map of ingredients tied to its price
    unordered_map<string, int> ingredientPrice;
    //total ingredients in a binder
    int totalIngredients = 0;
    //total recipes in a binder
    int totalRecipes = 0;
    //budget limit on how much can be spent
    int budget = 0;

    vector<string> affordableRecipes;
    vector<int> recipePrice;
    string recipeName;
    string ingredient;
    int price = 0;
    //amount of the ingredient needed
    int amount = 0;

    //search through each binder
    for (int i = 0; i < totalBinders; i++)
    {
        int totalRecipeCost = 0;
        //define the name of the binder currently being searched
        getline(inFile, binderName);
        uppercaseBinder(binderName);
        cout << binderName << endl
             << "-------------------------------------" << endl;
        inFile >> totalIngredients >> totalRecipes >> budget;
        getline(inFile, fileData);

        //loop through the ingredient list
        for (int j = 0; j < totalIngredients; j++)
        {
            inFile >> ingredient >> price;
            //map the ingredient to its price
            ingredientPrice[ingredient] = price;
        }

        //move over to the next line of data, skip the \n in a file
        getline(inFile, fileData);

        //loop through the amount of recipes
        for (int j = 0; j < totalRecipes; j++)
        {
            getline(inFile, recipeName);
            //get totalIngredients needed for the current recipe
            inFile >> totalIngredients;
            //move over to the next line of data, skip the \n in a file
            getline(inFile, fileData);

            int recipeCost = 0;

            //loop through each ingredient
            for (int k = 0; k < totalIngredients; k++)
            {
                inFile >> ingredient >> amount;
                //determine the amount of money required to purchase the ingredient
                recipeCost = ingredientPrice[ingredient] * amount;
                //compound the collective amount of money needed for the whole recipe
                totalRecipeCost += recipeCost;
            }

            //if the total cost exceeds the budget,
            if (totalRecipeCost > budget)
            {
                //break out of the binder
                break;
            }

            //insert the recipe in to a vector if affordable
            affordableRecipes.push_back(recipeName);
            //insert the corresponding price aswell
            recipePrice.push_back(recipeCost);

            //move over to the next line of data, skip the \n in a file
            getline(inFile, fileData);
        }

        //bubble sort algorithm, loop through the affordableRecipes
        for (int j = 0; j < affordableRecipes.size(); j++)
        {
            //loop and compare the price of the affordable recipes
            for (int k = 0; k < affordableRecipes.size() - j - 1; k++)
            {
                //if the recipePrice is the larger than the next price, swap
                if (recipePrice[k] > recipePrice[k + 1])
                {
                    //swap the name of the recipe
                    string temp1;
                    temp1 = affordableRecipes[k];
                    affordableRecipes[k] = affordableRecipes[k + 1];
                    affordableRecipes[k + 1] = temp1;
                    //swap the corresponding price of the recipe aswell
                    int temp2;
                    temp2 = recipePrice[k];
                    recipePrice[k] = recipePrice[k + 1];
                    recipePrice[k + 1] = temp2;
                }
            }
        }

        //cout the affordable recipes in order from cheapest to most expensive
        for (int j = 0; j < affordableRecipes.size(); j++)
        {
            cout << affordableRecipes[j] << endl;
        }

        //however, if there are no affordable recipes,
        if (affordableRecipes.size() == 0)
        {
            //cout statement below
            cout << "No cakes can be made" << endl;
        }

        //clear the vectors for the next binder iteration
        affordableRecipes.clear();
        recipePrice.clear();
        cout << endl;
        getline(inFile, fileData);
    }
}

/**********************************************
 *  uppercaseBinder
 *      parameter: string of the binderName
 *      change the binderName to all caps
**********************************************/
void uppercaseBinder(string &binderName)
{
    for (int i = 0; i < binderName.size(); i++)
    {
        binderName[i] = toupper(binderName[i]);
    }
}