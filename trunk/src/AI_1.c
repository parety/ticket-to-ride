// intermediary AI (minimal point objective + ACM)

#include "player.h"
#include "link.h"
#include "interface.h"
#include "server.h"
#include <stdio.h>
#include <stdlib.h>


struct Player AI_1;
static struct Link **AI_1_matrix;



// AUXILIARY FUNCTIONS

/*!
 * \brief give_size_accessible_rails
 * \param tab is the tabular of struct Rail of which the function is going to count the non-occupied rails and the rails occupied by a given player.
 * \param size is the size of the tabular "tab".
 * \param id is the identifier of a given player.
 * \return Returns a tabular of the rails from the tabular "tab" not already occupied by other players.
 */
int give_size_accessible_rails(struct Rail *tab, int size, int id){
  int k = 0;
  struct My_Rail *my_rail;
  for(int i=0; i<size; i++){
    my_rail = give_my_rail(i, AI_1_matrix, tab);
    if(my_rail->id_player==-1 || my_rail->id_player==id)
      k++;
  }
  return k;
}




/*!
 * \brief accessible_rails
 * \param tab is the tabular of struct Rails from which the function is going to keep the still accessible rails and the rails already owned by the given player.
 * \param tab_indices is the tabular that the function is going to fill (if struct Rail at indice "i" is kept, tab_indices[i]=1, 0 otherwise).
 * \param size is the length of the tabular "tab".
 * \param id is the identifier of a given player.
 */
void accessible_rails(struct Rail *tab, int *tab_indices, int size, int id){
  struct My_Rail *my_rail;
  for(int i=0; i<size; i++){
    my_rail = give_my_rail(i, AI_1_matrix, tab);
    if(my_rail->id_player==-1 || my_rail->id_player==id){
      tab_indices[i] = 1;
    }
  }
}



/*!
 * \brief sort_length
 * \param tab is the tabular of struc Rails which is going to be sorted by the function (from the shortest rail to the longest).
 * \param tab_indices is the tabular of indices of rails which is going to be sorted (from the shortest rail to the longest).
 * \param size is the size of the tabulars "tab" and "tab_indices".
 */
void sort_length(struct Rail *tab, int *tab_indices, int size){
  for(int i=0; i<size; i++){
    int min = tab[i].length;
    int ind_min = i;
    for(int j=i; j<size; j++){
      if(tab[j].length<min){
        min = tab[j].length;
        ind_min = j;
      }
    }
    struct Rail rail = {tab[i].town1, tab[i].town2, tab[i].length, tab[i].color};
    int k = tab_indices[i];
    tab[i].town1 = tab[ind_min].town1;
    tab[i].town2 = tab[ind_min].town2;
    tab[i].length = tab[ind_min].length;
    tab[i].color = tab[ind_min].color;
    tab_indices[i] = tab_indices[ind_min];
    tab[ind_min].town1 = rail.town1;
    tab[ind_min].town2 = rail.town2;
    tab[ind_min].length = rail.length;
    tab[ind_min].color = rail.color;
    tab_indices[ind_min] = k;
  }
}

/*!
 * \brief AI_1_fill_tab_accessible (auxiliary function of the function "objective_realised")
 * \param tab_to_fill is a tabular of size the total number of towns; the function is going to set tab_to_fill[i] at 1 if the town "i" is accessible by the player from the town "current_town".
 * \param current_town is the town from which the function is going to search all towns accessible by the player (if he has set a rails from this town); at the begining: current_town=town1 or town2 of the objective
 * \param id is the identifier of the player.
 */
void AI_1_fill_tab_accessible(int *tab_to_fill, int current_town, int id){ 
  tab_to_fill[current_town] = 1;
  for(int i=0; i<AI_1.nb_rails; i++){
    int town1 = AI_1.rails[i].town1;
    int town2 = AI_1.rails[i].town2;
    struct My_Rail *my_rail = give_my_rail(i,AI_1_matrix,AI_1.rails);
    if(my_rail->id_player == id && town1 == current_town && tab_to_fill[town2]==0)
      AI_1_fill_tab_accessible(tab_to_fill,town2,id);
    if(my_rail->id_player == id && town2 == current_town && tab_to_fill[town1]==0)
      AI_1_fill_tab_accessible(tab_to_fill,town1,id);
  }
}

