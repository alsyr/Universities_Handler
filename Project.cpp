/*
 Team 6
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "List.h"

using namespace std;

// Constants for the menu choices
const char  ADD_CHOICE = 'A',
            DELETE_CHOICE  = 'D',
            SEARCH_CHOICE = 'S',
            PRINT_HASH_CHOICE = 'H',
            PRINT_BST_CHOICE = 'B',
            PRINT_INDENTED_BST_CHOICE = 'I',
            WRITE_CHOICE = 'W',
            STATISTICS_CHOICE = 'T',
            DISPLAY_MOST_SEARCHED_CHOICE = 'Y',
            MENU_CHOICE = 'M',
            QUIT_CHOICE = 'Q';

// Function prototypes
void menu();
int getValidNum();
char getValidChoice();
void addUniversity(List *theList);
bool readUniversities(List *theList);
void searchUniversity(List *theList);
string removeTrailingWhiteSpace(string str);

int main( void )
{
    char choice;    // To hold a menu choice
    int num;
    List *theList = new List;
    
    if (!readUniversities(theList))
        return 1;
    
    menu();
    
    do
    {
        choice = getValidChoice(); // validate the input from the user
        
        switch (choice)
        {
            case ADD_CHOICE:
                addUniversity(theList);
                break;
            case DELETE_CHOICE:
                cout << "Type the code to delete corresponging school : ";
				cin >> num;
				theList->deleteList(num);
                break;
            case SEARCH_CHOICE:
                searchUniversity(theList);
                break;
            case PRINT_HASH_CHOICE:
                theList->displayList();
                break;
            case PRINT_BST_CHOICE:
                theList->displaySortedList();
                break;
            case PRINT_INDENTED_BST_CHOICE:
                theList->displayIndentedList();
                break;
            case WRITE_CHOICE:
                theList->writingTxt();
                break;
            case STATISTICS_CHOICE:;
                theList->displayHashStats();
                break;
            case DISPLAY_MOST_SEARCHED_CHOICE:
                theList->displayMostSearched();
                break;
            case MENU_CHOICE:
                menu();
        }
        
    } while (choice != QUIT_CHOICE);
    
    delete theList;
    
    cout << "\n\t*** THE END ***\n";
    
    return 0;
}

/**~*~*
 The menu function displays the menu
 *~**/
void menu()
{
    // Display the menu.
    cout << "\nWhat do you want to do?\n\t"
    << "A"
    << " - Add a university\n\t"
    << "D"
    << " - Delete a university\n\t"
    << "S"
    << " - Search and Print a university\n\t"
    << "H"
    << " - List universities in hash table sequence\n\t"
    << "B"
    << " - List universities in key sequence\n\t"
    << "I"
    << " - Print universities in indented tree\n\t"
    << "W"
    << " - Write data to a file\n\t"
    << "T"
    << " - Hash Statistics\n\t"
    << "Y"
    << " - Display the most frequently searched university\n\t"
    << "M"
    << " - Show the menu\n\t"
    << "Q"
    << " - Quit the program\n"
    << "Enter your choice: ";
}

/**~*~*
 This function prompts the user to enter a character between the ones
 given into the parentheses(upper or lower case).
 If the input is not valid (not a wanted character) it prompts the user
 to enter a new character, until the input is valid.
 *~**/
char getValidChoice()
{
    char input;
    
    do
    {
        cout << "\nPlease enter a valid choice (A, D, S, H, B, I, W, T, Y, M or Q): ";
        cin >> input;
        input = toupper(input); // Convert the input into uppercase
        cin.clear();            // to clear the error flag
        cin.ignore(80, '\n');   // to discard the unwanted input from the input buffer
    }while(input!='A' && input!='D' && input!='S' && input!='H' && input!='B' && input!='I' && input!='W' && input!='T' && input!='Y' && input!='M' && input!='Q');
    
    return input;
}

