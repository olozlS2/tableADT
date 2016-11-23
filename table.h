/*
** NAME : Eunji Lee
** FILE : table.h
** CLASS: CS163 Karla Fant
** ASSGN: Assignment3
** INPUT: CS163_game.txt
*/

// The purpose of this program is for thos who want to organize the best games that people like to play.
// Game information is stored in two hash tables, one is sorted by name and the other is sorted by platform.
#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>

using namespace std;
const int SIZE = 100;

// Class game_info contains all information of game for table ADT.
// It contains name, description, type, platform, rating, and recommendation of game.
class game_info
{
        public:
                game_info();
                ~game_info();
                int create_game(char * name, char * description, char * type, char * platform, int star, char * recommendation);
                int edit_game(char * recommendation);
                void copy_game(const game_info new_game);
                int retrieve(char * matching, game_info & found) const;
                int retrieve_plat(char * matching, game_info & found) const;
                bool compare(const game_info & found);
                bool isEmpty();
                void display();
        private:
                char * name;
                char * description;
                char * type;
                char * platform;
                int star;
                char * recommendation;
};

// node structure is for table ADT and it contains game_info pointer and node pointer.
struct node
{
        game_info * game;
        node * next;

};

// Class table contains two hash tables, one is sorted by name and second table is sorted by platform.
// hash_function returns the index of the array of linear linked lists.
class table
{
        public:
                table(int size);
                ~table();
                int insert(char * name, char * platform, const game_info & to_add);
                int retrieve(char * name, char * platform, game_info & found) const;
                int remove(char * key_value, game_info & deleted) const;
                void remove_all();
                int display_all() const;
                int display_value(char * name, char * platform, game_info & found) const;
                bool isEmpty();
                int add_recommendation(char * name, char * platform, char * recommendation, game_info & to_add);
                void read_file(); // to store data from the external file
        private:
                node ** hash_table;
                node ** second_table;
                int size_table;
                int hash_function(char * key_value) const;
};