/*!
 * \brief AI_1_objective_realised
 * \param town1 is the town1 of the objective.
 * \param town2 is the town2 of the objective.
 * \param id is the identifier of a given player.
 * \return Returns 1 if the objective has been realised by the player.
 */
int AI_1_objective_realised(int town1, int town2, int id){
  int towns_accessible_left[AI_1.nb_towns+1];
  int towns_accessible_right[AI_1.nb_towns+1];
  for(int i=1; i<AI_1.nb_towns+1; i++){
    towns_accessible_left[i] = 0;
    towns_accessible_right[i] = 0;
  }
  AI_1_fill_tab_accessible(towns_accessible_left,town1,id);
  AI_1_fill_tab_accessible(towns_accessible_right,town2,id);
  int realised = 0;
  for(int i=1; i<AI_1.nb_towns+1; i++){
    if(towns_accessible_left[i]==1 && towns_accessible_right[i]==1)
      realised = 1;
  } 
  return realised;
} 



/*!
 * \brief actualise_all_parameters_received Actualises all the changes that occured since the last time the player was called.
 * \param used_wagons is a tabular which length is the number of players (for a given player, the tabular's value is the number of wagons he has set during the last round).
 * \param cards_in_hand is a tabular which length is the number of players (for a given player, the tabular's value is the number of cards that the player has won or lost during the last round).
 * \param objectives is a tabular composed of the number of objectives drawned by each player.
 * \param nb_new_rails is the length of the tabular changes (= the number of rails that the current player has set during the last round).
 * \param changes is the tabular of all the rails that the current player has set during the last round.
 * \param new_obj is the tabular of the objectives that the current player has drawned during the last round.
 * \param cards If the action chosen in the last round was "draw": "cards" is the tabuler of all the colors (= wagon-cards) drawned. If the action chosen was "build": "cards" is the tabular of all the colors lost (because set).
 */
void actualise_all_parameters_received(int *used_wagons, int *cards_in_hand, int *objectives, int nb_new_rails, struct New_rail *changes, int *new_obj, int *cards){
    // Actualisation of the matrix with the tabular "changes"
    for(int i=0; i<nb_new_rails; i++){
      struct My_Rail *my_rail = give_my_rail(changes[i].rail, AI_1_matrix, AI_1.rails);
      set_player_on_rail(my_rail, changes[i].player);
    }


    // Actualisation of all player's parameters
    for(int i=0; i<AI_1.nb_players; i++){
      AI_1.nb_remaining_wagons[i] -= used_wagons[i];
      AI_1.nb_remaining_wagon_cards[i] += cards_in_hand[i];
      AI_1.nb_remaining_objective_cards[i] += objectives[i];
    }

    // Actualisation of own objectives
    for(int i=0; i<objectives[AI_1.id_player] && AI_1.nb_personal_objs < AI_1.total_nb_obj; i++){
      AI_1.personal_objs[AI_1.nb_personal_objs] = new_obj[i];
      AI_1.nb_personal_objs++;
    }

    // Actualisation of own cards
  if(AI_1.draw_chosen == 1){ // case draw
    for(int i=0; i<cards_in_hand[AI_1.id_player]; i++){
      AI_1.nb_personal_wagon_cards++;
      for(int j=0; j<AI_1.nb_colors; j++){
	if(cards[i]==j)
	  AI_1.personal_wagon_cards[j]++;
      }
    }
  }
  if(cards_in_hand[AI_1.id_player]<0){ // case build
    for(int i=0; i<(0-cards_in_hand[AI_1.id_player]); i++){
      AI_1.nb_personal_wagon_cards--;
      for(int j=0; j<AI_1.nb_colors; j++){
	if(cards[i]==j)
	  AI_1.personal_wagon_cards[j]--;
      }
    }
  }
    
    // Actualisation of number of own objectives completed
  int realised = 1;
  while(realised && AI_1.nb_objs_completed < AI_1.nb_personal_objs){
    int town1 = AI_1.objs[AI_1.personal_objs[AI_1.nb_objs_completed]].town1;
    int town2 = AI_1.objs[AI_1.personal_objs[AI_1.nb_objs_completed]].town2;
    realised = AI_1_objective_realised(town1,town2,AI_1.id_player);
    if(realised)
      AI_1.nb_objs_completed++;
  }
}



