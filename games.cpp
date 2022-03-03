#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;
const int MAX_GAMES = 100;

struct Game{
  enum {MAX_CHAR = 100};
  char name[MAX_CHAR];
  int sales;
  char platform[MAX_CHAR];
  char releaseDate[MAX_CHAR];
  char developer[MAX_CHAR];
  char publisher[MAX_CHAR];
  Game();
};

//Default
Game::Game(){
  //Initializes all arrays full of null characters
  for (int i = 0; i < MAX_CHAR; i++){
    name[i] = '\0';
    platform[i] = '\0';
    releaseDate[i] = '\0';
    developer[i] = '\0';
    publisher[i] = '\0';
  }
  sales = 0;
}

//Data validation for ints
int readInt(const char prompt[]){
    int temp;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Entry!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}

//Function that reads game file
Game readFile(ifstream &file){
  Game game;
  file.get(game.name, Game::MAX_CHAR, ';');
    file.ignore(100,';');
  file >> game.sales;
  file.ignore(100, ';');
    file.get(game.platform, Game::MAX_CHAR, ';');
  file.ignore(100,';');
    file.get(game.releaseDate, Game::MAX_CHAR, ';');
  file.ignore(100,';');
    file.get(game.developer, Game::MAX_CHAR, ';');
  file.ignore(100,';');
    file.get(game.publisher, Game::MAX_CHAR, '\n');
  file.ignore(100,'\n');
  return game;
}

//Function that fills each part of the array of structs with data from the file
int readData(Game games[]){
  ifstream file("videogames.txt");
  int count = 0;
  while (file.peek() != EOF){
    games[count] = readFile(file);
    count++;
  }
  return count;
}

//Print function
void print(Game g){
  cout << "Title of game: " << g.name << endl;
  cout << "Number of sales: " << g.sales << endl;
  cout << "Platform: " << g.platform << endl;
  cout << "Release date: " << g.releaseDate << endl;
  cout << "Developer: " << g.developer << endl;
  cout << "Publisher: " << g.publisher << endl;
}

//Function to add a game
void addGame(Game &g, int gamesAmount){

  cout << "Please enter a game title:" << endl;
  cin.ignore(100, '\n');
  cin.getline(g.name, gamesAmount);

  g.sales = readInt("Please enter the number of sales:\n");
  
  cout << "Please enter the platform the game is on:" << endl;
    cin.ignore(100, '\n');
  cin.getline(g.platform, gamesAmount);
  
  cout << "Please enter a release date (i.e. September 25, 2003):" << endl;
  cin.getline(g.releaseDate, gamesAmount);
  
  cout << "Please enter the developer of the game:" << endl;
  cin.getline(g.developer, gamesAmount);
  
  cout << "Please enter the publisher of the game:" << endl;
  cin.getline(g.publisher, gamesAmount);
  
}

//Function to remove a game
void removeGame(Game games[], int gamesAmount, int remove){
  for(int i = remove - 1; i < gamesAmount; i++){
    games[i] = games[i + 1];
  }
}

//Function that writes data in the array to the file, "saving" it
void save(Game games[], int gamesAmount){
  ofstream out("videogames.txt");
  for (int i = 0; i < gamesAmount; i++){
    out << games[i].name << ";";
    out << games[i].sales << ";";
    out << games[i].platform << ";";
    out << games[i].releaseDate << ";";
    out << games[i].developer << ";";
    out << games[i].publisher << endl;
  }
}

//Menu fucntion
int menu(int select){
  cout << "Please input a selection by inputting 1 - 7:" << endl;
  cout << "1) Reload previous version" << endl;
  cout << "2) Print database" << endl;
  cout << "3) Add a game" << endl;
  cout << "4) Remove a game" << endl;
  cout << "5) Print games developed by Nintendo" << endl;
  cout << "6) Save current changes" << endl;
  cout << "7) Quit" << endl;
  select = readInt("");
  return select;
}



