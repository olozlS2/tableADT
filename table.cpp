/*
** NAME : Eunji Lee
** FILE : table.cpp
** CLASS: CS163 Karla Fant
** ASSGN: Assignment3
*/

#include "table.h"

// Class game_info
// Default constructor
game_info::game_info():name(NULL), description(NULL), type(NULL), platform(NULL), star(0), recommendation(NULL) {}

// Default destructor
game_info::~game_info(){}

// This function is to create a collection of game info for each node.
int game_info::create_game(char * new_name, char * new_description, char * new_type, char * new_platform, int new_star, char * new_recommendation)
{
        name = new char[strlen(new_name)+1];
        for(int i=0; i<100; ++i)
        {
                new_name[i] = tolower(new_name[i]);
                new_platform[i] = tolower(new_platform[i]);
        }
        strcpy(name, new_name);
        description = new char[strlen(new_description)+1];
        strcpy(description, new_description);
        type = new char[strlen(new_type)+1];
        strcpy(type, new_type);
        platform = new char[strlen(new_platform)+1];
        strcpy(platform, new_platform);
        recommendation = new char[strlen(new_recommendation)+1];
        strcpy(recommendation, new_recommendation);
        star = new_star;
        return 1;
}

// This function is to edit recommendation into existing game info
int game_info::edit_game(char * new_recommendation)
{
        recommendation = new char[strlen(new_recommendation)+1];
        strcpy(recommendation, new_recommendation);
        return 1;
}

// This function is to copy a collection of game info into another collection of game info
void game_info::copy_game(const game_info new_game)
{
        if(!new_game.name || !new_game.description || !new_game.type || !new_game.platform || !new_game.recommendation || new_game.star == 0)
                return;
        if(name)
                delete[] name;
        if(description)
                delete[] description;
        if(type)
                delete[] type;
        if(platform)
                delete[] platform;
        if(recommendation)
                delete[] recommendation;
        if(star != 0)
                star = 0;

        name = new char[strlen(new_game.name)+1];
        strcpy(name, new_game.name);
        description = new char[strlen(new_game.description)+1];
        strcpy(description, new_game.description);
        type = new char[strlen(new_game.type)+1];
        strcpy(type, new_game.type);
        platform = new char[strlen(new_game.platform)+1];
        strcpy(platform, new_game.platform);
        recommendation = new char[strlen(new_game.recommendation)+1];
        strcpy(recommendation, new_game.recommendation);
        star = new_game.star;
}

// This function is to check if inputted data matches with a name from a collection of a game
int game_info::retrieve(char * matching, game_info & found) const
{
        if(strcmp(matching, found.name)==0)
                return 1;
        return 0;
}

// This function is to check if inputted data matches with a platform from a collection of a game
int game_info::retrieve_plat(char * matching, game_info & found) const
{
        if(strcmp(matching, found.platform)==0)
                return 1;
        return 0;
}

// This function is to compare if two game info objects are same
bool game_info::compare(const game_info & found)
{
        if(strcmp(name, found.name)==0 && strcmp(description, found.description)==0 && strcmp(type, found.type)==0 && strcmp(platform, found.platform)==0 && strcmp(recommendation, found.recommendation)==0 && (star==found.star))
                return 1;
        else
                return 0;
}

// This function is to check if the game info collection exists
bool game_info::isEmpty()
{
        if(name && description && type && platform && recommendation && star!=0)
                return false;
        else
                return true;
}

// This function is to display the collection of game info for table ADT
void game_info::display()
{
        cout << "\nName : " << name << endl;
        cout << "Description : " << description << endl;
        cout << "Type : " << type << endl;
        cout << "Platform : " << platform << endl;
        cout << "Star : " << star << endl;
        cout << "Recommendation : " << recommendation << endl;
}

// table Class
// This function is to store data from the external file into the hash table
void table::read_file()
{
        ifstream in_file;
        in_file.open("CS163_game.txt");
        game_info info;
        if(in_file)
        {
                char * name = new char[SIZE];
                char * genre = new char[SIZE];
                char * type = new char[SIZE];
                char * platform = new char[SIZE];
                int rating = 0;
                char * comment = new char[SIZE];
                while(!in_file.eof())
                {
                        in_file.get(name, SIZE,':');
                        in_file.ignore(SIZE, ':');
                        in_file.get(genre, SIZE,':');
                        in_file.ignore(SIZE, ':');
                        in_file.get(type, SIZE,':');
                        in_file.ignore(SIZE, ':');
                        in_file.get(platform, SIZE,':');
                        in_file.ignore(SIZE, ':');
                        in_file >> rating;
                        in_file.ignore(SIZE, ':');
                        in_file.get(comment, SIZE,'\n');
                        in_file.ignore(SIZE, '\n');
                        info.create_game(name, genre, type, platform, rating, comment);
                        if(!in_file.eof())
                                insert(name, platform, info);
                }
        }
}

// Constructor with integer argument
table::table(int size)
{
        hash_table = new node*[size];
        second_table = new node*[size];
        for(int i=0; i<size; ++i)
        {
                hash_table[i] = NULL;
                second_table[i] = NULL;
        }
        size_table = size-1;
}

