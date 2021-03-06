#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "server.h"



void build_rail(int player, int nb_players, int rail,int **card_hands,
		int *nb_cards, int *wagon_cards_modif, int **cards, 
		struct Link **map, struct Rail *rails, /*int nb_rails,*/
		int *wagons_remaining, int *used_wagons){
  printf("\n debut build rail\n");
  int town1 = rails[rail].town1;
  int town2 = rails[rail].town2;
  int length = rails[rail].length;

  if (town1 > town2){ // map is a triangular matrix (sup)
    int tmp = town1;
    town1 = town2;
    town2 = tmp;
  }
  printf("fin if1\n");
  // indicate in the map that the rail is not free anymore

  int set = 0;
  int nb_way = map[town1][town2].nbr_way;
  for (int i = 0; !set && i < nb_way; i++){
    if (map[town1][town2].tab_rails[i].id_rail == rail){
      set = 1;
      if (map[town1][town2].tab_rails[i].id_player == -1){
        map[town1][town2].tab_rails[i].id_player = player;
      }
    }
  }
  printf("fin for1\n");
  // make lose the color cards to the player
  
  int draw_joker = 0;
  for (int lost_cards = 0; lost_cards < length; lost_cards++){
    
    int i = 0;
    if (!draw_joker){
      
      while (i < nb_cards[player] && card_hands[player][i] != rails[rail].color){
        i++;
      }
      printf("fin while in for2\n");
      
      if (i == nb_cards[player])
        draw_joker = 1;
      else{
        nb_cards[player]--;
        cards[player][lost_cards]=rails[rail].color;
        while (i < nb_cards[player]){
            card_hands[player][i] = card_hands[player][i+1];
            i++;
        }
      }
      printf("fin if in for2 1\n");
     }
    
    else{
      
      while (i < nb_cards[player] && card_hands[player][i] != 0)
        i++;
      printf("fin while1 in else in for\n");
      nb_cards[player]--;
      cards[player][lost_cards]=0;
      while (i < nb_cards[player]){
	printf("while2 in else in for %d\n", i);
	card_hands[i] = card_hands[i+1];
	i++;
	    i++;
      }
      printf("fin while1 in else in for\n");
    }
  }
  printf("fin for2\n");
  wagon_cards_modif[player] = -length;
  printf("coucou build rail\n");
  // make lose the wagons to the player

  wagons_remaining[player] -= length;
  used_wagons[player] = length;
  printf("fin build rail\n");
}
