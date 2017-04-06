#include <stdlib.h>
#include <stdio.h>
#include "../src/interface.h"
#include "../src/server.h"
#include "../src/link.h"



int test_is_last_turn(){

  int nb_players = 4;
  int wagons_remaining[4];
  for (int i = 0; i < nb_players; i++)
    wagons_remaining[i] = 5;

  if (is_last_turn(wagons_remaining,nb_players))
    return 0;
  
  wagons_remaining[3] = 2;
  if (!is_last_turn(wagons_remaining,nb_players))
    return 0;

  return 1;
}










int test_cheat(){
  
  struct Map_info map_info = get_map_info("tests_file.txt");
  struct Action action;
  int nb_players = 3;
  int player = 1;
  int nb_objs_tot = 10;
  int nb_objs[] = {2,3,2};
  int nb_rails = map_info.nb_links;
  struct Rail rails[nb_rails];
  rails[0].town1 = 1;
  rails[0].town2 = 2;
  rails[0].length = 6;
  rails[0].color = 42;
  struct Link ** map = init_map(map_info.nb_towns, rails, map_info.nb_links); //matrix of link structures
  
  int wagons_remaining[] = {2,10,2};
  int **card_hands = malloc(nb_players*sizeof(int*));
  int t[] = {1,42,42,42,7,42,42,42,42,42,3};
  card_hands[player] = t;
  int nb_cards[] = {0,11,0};
  int nb_town = map_info.nb_towns;

  
  
  // draw color cards -> no pb
  action.type = 0;
  if (cheat(action,nb_players,player,nb_objs_tot,nb_objs,rails,nb_rails,wagons_remaining,card_hands,nb_cards,map,nb_town))
    return 0;

  

  // draw objectives -> enought objs in the pile ?
  action.type = 2;

  if (cheat(action,nb_players,player,nb_objs_tot,nb_objs,rails,nb_rails,wagons_remaining,card_hands,nb_cards,map,nb_town))
    return 0;

  nb_objs[0] = 4; // 1 obj left
  
  if (!cheat(action,nb_players,player,nb_objs_tot,nb_objs,rails,nb_rails,wagons_remaining,card_hands,nb_cards,map,nb_town))
    return 0;

  nb_objs[0] = 2;

  
  // build a rail -> rail exist and is free ? enougth wagons ? enought cards of the right color ?
  action.type = 1;
  action.rail = 0;
  //printf("%d\n",map[1][2].tab_rails[0].id_player);
  if (cheat(action,nb_players,player,nb_objs_tot,nb_objs,rails,nb_rails,wagons_remaining,card_hands,nb_cards,map,nb_town))
    return 0;
    
   
  map[1][2].tab_rails[0].id_player = 1; // not free
  if (!cheat(action,nb_players,player,nb_objs_tot,nb_objs,rails,nb_rails,wagons_remaining,card_hands,nb_cards,map,nb_town))
    return 0;
  map[1][2].tab_rails[0].id_player = -1; // free
  
  
  wagons_remaining[player] = 0; // not enougth wagons
  if (!cheat(action,nb_players,player,nb_objs_tot,nb_objs,rails,nb_rails,wagons_remaining,card_hands,nb_cards,map,nb_town))
    return 0;
  wagons_remaining[player] = 10; // not enougth wagons
  
  
  t[1]=2; t[2]=2; t[3]=2; //not enought cards
  if (!cheat(action,nb_players,player,nb_objs_tot,nb_objs,rails,nb_rails,wagons_remaining,card_hands,nb_cards,map,nb_town))
    return 0;

  t[1]=0; t[2]=0; t[3]=0; //joker cards
  if (cheat(action,nb_players,player,nb_objs_tot,nb_objs,rails,nb_rails,wagons_remaining,card_hands,nb_cards,map,nb_town))
    return 0;
  


  return 1;
}











int main(){
  
  printf("Test of is_last_turn ...");
  if (test_is_last_turn())
    printf("PASSED\n");
  else
    printf("FAILED\n");
  


  printf("Test of cheat ...");
  if (test_cheat())
    printf("PASSED\n");
  else
    printf("FAILED\n");



  return 0;
}