// Default destructor
table::~table()
{
        remove_all();
}

// This function is to return the index of array of linear linked lists, where key value is
int table::hash_function(char * key_value) const
{
        int sum = 0;
        if(!key_value)
                return -1;
        for(int i=0; key_value[i]!='\0'; ++i)
        {
                sum+=key_value[i];
                key_value[i]=tolower(key_value[i]);
        }
        return sum % size_table;
}

// This function is to insert particular name and platform of a game
// Two hash tables are created depending on inputted value
// Both hash tables share the same game info but how they store data is different
int table::insert(char * name,char * platform, const game_info & to_add)
{
        int index = hash_function(name);
        int index2 = hash_function(platform);
        if(index==-1)
                return 0;
        if(index2==-1)
                return 0;
        node * temp = new node;
        temp->game = new game_info();
        temp->game->copy_game(to_add);
        temp->next = hash_table[index];
        hash_table[index] = temp;
        node * temp2 = new node;
        temp2->game = new game_info();
        temp2->game->copy_game(to_add);
        temp2->next = second_table[index2];
        second_table[index2] = temp2;
        return 1;
}
// This function is to add recommendation for a particular platform of a game
int table::add_recommendation(char * name, char * platform, char * recommendation, game_info & found)
{
        int index = hash_function(name);
        if(index==-1)
                return 0;
        if(hash_table[index]==NULL)
                return 0;
        node * current  = hash_table[index];
        while(current)
        {
                if(current->game->retrieve_plat(platform, *current->game))
                        current->game->edit_game(recommendation);                               current = current->next;
        }
        return 1;
}

// This function is to check if inputted data is in the hash table
int table::retrieve(char * name, char * platform, game_info & found) const
{
        int index = hash_function(name);
        int index2 = hash_function(platform);
        int result = 0;
        node * current = NULL;
        if(index==-1 && index2==-1)
                return 0;
        if(hash_table[index]==NULL && second_table[index2]==NULL)
                return 0;
        if(hash_table[index] && index2==-1)
        {
                current = hash_table[index];
                while(current)
                {
                        if(current->game->retrieve(name, *current->game))
                        {
                                found.copy_game(*current->game);
                                result = 1;
                        }
                        current = current->next;
                }
        }
        else if(second_table[index2] && index==-1)
        {
                current = second_table[index2];
                while(current)
                {
                        if(current->game->retrieve_plat(platform, *current->game))
                        {
                                found.copy_game(*current->game);
                                result = 1;
                        }
                        current = current->next;
                }
        }
        else if(name && platform && hash_table[index])
        {
                current = hash_table[index];
                while(current)
                {
                        if(current->game->retrieve_plat(platform, *current->game))
                                result = 1;
                        current = current->next;
                }
        }
        return result;
}

// This function is to remove the inputted value from the hash table
int table::remove(char * key_value, game_info & deleted) const
{
        int index = hash_function(key_value);
        if(index==-1)
                return 0;
        if(hash_table[index]==NULL)
                return 0;
        node * current = hash_table[index];
        node * temp = NULL;
        while(current)
        {
                temp = current;
                current = current->next;
                delete temp;
        }
        hash_table[index]=NULL;
        return 1;

}

// This function is to remove all data from the hash table
void table::remove_all()
{
        if(hash_table==NULL)
                return;
        node * temp = NULL;
        for(int i=0; i<size_table; ++i)
        {
                while(*(hash_table+i))
                {
                        temp =*(hash_table+i);
                        temp = temp->next;
                        delete *(hash_table+i);
                        *(hash_table+i) = temp;
                }
        }
}

// This function is to display all data of the hash table
int table::display_all() const
{
        node * temp = NULL;
        node ** temp2 = hash_table;
        if(!temp2)
                return 0;
        for(int i=0; i<size_table; ++i)
        {
                temp = hash_table[i];
                while(temp)
                {
                        temp->game->display();
                        temp = temp->next;
                }
                cout << endl;
        }
        return 1;
}

// This function is to display a collection of game info with a particular name or platform
int table::display_value(char * name, char * platform, game_info & found) const
{
        int index = hash_function(name);
        int index2 = hash_function(platform);
        if(index==-1 && index2==-1)
                return 0;
        if(hash_table[index]==NULL&&second_table[index2]==NULL)
                return 0;
        node * current = NULL;
        if(hash_table[index] && index2==-1)
                current = hash_table[index];
        else if(second_table[index2] && index==-1)
                current = second_table[index2];
        else if(name && platform)
        {
                current = hash_table[index];
                while(current)
                {
                        if(current->game->retrieve_plat(platform, *current->game))
                                current->game->display();
                        current = current->next;
                }
                return 1;
        }
        while(current)
        {
                current->game->display();
                current = current->next;
        }
        return 1;
}

// This function is to check if the hash table is empty
bool table::isEmpty()
{
        node * temp = NULL;
        for(int i=0; i<size_table; ++i)
        {
                temp = hash_table[i];
                while(temp)
                {
                        if(temp)
                                return false;
                        temp = temp->next;
                }
        }
        return true;
}