/*!
 * \brief fill_tab_acyclic Is a recursive function which fills the tabular "tab_to_fill" (set the indice "i" at 1 if the town "i" is accessible from the town "current_town" by using rails of the tabular "tab", 0 otherwise).
 * \param tab is a tabular of struct Rails which is going to be analysed by the function.
 * \param size is the length of the tabular "tab".
 * \param tab_to_fill is the tabular which is going to be filled (the indice "i" is set at 1 if the town "i" is accessible from the town "current_town" by using rails of the tabular "tab", 0 otherwise).
 * \param current_town is a town accessible from the first town analysed (= the first value of "current_town"), and from which all the rails still accessible are going to be analysed.
 */
void fill_tab_acyclic(struct Rail *tab, int size, int *tab_to_fill, int current_town){
  tab_to_fill[current_town] = 1;
  for(int i=0; i<size; i++){
    if(tab[i].town1==current_town && tab_to_fill[tab[i].town2]==0)
      fill_tab_acyclic(tab,size,tab_to_fill,tab[i].town2);
    if(tab[i].town2==current_town && tab_to_fill[tab[i].town1]==0)
      fill_tab_acyclic(tab,size,tab_to_fill,tab[i].town1);
  }
}



/*!
 * \brief acyclic
 * \param tab is a tabular of struct Rails which correspond to a certain number of rails which represent an acyclic graph.
 * \param size is the length of the tabular "tab".
 * \param rail is a rail which is not already in the tabular "tab".
 * \return Returns 1 if all the rails of the tabular "tab" plus the rail "rail" represent an acyclic graph.
 */
int acyclic(struct Rail *tab, int size, struct Rail rail){
  int towns_visited_left[AI_1.nb_towns+1];
  int towns_visited_right[AI_1.nb_towns+1];
  for(int i=1; i<AI_1.nb_towns+1; i++){
      towns_visited_left[i] = 0;
      towns_visited_right[i] = 0;
  }
  fill_tab_acyclic(tab,size,towns_visited_left,rail.town1);
  fill_tab_acyclic(tab,size,towns_visited_right,rail.town2);
  int acyclic = 1;
  for(int i=1; i<AI_1.nb_towns+1; i++){
    if(towns_visited_left[i]==1 && towns_visited_right[i]==1)
      acyclic = 0;
  } 
  return acyclic;
} 



/*!
 * \brief fill_tab_rail_free_in_ACM
 * \param tab is the ACM tabular.
 * \param acm_tab_indices is the tabular of the indices of the rails in "tab".
 * \param size is the length of the tabulars "tab" and "acm_tab_indices".
 * \param tab_towns_to_fill is a boolean tab which indicates which towns are accessible by town1 or town2 of an objective.
 * \param tab_rails_to_fill is a boolean tab which indicates which rails are accessible by town1 or town2 of an objective.
 * \param current_town is called at the begining with town1 or town2 of an objective owned by the player; the function is going to set at 1 "tab_towns_to_fill[i]" and "tab_rails_to_fill[j]" if the town "i" and the rail "j" are accessible by the player from the town2.
 */
