#ifndef LIAISON_H
#define LIAISON_H
#include "interface.h"




/*!
 * \brief The My_Rail struct is a structure composed of a pointer to a rail, the identifier of the player in the rail (-1 if none), and the identifier of the rail.
 */
struct My_Rail{
  struct Rail const * rail; //ptr
  int id_player; // -1 if no player 
  int id_rail; 
};

/*!
 * \brief The Link struct is a structure composed of the number of ways (rails) between two given towns, and the tabular of the My_rail(s) corresponding to those rails.
 */
struct Link{
  int nbr_way;
  struct My_Rail *tab_rails;
};





/*!
 * \brief give_my_rail
 * \param id_rail is the identifier of the rail wanted.
 * \param matrix is the matrix of all Link(s) composed of all the My_Rail(s) corresponding to all the rails of the game.
 * \param tab_rails is the tabular composed of all the rails of the game.
 * \return the My_Rail corresponding to the identifier "id_rail" of a given rail in the tabular "tab_rails".
 */
struct My_Rail *give_my_rail(int id_rail, struct Link **matrix, struct Rail *tab_rails);



/*!
 * \brief rail_size
 * \param rail is a pointer to the struct My_Rail of which the size is wanted.
 * \return the size of the struct My_Rail given.
 */
int rail_size(struct My_Rail *rail);



/*!
 * \brief set_player_on_rail
 * \param rail is a pointer to the struct My_Rail where the player is going to be placed.
 * \param id is the identifier of the player who is going to be placed on the My_Rail.
 */
void set_player_on_rail(struct My_Rail *rail, int id);



/*!
 * \brief is_rail_free
 * \param rail is a pointer to the struct My_Rail which is going to be analysed.
 * \return 1 if the struct My_Rail is free, 0 otherwise.
 */
int is_rail_free(struct My_Rail *rail);



/*!
 * \brief who_on_rail
 * \param rail is a pointer to the struct My_Rail which is going to be analysed.
 * \return the identifier of the player set on the given struct My_Rail.
 */
int who_on_rail(struct My_Rail *rail); 



/*!
 * \brief init_link
 * \param link is a pointer to the struct Link which is going to be initialised.
 */
void init_link(struct Link *link);



/*!
 * \brief modify_link
 * \param link is a pointer to the struct Link where a rail is going to be added.
 * \param rail is a pointer to the struct Rail which is going to be added in the given struct Link.
 */
void modify_link(struct Link *link, struct Rail *rail, int); 



/*!
 * \brief free_link
 * \param link is a pointer to the struct Link which is going to be freed.
 */
void free_link(struct Link *link);



/*!
 * \brief init_map Initialises the matrix of all the Link(s) composed of all the My_Rail(s) corresponding to all the rails of the game.
 * \param nbr_towns is the total number of towns.
 * \param tab_rails is the tabular of all the rails of the game.
 * \param size_tab_rails is the length of the tabular "tab_rails".
 * \return Returns a matrix so that matrix[i][j] is the struct Link corresponding to the rails between town "i" and town "j".
 */
struct Link **init_map(int nbr_towns, struct Rail *tab_rails, int size_tab_rails);



/*!
 * \brief free_map Frees the matrix created by the function "init_map".
 * \param matrix is the matrix created by the function "init_map".
 * \param nbr_towns is the total number of towns.
 */
void free_map(struct Link ** matrix, int nbr_towns);



#endif 
