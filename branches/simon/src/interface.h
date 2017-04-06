#ifndef RAIL_H
#define RAIL_H




// Structure declaration

struct Rail{
  int town1;
  int town2;
  int length;
  int color; // 0 = neutral
};

struct Objective{
  int town1;
  int town2;
  int points;
};

struct Town{
  int id;
  char * name;
};

struct New_rail{
  int rail;
  int player;
};

struct Action{
  enum type{DRAW, BUILD, OBJECTIVE} type;
  int rail; // if BUILD
  int color; // if DRAW // 0 = multicolor
  int color2; // if DRAW

};




// Communication functions (between the server and the clients)

int init_player(int id, int nb_player, int nb_towns, int nb_rails, struct Rail *rails, int nb_wagons, int nb_obj, struct Objective *objs);

struct Action play_turn(int *used_wagons, int *cards_in_hand, int *objectives, int nb_new_rails, struct New_rail *changes, int *new_obj, int *cards);
// used_wagons>=0 ; cards_in_hand>=0 if DRAW, <=0 if BUILD ; objectives>=0 ; cards pointing to the array of colors

int *choose_objective(int nb, int *objs);
// Boolean tab of size nb

int free_player();




#endif
