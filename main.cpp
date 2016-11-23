/*
** NAME : Eunji Lee
** FILE : main.cpp
** CLASS: CS163 Karla Fant
** ASSGN: Assignment3
*/

#include "table.h"

int main()
{
        char name[SIZE], description[SIZE], type[SIZE], platform[SIZE], recommendation[SIZE];
        int star = 0;
        table my_game(37); // prime num
        game_info new_game, found_game, deleted_game, matching_platform;


// STORE data into the table
        my_game.read_file();
        cout << "Please enter a name of the game : ";
        cin.get(name, SIZE); cin.ignore(SIZE, '\n');
        cout << "Please enter a description of the game : ";
        cin.get(description, SIZE); cin.ignore(SIZE, '\n');
        cout << "Please enter a type of the game : ";
        cin.get(type, SIZE); cin.ignore(SIZE, '\n');
        cout << "Please enter a platform of the game : ";
        cin.get(platform, SIZE); cin.ignore(SIZE, '\n');
        cout << "Please enter a rating of the game : ";
        cin >> star; cin.ignore(SIZE, '\n');
        cout << "Please enter a comment of the game : ";
        cin.get(recommendation, SIZE); cin.ignore(SIZE, '\n');

        new_game.create_game(name, description, type, platform, star, recommendation);
        my_game.insert(name, platform, new_game);

// DISPLAY the entire data in the table
        cout << "\n\n\t<< Games in the table >> " << endl;
        my_game.display_all();

// RETRIEVE by name
        cout << "What game would you like to retrieve - provide the name: ";
        cin.get(name, SIZE); cin.ignore(SIZE, '\n');
        if(my_game.retrieve(name, NULL, found_game))
        {
                cout << "\n\nThis is what was found: ";
                my_game.display_value(name, NULL, found_game);
        }
        else
                cout << "\n\nThere is no matching game with " << name <<endl;

// RETRIEVE by platform
        cout << "\n\nWhat game would you like to retrieve - provide the platform: ";
        cin.get(platform, SIZE); cin.ignore(SIZE, '\n');
        if(my_game.retrieve(NULL, platform, matching_platform))
        {
                cout << "\n\nThis is what was found: ";
                my_game.display_value(NULL, platform, matching_platform);
        }
        else
                cout << "\n\nThere is no matching game with " << platform <<endl;

// ADD recommendations given the particular platform for a game
        cout << "\n\nWhat game would you like to add recommendations - provide the name and platform ";
        cout << "\nname: ";
        cin.get(name, SIZE); cin.ignore(SIZE, '\n');
        cout << "platform: ";
        cin.get(platform, SIZE); cin.ignore(SIZE, '\n');
        if(my_game.retrieve(name, platform, found_game))
        {
                cout << "recommendation for " <<name<<" with "<<platform<<" : ";
                cin.get(recommendation, SIZE); cin.ignore(SIZE, '\n');
                my_game.add_recommendation(name, platform, recommendation, found_game);
                cout << "\n\nThis is how it added: ";
                my_game.display_value(name, platform, found_game);

        }
        else
                cout << "\n\nThere is no matching game with " << name << " with " <<platform <<endl;

// REMOVE by name
        cout << "\nWhat game would you like to remove - provide the name: ";
        cin.get(name, SIZE); cin.ignore(SIZE, '\n');
        if(my_game.retrieve(name, NULL, deleted_game))
        {
                cout << "\n\nThis is what was deleted: ";
                my_game.display_value(name, NULL, deleted_game);
                my_game.remove(name, deleted_game);
        }
        else
                cout << "\n\nThere is no matching game with " << name <<endl;

        cout << "\n\n\t<< Games in the table >> " << endl;
        if(!my_game.isEmpty())
                my_game.display_all();
        else
                cout << "This table is empty!" <<endl;
}
