#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "server.h"
#include "link.h"




int winner(struct Link **map, int nb_towns, int nb_players,struct Objective * all_objectives, int **obj_hands, int *nb_objs, int nb_rails, struct Rail *rails){

  int *points = malloc(nb_players*sizeof(int));
  for (int player = 0; player < nb_players; player++){
    points[player] = 0;
  }

  points_rails(map, nb_towns, nb_players,points);

  points_objs(map, nb_towns, nb_players,all_objectives,obj_hands,nb_objs,points, nb_rails, rails);


  // The winner is 

  int max_points = 0;
  int winner = -1;
  for (int player = 0; player < nb_players; player++){
    if (points[player] > max_points){
      winner = player;
      max_points = points[player];
    }
  }
  return winner;
}




void points_rails(struct Link **map, int nb_towns, int nb_players,int *points){

  for (int j = 2; j < nb_towns+1; j++){
    
    for (int i = 1; i < j; i++){
      
      for (int way = 0; way < map[i][j].nbr_way; way++){
	

	if (map[i][j].tab_rails[way].id_player > -1){

	    int n = map[i][j].tab_rails[way].rail->length;
	    

	    points[map[i][j].tab_rails[way].id_player] += 1 + (n*(n-1))/2;
	    
	}
      }
    }
  }
}


void fill_tab_accessible(int *tab_to_fill, int current_town, int id, struct Link ** map, int nb_rails, struct Rail *rails){ 
  tab_to_fill[current_town] = 1;
  for(int i=0; i<nb_rails; i++){
    int town1 = rails[i].town1;
    int town2 = rails[i].town2;
    struct My_Rail *my_rail = give_my_rail(i,map,rails);
    if(my_rail->id_player == id && town1 == current_town && tab_to_fill[town2]==0)
      fill_tab_accessible(tab_to_fill,town2,id,map,nb_rails,rails);
    if(my_rail->id_player == id && town2 == current_town && tab_to_fill[town1]==0)
      fill_tab_accessible(tab_to_fill,town1,id,map,nb_rails,rails);
  }
}


int objective_realised(int town1, int town2, int id, int nb_towns, struct Link ** map, int nb_rails, struct Rail *rails){
  int towns_accessible_left[nb_towns+1];
  int towns_accessible_right[nb_towns+1];
  for(int i=1; i<nb_towns+1; i++){
    towns_accessible_left[i] = 0;
    towns_accessible_right[i] = 0;
  }
  fill_tab_accessible(towns_accessible_left,town1,id,map,nb_rails,rails);
  fill_tab_accessible(towns_accessible_right,town2,id,map,nb_rails,rails);
  int realised = 0;
  for(int i=1; i<nb_towns+1; i++){
    if(towns_accessible_left[i]==1 && towns_accessible_right[i]==1)
      realised = 1;
  } 
  return realised;
} 


void points_objs(struct Link **map, int nb_towns, int nb_players,struct Objective * all_objectives, int **obj_hands, int *nb_objs,int *points, int nb_rails, struct Rail *rails){

  for(int player=0; player<nb_players; player++){
    for(int obj=0; obj<nb_objs[player]; obj++){
      int town1 = all_objectives[obj_hands[player][obj]].town1;
      int town2 = all_objectives[obj_hands[player][obj]].town2;
      int pts = all_objectives[obj_hands[player][obj]].points;
      if(objective_realised(town1,town2,player,nb_towns,map,nb_rails,rails))
        points[player] += pts;
      else
          points[player] -= pts;
    }
  }
}