int fill_tab_rail_free_in_ACM(struct Rail *tab,int *acm_tab_indices, int size, int *tab_towns_to_fill, int *tab_rails_to_fill, int current_town, int town_to_reach){
  if(current_town == town_to_reach)
    return 1;

  tab_towns_to_fill[current_town] = 1;

  for(int i=0; i<size; i++){
    if(tab[i].town1==current_town && tab_towns_to_fill[tab[i].town2]==0){
      struct My_Rail *my_rail = give_my_rail(acm_tab_indices[i], AI_1_matrix, AI_1.rails);
      if(is_rail_free(my_rail) || who_on_rail(my_rail)==AI_1.id_player){
	tab_rails_to_fill[acm_tab_indices[i]] = 1;
	fill_tab_rail_free_in_ACM(tab,acm_tab_indices,size,tab_towns_to_fill,tab_rails_to_fill,tab[i].town2,town_to_reach);	  
      }
    }
    if(tab[i].town2==current_town && tab_towns_to_fill[tab[i].town1]==0){
      struct My_Rail *my_rail = give_my_rail(acm_tab_indices[i], AI_1_matrix, AI_1.rails);
      if(is_rail_free(my_rail) || who_on_rail(my_rail)==AI_1.id_player){
	tab_rails_to_fill[acm_tab_indices[i]] = 1;
	fill_tab_rail_free_in_ACM(tab,acm_tab_indices,size,tab_towns_to_fill,tab_rails_to_fill,tab[i].town1,town_to_reach);
      }
    }
  }

  tab_towns_to_fill[current_town] = 0;
  return 0;
}


/*!
 * \brief rail_free_in_ACM
 * \param acm is the tabular in which the function is going to search for a free rail between town1 and town2 if the all way between the two towns is free.
 * \param acm_tab_indices is the tabular of the indices of the rails in the tabular "acm".
 * \param size is the length of the tabulars "acm" and "acm_tab_indices".
 * \param town1 is the town1 of a given objective.
 * \param town2 is the town2 of of a given objective.
 * \return Returns the indice of a free rail between the two towns of the objective given if the all way is still free or partially owned by the player and if the player has enough wagons and wagon-cards to build this rail; returns -1 otherwise.
 */
int rail_free_in_ACM(struct Rail *acm, int *acm_tab_indices, int size, int town1, int town2){
  int towns_visited_left[AI_1.nb_towns+1];
  int rails_visited_left[AI_1.nb_rails];
  for(int i=0; i<AI_1.nb_towns+1; i++)
    towns_visited_left[i] = 0;
  for(int i=0; i<AI_1.nb_rails; i++)
    rails_visited_left[i] = 0;

  int  way_exists = fill_tab_rail_free_in_ACM(acm,acm_tab_indices,size,towns_visited_left,rails_visited_left,town1,town2);
 
  int rail_free_for_objective = -1;

  if(way_exists){
    for(int i=0; i<AI_1.nb_rails; i++){
      if(rails_visited_left[i]==1){ // if rail "i" is between the two towns of the objective
	if(AI_1.rails[i].length <= AI_1.nb_remaining_wagons[AI_1.id_player]){ // if enough wagons to build this rail
	  if(AI_1.rails[i].color == 0){ // if rail is of color neutral
	    if(AI_1.personal_wagon_cards[0] >= AI_1.rails[i].length) // if enough color neutral
	      rail_free_for_objective = i;
	  }
	  else{ // if rail is not of color neutral
	    if(AI_1.personal_wagon_cards[0]+AI_1.personal_wagon_cards[AI_1.rails[i].color] >= AI_1.rails[i].length) // if enough color neutral + color needed
	      rail_free_for_objective = i;
	  }
	}
      }
    }
  }
  return rail_free_for_objective; // Returns -1 if no rail free found; indice of rail otherwise
} 













// MAIN FUNCTIONS



/*!
 * \brief AI_0_init_player Initialises all the parameters of a struct Player (composed of the general game parameters, and his own informations about the game).
 * \param id is the identifier of the player.
 * \param nb_players is the total number of players in the game.
 * \param nb_towns is the total number of towns in the game.
 * \param nb_rails is the total number of rails in the game.
 * \param rails is the tabular composed of all the rails of the game.
 * \param nb_initial_wagons is the number of wagons that each player has at the begining of the game.
 * \param nb_obj is the total number of objective-cards of the game.
 * \param objs is the tabular composed of all the objective-cards of the game.
 * \return Returns 1 if the initialisation went well; 0 otherwise.
 */