/**~*~*
 This function makes sure that the input is an int.
 If the input is not valid it prompts the user to enter
 a new number, until the input is valid.
 *~**/
int getValidNum()
{
    int target;
    bool success;
    
    do
    {
        success = static_cast<bool>(cin >> target);
        if(!success)
            cout << "\nPlease enter a valid number: ";
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
    }while(!success);
    
    return target;
}

//**************************************************
// Definition of function readUniversities.
// This function will read all the universities info from
// the file universities.txt and insert them into a
// list, a reference parameter. This function returns
// true if read successfully, and false if it did
// not read successfully or read no university.
// ASSUMPTIONS: about universities.txt
//  1) Each university's data member is on a separate line.
//  2) Each university is immediately after one another.
//  3) There is nothing after the last university's data.
//**************************************************
bool readUniversities(List *theList)
{
    ifstream inFile;
    University *readUniversity;
    string readStr;
    bool empty = true;
    
    // Open file to read, if couldn't open, display error
    // and exit with false
    inFile.open("universities.txt");
    if (!inFile)
    {
        cout << "Error opening universities.txt!\n";
        return false;
    }
    
    while (getline(inFile, readStr))  // get Country's Code
    {
        readUniversity = new University;
        
        // read and process Univeristy's name
        readUniversity->name = removeTrailingWhiteSpace(readStr);
        
        // read and process Univeristy's state
        getline(inFile, readStr);
        readUniversity->state = removeTrailingWhiteSpace(readStr);
        
        // read and process Univeristy's tuition
        getline(inFile, readStr);
        readUniversity->tuition = atoi(readStr.c_str());
        
        // read and process Univeristy's code
        getline(inFile, readStr);
        readUniversity->code = atoi(readStr.c_str());
        
        theList->insertList(readUniversity);
        empty = false;
    }
    
    inFile.close();
    
    if (empty)
        return false;
    
    return true;
}

void addUniversity(List *theList)
{
    University *univ = new University;
    University test;
    int num;
	string answer;
    
    cout << "\n********************************************************************\n";
    cout << "Type the school name : ";
    getline(cin, answer);
    univ->name = answer;
    cout << "Type the state       : ";
    getline(cin, answer);
    univ->state = answer;
    cout << "Type tuition         : ";
    num = getValidNum();
    univ->tuition = num;
    cout << "Type code            : ";
    num = getValidNum();
    univ->code = num;
    cout << "********************************************************************\n";
    
    if(theList->searchListForDuplicate(univ->code,test))
        cout << "Error, this code university is already used" << endl;
    else
        theList->insertList(univ);
}

//**************************************************
// Definition of function removeTrailingWhiteSpace.
// This function removes trailing white spaces at
// the back of the string, str, and returns the new
// string. Removes trailing tabs, line feeds,
// spaces, and carriage returns.
//**************************************************
string removeTrailingWhiteSpace(string str)
{
    int i = str.length() - 1;  // zero based
    while (str[i] == '\t' || str[i] == '\n' || str[i] == ' ' || str[i] == '\r')
    {
        str.erase(i, 1);
        i--;
    }
    return str;
}

/**~*~*
 The searchUniversity searches by unique key
 in the hashedTable given as parameter and prints out
 element if found or an error message if not.
 *~**/
void searchUniversity(List *theList)
{
    int target;
    University univ;
    
    cout << "\nEnter a university you are looking for by its code: ";
    
    target = getValidNum();
    
    cout << "\n********************************************************************\n";
    if (theList->searchList(target, univ))
    {
        cout << "\n\tFOUND! The university with code " << target << " is:";
        cout << "\n\tName    : " << univ.name;
        cout << "\n\tState   : " << univ.state;
        cout << "\n\tTuition : " << univ.tuition << endl << endl;
    }
    else
        cout << "\n\tNOT FOUND! There is no university with the code "
        << target << endl << endl;
    cout << "********************************************************************\n";
    
}