int main(){
  Game gamesOriginal[MAX_GAMES];
  int gamesAmountOriginal = readData(gamesOriginal);
  Game gamesOld[MAX_GAMES];
  Game gamesNew[MAX_GAMES];
  int gamesAmount = readData(gamesNew);
  
  //testing the array
  cout << "Amount OF GAMES = " << gamesAmount << endl;
  int select = 0;
  while (select != 7){
    cout << "---MAIN MENU---" << endl;
    select = menu(select);
    int gamesAmountOld = gamesAmount;
    


    //Reload Database
    if (select == 1){

      int choice = 0;
      while (choice != 3){
      
      cout << "Would you like to reload to the previous version or hard reset?" <<endl;
      cout << "1) Previous version" << endl;
      cout << "2) Hard reset" << endl;
      cout << "3) Go back" << endl;
        cin >> choice;

      if (choice == 1){
        save(gamesOld, gamesAmountOld);
        break;
      } else if (choice == 2){
        save(gamesOriginal, gamesAmountOriginal);
        break;
      } else if (choice == 3){
        cout << "Returning to main menu..." << endl;
      }
      
      }

      //Print
    } else if (select == 2){
      int choice = 0;
      
      while (choice != 3){
        cout << "Would you like to print the entire database or just a specific game?" << endl;
      cout << "1) Entire database" << endl;
      cout << "2) Specific game" << endl;
      cout << "3) Go back" << endl;
        choice = readInt("");
        //Print entire database
        if (choice == 1){
          for (int i = 0; i < gamesAmount; i++){
            cout << "---GAME #" << i + 1 << "---" << endl;
            print(gamesNew[i]);
          }
          cout << "Total number of games: " << gamesAmount << endl;
        }
        //Print specific game
        if (choice == 2){
          cout << "At least its running" << endl;
          bool valid = false;
          while (valid == false){
            int num;
            cout << "Which game number woudld you like to print (1 -" << gamesAmount << ")?\n" << endl;
            num = readInt("");
            if (num > 0 && num <= gamesAmount){
              cout << "---GAME #" << num << endl;
              print(gamesNew[num - 1]);
              valid = true;
            } else {
              cout << "That game does not exist!" << endl;
            }
        }
      }
      }
    }

      //Adds a game and increments gamesAmount
    else if (select == 3){
      if (gamesAmount < MAX_GAMES){
        addGame(gamesNew[gamesAmount], gamesAmount);
        cout << "Printing your new game: " << endl;
        print(gamesNew[gamesAmount]);
        gamesAmount++;
      } else {
        cout << "There is no space to add another game!" << endl;
      }
    }

      //Removes a game
    else if (select == 4){
      cout << "Please enter the index of the game you would like to remove (1 - " << gamesAmount << "):" << endl;
      int remove = readInt("");
      removeGame(gamesNew, gamesAmount, remove);
      gamesAmount--;
      cout << "Game " << remove << " removed!" << endl;
    }

      //Print all games made by Nintendo
    else if (select == 5){
      cout << "Printing games developed by Nintendo..." << endl;
      for (int i = 0; i < gamesAmount; i++){
        if (strcmp(gamesNew[i].developer, "Nintendo") == 0 || strcmp(gamesNew[i].developer, "Nintendo EAD") == 0){
          print(gamesNew[i]);
        }
      }
    }

      //Save
    else if (select == 6){
      //Fills gamesOld array with file contents at time just before save
      readData(gamesOld);
      save(gamesNew, gamesAmount);
      cout << "Saving..." << endl;
    }

      //Quit
    else if (select == 7){
      cout << "Are you sure you want to quit? Make sure you saved your changes!" << endl;
      int choice = 0;
    while (choice != 1 && choice !=2){
      
      cout << "1) Yes" << endl;
      cout << "2) No" << endl;
      
        choice = readInt("");
      if (choice == 1){
          cout << "Exiting..." << endl;
      } else if (choice == 2) {
        cout << "Returning to main menu..." << endl;
        cout << endl;
        select = 0;
      } else {
        cout << "Please enter a valid selection." << endl;
      }
      

    }
  } else {
      cout << "Please enter a valid selection." << endl;
  }
    }
}