int AI_1_init_player(int id, int nb_players, int nb_towns, int nb_rails, struct Rail *rails, int nb_initial_wagons, int nb_obj, struct Objective *objs){
    // Storage of all the informations
    AI_1.id_player = id;
    AI_1.points = 0;
    AI_1.nb_players = nb_players;
    AI_1.nb_towns = nb_towns;

    AI_1.nb_remaining_wagons = malloc(nb_players*sizeof(int));
    for(int i=0; i<nb_players; i++)
      AI_1.nb_remaining_wagons[i] = nb_initial_wagons;


    AI_1.nb_remaining_wagon_cards = malloc(nb_players*sizeof(int));
    for(int i=0; i<nb_players; i++){
      AI_1.nb_remaining_wagon_cards[i] = 0;
    }


    AI_1.nb_remaining_objective_cards = malloc(nb_players*sizeof(int));
    for(int i=0; i<nb_players; i++){
      AI_1.nb_remaining_objective_cards[i] = 0;
    }


    AI_1.nb_rails = nb_rails;
    AI_1.rails = malloc(nb_rails*sizeof(struct Rail));
    for(int i=0; i<nb_rails; i++){
      AI_1.rails[i].town1 = rails[i].town1;
      AI_1.rails[i].town2 = rails[i].town2;
      AI_1.rails[i].length = rails[i].length;
      AI_1.rails[i].color = rails[i].color;
    }


    AI_1.total_nb_obj = nb_obj;
    AI_1.objs = malloc(nb_obj*sizeof(struct Objective));
    for(int i=0; i<nb_obj; i++){
      AI_1.objs[i].town1 = objs[i].town1;
      AI_1.objs[i].town2 = objs[i].town2;
      AI_1.objs[i].points = objs[i].points;
    }


    AI_1.nb_personal_objs = 0;
    AI_1.nb_objs_completed = 0;
    AI_1.personal_objs = malloc(nb_obj*sizeof(int));
    for(int i=0; i<nb_obj; i++)
      AI_1.personal_objs[i] = -1;
  // size of AI_0.personal_objs = total number of objs
  // but has only AI_0.nb_personal_objs


    int *col = malloc(sizeof(int)); //col must be used in the function colors
    AI_1.nb_colors = colors(AI_1.rails, AI_1.nb_rails, &col);
    free(col); //col not usefull so needs to be freed


    AI_1.nb_personal_wagon_cards = 0;
    AI_1.personal_wagon_cards = malloc(AI_1.nb_colors*sizeof(int));
    for(int i=0; i<AI_1.nb_colors; i++)
      AI_1.personal_wagon_cards[i] = 0;


    AI_1.nb_objectives_chosen = 0;
    AI_1.draw_chosen = 0;


    // Initialisation of the personal matrix
    AI_1_matrix = init_map(nb_towns, rails, nb_rails);

    return 1;
}






/*!
 * \brief AI_0_play_turn Calls the player, actualises all the changes that occured since the last time the player was called, and asks the player which action he wants.
 * \param used_wagons is a tabular which length is the number of players (for a given player, the tabular's value is the number of wagons he has set during the last round).
 * \param cards_in_hand is a tabular which length is the number of players (for a given player, the tabular's value is the number of cards that the player has won or lost during the last round).
 * \param objectives is a tabular composed of the number of objectives drawned by each player.
 * \param nb_new_rails is the length of the tabular changes (= the number of rails that the current player has set during the last round).
 * \param changes is the tabular of all the rails that the current player has set during the last round.
 * \param new_obj is the tabular of the objectives that the current player has drawned during the last round.
 * \param cards If the action chosen in the last round was "draw": "cards" is the tabuler of all the colors (= wagon-cards) drawned. If the action chosen was "build": "cards" is the tabular of all the colors lost (because set).
 * \return Returns the struct Action chosen and completed by the player according to his strategy.
 */
