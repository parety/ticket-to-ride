#ifndef SERVER_H
#define SERVER_H

#include "interface.h"
#include "player.h"


#define NB_PLAYERS 2
#define NB_STARTING_CARDS 5


struct f_player{
  int (*init_player)(int id, int nb_player, int nb_towns, int nb_rails, struct Rail *rails, int nb_wagons, int nb_obj, struct Objective *objs);

  struct Action (*play_turn)(int *used_wagons, int *cards_in_hand, int *objectives, int nb_new_rails, struct New_rail *changes, int *new_obj, int *cards);

  int* (*choose_objective)(int nb, int *objs, int min);
  int (*free_player)();
}; // tab de struct f_player dans server.h



enum Town_name;

struct Map_info{
  int nb_towns;
  int nb_links;
  int nb_objs;
  int nb_w_player;

};
  
struct Map_info get_map_info(char* file_name);
void file2rails(struct Rail *rails,int nb_rails,struct Objective* objs ,int nb_objs, char *file_name);  

/**
 * @brief colors Complete the array with the colors used in the game and return the number of colors
 * @param rails Array with all the rails, where there are the colors
 * @param nb_rails The number of rails, length of rails
 * @param col Array to be completed
 * @return The number of colors in the game = length of colors
 */
int colors(struct Rail *rails, int nb_rails, int *col);

/**
 * @brief init_card_hands initialisation of the cards in possession of each player in the beaginning of the game
 * @param card_hands array to be completed
 * @param colors array of all colors
 * @param nb_colors nomber of colors = length of color
 */
void init_card_hands(int nb_players, int nb_starting_objs, int **card_hands, int *colors, int nb_colors);

//void init_nb_cards(NB_PLAYERS, NB_STARTING_CARDS, card_hands, col, nb_colors);

/**
 * @brief max_rail_length
 * @param rails Array with all the rails
 * @param nb_rails The number of rails = length of rails
 * @return The length of the longest rail of the map
 */
int max_rail_length(struct Rail *rails, int nb_rails);



/**
 * @brief init_obj_hands
 * @param nb_players number of players toatal in the game
 * @param nb_starting_objs number of objectives in the hand of each player in the beginning of the game
 * @param obj_hands array to be completed, each case is an array for each player of size nb_starting objs, the int is the index in the array objectives
 * @param objectives array of all the objsctives of the game
 * @param nb_objs number total of objectives in the game
 */
void init_obj_hands(int nb_players, int nb_starting_objs, int  ** obj_hands, struct Objective *objectives,int nb_objs);


/**
 * @brief init_nb_objs
 * @param nb_players
 * @param nb_starting_objs
 * @param nb_objs array with nb_players cases which correspond to the nb of objs of each player
 */
void init_nb_objs(int nb_players, int nb_starting_objs, int *nb_objs);


/**
 * @brief game_end
 * @param wagons_remaining array with nb_players cases which correspond to the nb of wagon of each player
 * @param nb_players
 * @return 0 if all players have more than 2 wagons and the show must go on ! else 1 this this the last turn
 */
int is_last_turn(int * wagons_remaining, int nb_players);

#endif
