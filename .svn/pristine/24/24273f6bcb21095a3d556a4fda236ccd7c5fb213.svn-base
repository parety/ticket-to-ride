#include <stdlib.h>
#include <stdio.h>
#include "../src/interface.h"
#include "../src/server.h"
#include "../src/link.h"


int test_points_rails_test_file(){//TO USE WITH THE FILE "test_file.txt" AND ONLY WITH THIS FILE

  ////// Initialisation of arguments//////

  struct Map_info map_info = get_map_info("tests_file.txt");
  struct Rail rails[map_info.nb_links];
  struct Objective all_objectives[map_info.nb_objs];
  
  file2rails(rails, map_info.nb_links, all_objectives, map_info.nb_objs, "tests_file.txt");
  struct Link ** map = init_map(map_info.nb_towns, rails, map_info.nb_links); //matrix of link structures
  int nb_towns = map_info.nb_towns;
  int nb_players = 2;
  
  int *points = malloc(nb_players*sizeof(int));
  for (int player = 0; player < nb_players; player++){
    points[player] = 0;
  }

  map[1][2].tab_rails[0].id_player = 1;


  //Tests
  
  points_rails(map,nb_towns,nb_players,points);
  int n = map[1][2].tab_rails[0].rail->length;


  if (points[1] != 1 + (n*(n-1))/2 || points[0] != 0)
    return 0;
  
  free(points);

  return 1;
 
}


int test_points_rails_France(){//TO USE WITH THE FILE "France.txt" AND ONLY WITH THIS FILE

  ////// Initialisation of arguments//////

  //printf("start test");

  struct Map_info map_info = get_map_info("France.txt");
  struct Rail rails[map_info.nb_links];
  struct Objective all_objectives[map_info.nb_objs];
  
  file2rails(rails, map_info.nb_links, all_objectives, map_info.nb_objs, "France.txt");
  struct Link ** map = init_map(map_info.nb_towns, rails, map_info.nb_links); //matrix of link structures

  int nb_players = 4;
  
  int *points = malloc(nb_players*sizeof(int));
  for (int player = 0 ; player < nb_players ; player++){
    points[player] = 0;
  }

  //////building rails and counting points//////


  int *test_points = malloc(nb_players * sizeof(int));
  
  //giving the rails 0 1 2 4 to the player 0
  map[17][32].tab_rails[0].id_player=0;
  test_points[0] = 1+((map[17][32].tab_rails[0].rail->length)*(map[17][32].tab_rails[0].rail->length - 1))/2;
  map[32][33].tab_rails[0].id_player=0;
  test_points[0] += 1+((map[32][33].tab_rails[0].rail->length)*(map[32][33].tab_rails[0].rail->length - 1))/2;
  map[31][32].tab_rails[0].id_player=0;
  test_points[0] += 1+((map[31][32].tab_rails[0].rail->length)*(map[31][32].tab_rails[0].rail->length - 1))/2;
map[30][31].tab_rails[0].id_player=0;
  test_points[0] += 1+((map[30][31].tab_rails[0].rail->length)*(map[30][31].tab_rails[0].rail->length - 1))/2;

  //giving the rails 3 5 7 9 to the player 1
  map[31][32].tab_rails[1].id_player=1;
  test_points[1] = 1+((map[31][32].tab_rails[1].rail->length)*(map[31][32].tab_rails[1].rail->length - 1))/2;
  map[29][31].tab_rails[0].id_player=1;
  test_points[1] += 1+((map[29][31].tab_rails[0].rail->length)*(map[29][31].tab_rails[0].rail->length - 1))/2;
  map[30][33].tab_rails[0].id_player=1;
  test_points[1] += 1+((map[30][33].tab_rails[0].rail->length)*(map[30][33].tab_rails[0].rail->length - 1))/2;
  map[29][30].tab_rails[0].id_player=1;
  test_points[1] += 1+((map[29][30].tab_rails[0].rail->length)*(map[29][30].tab_rails[0].rail->length - 1))/2;

  //giving the rails 6 8 10 12 to the player 2
  map[29][31].tab_rails[1].id_player=2;
  test_points[2] = 1+((map[29][31].tab_rails[1].rail->length)*(map[29][31].tab_rails[1].rail->length - 1))/2;
  map[30][33].tab_rails[1].id_player=2;
  test_points[2] += 1+((map[30][33].tab_rails[1].rail->length)*(map[30][33].tab_rails[1].rail->length - 1))/2;
  map[28][29].tab_rails[0].id_player=2;
  test_points[2] += 1+((map[28][29].tab_rails[0].rail->length)*(map[28][29].tab_rails[0].rail->length - 1))/2;
  map[28][30].tab_rails[0].id_player=2;
  test_points[2] += 1+((map[28][30].tab_rails[0].rail->length)*(map[28][30].tab_rails[0].rail->length - 1))/2;

  //giving the rails 11 13 14 15 to the player 3
  map[28][29].tab_rails[1].id_player=3;
  test_points[3] = 1+((map[28][29].tab_rails[1].rail->length)*(map[28][29].tab_rails[1].rail->length - 1))/2;
  map[19][30].tab_rails[0].id_player=3;
  test_points[3] += 1+((map[19][30].tab_rails[0].rail->length)*(map[19][30].tab_rails[0].rail->length - 1))/2;
  map[19][28].tab_rails[0].id_player=3;
  test_points[3] += 1+((map[19][28].tab_rails[0].rail->length)*(map[19][28].tab_rails[0].rail->length - 1))/2;
  map[9][19].tab_rails[0].id_player=3;
  test_points[3] += 1+((map[9][19].tab_rails[0].rail->length)*(map[9][19].tab_rails[0].rail->length - 1))/2;



  //////test//////
  points_rails(map, map_info.nb_towns, nb_players, points);
  for (int i=0 ; i<nb_players ; i++){
    if(points[i] != test_points[i]){
      free(points);
      free(test_points);
      return 0;
    }
  }
  free(points);
  free(test_points);
  return 1;
}




int main(){

  
  printf("Test of test_points_rails_test_file ... ");
  if (test_points_rails_test_file())
    printf("PASSED\n");
  else
    printf("FAILED\n");
  
  printf("Test of test_points_rails_France ... ");
  if (test_points_rails_France())
    printf("PASSED\n");
  else
    printf("FAILED\n");
  
  return 0;
}