struct Action AI_1_play_turn(int *used_wagons, int *cards_in_hand, int *objectives, int nb_new_rails, struct New_rail *changes, int *new_obj, int *cards){

  actualise_all_parameters_received(used_wagons, cards_in_hand, objectives, nb_new_rails, changes, new_obj, cards);

  
  /*
   * while objectives not completed: build a rail for objectives if can, else take cards_wagons 
   * else (objectives all completed): choose maximal length rail and build if can, else take cards_wagons
   */
  struct Action action;
  
  if(AI_1.nb_objs_completed != AI_1.nb_personal_objs){ // if objectives not completed

    // Construction of the ACM tabular
    int size_accessible_rails = give_size_accessible_rails(AI_1.rails, AI_1.nb_rails, AI_1.id_player);
    int kept_indices[AI_1.nb_rails]; 
    for(int i=0; i<AI_1.nb_rails; i++)
      kept_indices[i] = 0;
    struct Rail tab[size_accessible_rails]; // Tabular of the rails kept (already owned or still accessible)
    accessible_rails(AI_1.rails, kept_indices, AI_1.nb_rails, AI_1.id_player);
    int l = 0;
    for(int i=0; i<AI_1.nb_rails; i++){
      if(kept_indices[i]==1){
	tab[l].town1 = AI_1.rails[i].town1;
	tab[l].town2 = AI_1.rails[i].town2;
	tab[l].length = AI_1.rails[i].length;
	tab[l].color = AI_1.rails[i].color;
	l++;
      }
    } // "tab" is only composed of free rails and rails owned bu the player himself
    
    int tab_indices[size_accessible_rails];
    int k=0;
    for(int i=0; i<AI_1.nb_rails; i++){
      if(kept_indices[i]==1){
	tab_indices[k] = i;
	k++;
      }
    } // "tab_indices" is composed of the indices of the struct Rail(s) of "tab"
    
    sort_length(tab, tab_indices, size_accessible_rails);
    struct Rail ACM_tab[AI_1.nb_rails]; // ACM tab
    int ACM_tab_indices[AI_1.nb_rails]; // ACM tab indices
    int size_ACM_tab = 0;
    for(int i=0; i<size_accessible_rails; i++){
      if(acyclic(ACM_tab, size_ACM_tab, tab[i])){
	ACM_tab[size_ACM_tab].town1 = tab[i].town1;
	ACM_tab[size_ACM_tab].town2 = tab[i].town2;
	ACM_tab[size_ACM_tab].length = tab[i].length;
	ACM_tab[size_ACM_tab].color = tab[i].color;
	ACM_tab_indices[size_ACM_tab] = tab_indices[i];
	size_ACM_tab++;
      }
    }
    
    
    //Find a way in the ACM tabular to complete the objective
    
    int start_town = (AI_1.objs[AI_1.personal_objs[AI_1.nb_objs_completed]]).town1;
    int end_town = (AI_1.objs[AI_1.personal_objs[AI_1.nb_objs_completed]]).town2;
    //printf("%d    %d\n",start_town, end_town);

    int indice_of_rail_wanted = rail_free_in_ACM(ACM_tab, ACM_tab_indices, size_ACM_tab, start_town, end_town);

    if(indice_of_rail_wanted > -1){ // build a rail
      action.type = BUILD;
      action.rail = indice_of_rail_wanted;
      action.color = 0; // unused but still initialised
      action.color = 0; // unused but still initialised
      AI_1.nb_objectives_chosen = 0;
      AI_1.draw_chosen = 0;
    }
    else{ // draw wagon_cards
      action.type = DRAW;
      action.rail = 0; //unused but still initialised
      action.color = 0;//AI_1.rails[indice_of_rail_wanted].color;
      action.color = 0;//AI_1.rails[indice_of_rail_wanted].color;
      AI_1.nb_objectives_chosen = 0;
      AI_1.draw_chosen = 1;
    }
  }
  
