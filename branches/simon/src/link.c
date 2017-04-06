#include <stdlib.h>
#include "link.h"
#include "interface.h"

/*!
 * \brief init_link
 * \param rail
 * \return
 */
struct Link * init_link(){
  struct Link *res;
  res->nbr_way = 0;
  res->tab_rails = malloc(sizeof(struct My_Rail));
  res->tab_rails[0].id = 0;
  return res;
}

/*!
 * \brief modify_link
 * \param link
 * \param rail
 * \return
 */
void modify_link(struct Link * link, struct Rail * rail){
    if (link->nbr_way != 0)
        link->tab_rails = realloc(link->tab_rails,link->nbr_way * sizeof(struct My_Rail));
    link->nbr_way++;
    link->tab_rails[link->nbr_way - 1].rail = rail;
    link->tab_rails[link->nbr_way - 1].id = 0;
}

/*!
 * \brief free_my_rail
 * \param link
 */
void free_my_rail(struct Link * link){
  free(link->tab_rails);
  link->tab_rails = NULL;
}


// A FINIR !!!
/*!
 * \brief init_map
 * \param nbr_lines
 * \param nbr_columns
 * \param tab_rails
 * \param taille_tab_rails
 * \return
 */
struct Link ** init_map(int nbr_towns, struct Rail *tab_rails, int size_tab_rails){

    struct Link ** matrix = malloc(nbr_towns * sizeof(struct Link *));
    for(int i=0; i<nbr_towns; i++)
    matrix[i] = malloc(nbr_towns * sizeof(struct Link));

    for (int i=0;i<nbr_towns;i++)
        for (int j=0;j<nbr_towns;j++)
            matrix[i][j]=*init_link();

    int a;
    int b;
    for (int i=0; i<size_tab_rails;i++){
        a=tab_rails[i].town1;
        b=tab_rails[i].town2;
        if (a<b)
            modify_link(&matrix[a][b],&tab_rails[i]);
        else
            modify_link(&matrix[b][a],&tab_rails[i]);
    }
    return matrix;
}


/*!
 * \brief free_map
 * \param matrix
 * \param nbr_lines
 * \param nbr_columns
 */
void free_map(struct Link ** matrix, int nbr_towns){
  for(int i=0; i<nbr_towns; i++){
    for(int j=0;j<nbr_towns; j++)
      free_my_rail(&matrix[i][j]);
    free(matrix[i]);
  } 
  free(matrix);
}



/*!
 * \brief set_player_on_rail
 * \param rail
 * \param id
 */
void set_player_on_rail(struct My_Rail * rail, int id){
    rail->id = id;
}


/*!
 * \brief is_rail_free
 * \param rail
 * \return
 */
int is_rail_free(struct My_Rail * rail){
    return rail->id==0;
}


/*!
 * \brief who_on_rail
 * \param rail
 * \return
 */
int who_on_rail(struct My_Rail * rail){
    return rail->id;
}


/*!
 * \brief rail_size
 * \param rail
 * \return
 */
int rail_size(struct My_Rail * rail){
    return rail->rail->length;
}

