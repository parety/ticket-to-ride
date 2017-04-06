#include <stdlib.h>
#include <stdio.h>
#include "../src/interface.h"
#include "../src/server.h"
#include "../src/link.h"


int test_build_rail(){

  // Initialisation of parameters
  int player = 1;
  struct Map_info map_info = get_map_info("tests_file.txt");
  struct Rail rails[map_info.nb_links];
  struct Objective objectives[map_info.nb_objs];
  file2rails(rails,map_info.nb_links,objectives,map_info.nb_objs,"tests_file.txt");
  int * col = malloc(sizeof(int));
  int nb_colors = colors(rails,map_info.nb_links,col);
  int ** card_hands = malloc(NB_PLAYERS*sizeof(int *));
  int nb_players = 3;
  int nb_starting_cards = 5;
  init_card_hands(nb_players, nb_starting_cards,card_hands, col, nb_colors);

  
  int nb_cards[] = {nb_starting_cards,nb_starting_cards,nb_starting_cards};
  nb_cards[player] = 10;

  card_hands[player] = realloc(card_hands[player], nb_cards[player]*sizeof(int));
  for (int i = 0; i < nb_cards[player]; i++){
    card_hands[player][i] = 42;
  }



  int wagon_cards_modif[] = {0,0,0};
  int **cards = malloc(nb_players*sizeof(int*));
  for (int i = 0; i < nb_players; i++){
    cards[i] = malloc(2*sizeof(int));
    for (int j = 0; j < 2; j++)
      cards[i][j] = -1;
  }

  int rail = 0;
  struct Link ** map = init_map(map_info.nb_towns, rails, map_info.nb_links);
  int nb_rails = map_info.nb_links;
  int wagons_remaining[NB_PLAYERS];
  wagons_remaining[player] = 10;
  init_wagons(wagons_remaining,NB_PLAYERS, map_info.nb_w_player);
  int used_wagons[] = {0,0,0};



  //tests

  build_rail(player,nb_players,rail,card_hands,nb_cards,wagon_cards_modif,cards,map,rails,nb_rails,wagons_remaining,used_wagons);
  
  if (map[1][2].tab_rails[0].id_player != 1)
    return 0;
  
  if (nb_cards[player] != 4)
    return 0;
  
  
  if (cards[player][0] != 42 || cards[player][1] != 42)
    return 0;
  
  if (wagons_remaining[player] != 4)
    return 0;
   
  if (used_wagons[player] != 6)
    return 0;
  
  
  return 1;
}



int main(){

  printf("Test of build_rail ... ");
  if (test_build_rail())
    printf("PASSED\n");
  else
    printf("FAILED\n");

  return 0;

}