  else{ // if objectives all completed: choose maximal length rail and build if can, else take cards_wagons

    int maximal_length_town = 0;
    int maximal_length = AI_1.rails[0].length;
    int color = 0;
    for(int i=0; i<AI_1.nb_rails; i++){
      struct My_Rail *my_rail = give_my_rail(i, AI_1_matrix, AI_1.rails);
      if(is_rail_free(my_rail) && my_rail->rail->length > maximal_length){
	maximal_length_town = i;
	maximal_length = my_rail->rail->length;
	color = my_rail->rail->color;
      }
    }
    if(AI_1.nb_personal_wagon_cards >= maximal_length && color!=0 && (AI_1.personal_wagon_cards[color]+AI_1.personal_wagon_cards[0])>=maximal_length){
      action.type = BUILD;
      action.rail = maximal_length_town;
      action.color = 0; // unuseful item but still initialised
      action.color2 = 0; // unuseful item but still initialised
      AI_1.nb_objectives_chosen = 0;
      AI_1.draw_chosen = 0;
    }
    if(AI_1.nb_personal_wagon_cards >= maximal_length && color==0 && AI_1.personal_wagon_cards[0]>=maximal_length){
      action.type = BUILD;
      action.rail = maximal_length_town;
      action.color = 0; // unuseful item but still initialised
      action.color2 = 0; // unuseful item but still initialised
      AI_1.nb_objectives_chosen = 0;
      AI_1.draw_chosen = 0;
    }
    else{
      action.type = DRAW;
      action.rail = 0; // unuseful item but still initialised
      action.color = color; 
      action.color2 = color;
      AI_1.nb_objectives_chosen = 0;
      AI_1.draw_chosen = 1;
    }
  }
  return action;
}






/*!
 * \brief min_point_objs
 * \param nb is the length of the tabular "objs".
 * \param objs is a tabular of objectives proposed to the player (it is the tabular of the indices of the objectives).
 * \param tab is a tabular indicating which objectives have already been chosen (tab[i]=1 if the objective "i" has already been chosen, 0 otherwise).
 * \return Returns the objective (not already chosen by the player) which has the minimal number of points in the tabular "objs".
 */
int min_point_objs(int nb, int *objs, int *tab){
    int i=0;
    while (tab[i] == 1 && i<nb)
        i++;
    for (int k=i;k<nb;k++){
        if (AI_1.objs[objs[k]].points < AI_1.objs[objs[i]].points && tab[k] == 0)
            i=k;
    }
    return i;
}



/*!
 * \brief AI_0_choose_objective
 * \param nb is the number of objectives proposed to the player.
 * \param objs is the tabular of the objectives proposed to the player.
 * \param min is the minimum number of objectives that the player has to chose in the tabular "objs".
 * \return Returns a tabular (in the stack, but instantly registered by the server) indicating which objectives have been chosen.
 */
int *AI_1_choose_objective(int nb, int *objs, int min){
    int k=0;
    int i=0;
    int *tab = malloc(nb * sizeof(int));
    for (i=0;i<nb;i++)
        tab[i]=0;
    while (k<min){
        //chooses minimal point objective
        AI_1.nb_personal_objs++;
        i = min_point_objs(nb, objs, tab);
        tab[i] = 1;
        k++;
    }
    AI_1.nb_objectives_chosen = min;
    return tab;
}




/*!
 * \brief AI_0_free_player Frees the struct Player of the player.
 * \return Returns 1 if the player has been freed well.
 */
int AI_1_free_player(){
    free(AI_1.nb_remaining_wagons);
    free(AI_1.nb_remaining_wagon_cards);
    free(AI_1.nb_remaining_objective_cards);
    free(AI_1.rails);
    free(AI_1.objs);
    free(AI_1.personal_objs);
    free(AI_1.personal_wagon_cards);
    return 1;
}

