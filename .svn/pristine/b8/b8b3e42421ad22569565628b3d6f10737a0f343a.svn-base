#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "server.h"
#include "link.h"



void free_all(int *col, int nb_towns, struct Link **map, int nb_players, 
		int **card_hands, int **obj_hands, struct f_player * player_functions,
	      int **new_obj, int **cards, int * T_chosen_objs){
  free(col);

  free_map(map,nb_towns);
  for (int i = 0; i < nb_players; i++){
    free(card_hands[i]);
    free(obj_hands[i]);
    free(new_obj[i]);
    free(cards[i]);
    player_functions[i].free_player();
  }

  free(card_hands);
  free(obj_hands);
  free(new_obj);
  free(cards);
  free(T_chosen_objs);
  
  free(player_functions);
}
