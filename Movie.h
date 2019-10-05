//
// Created by adrian on 14/9/19.
//


/**
 * @file Movie.h
 * @author Adrian Lopez
 * @date 14 Sep 2019
 * @brief File for using linked list to save movie nodes
 *
 * The movie nodes are used to save important details of movie and saved in a list
 */

#ifndef PROJECTS_MOVIE_H
#define PROJECTS_MOVIE_H

#include <string>
#include <iostream>
#include <gtk/gtk.h>
#include "Html.h"
#include "Linkedlist.h"


using namespace std;

/*!
*Movie node that saves the data
*/
class Movie_node {


public:
    string name; /**< Movie name*/
    string year; /**< Year of the movie */
    string IMBDlink; /**< link that is used to search with curl */
    string ranking; /**< movie ranking*/
    string Summary;/**< movie summary*/
    string image; /**< movieiimage that will be display in the main window*/
    string videoURl; /**< Url of the video that is obtain from the page */
    string director; /**< Director of the video t */
    Movie_node* next; /**< Next reference*/

};

/*!
*Class to make a linked list of movies
*/
class Movie { ;

public:
    /*!
*Linked list method to remove the first method by changing the head.
*/
    void removeFirstNode()
    {

        // Move the head pointer to the next node
        Movie_node* temp = head;
        head = head->next;

        delete temp;

    }
    /*!
*Linked list method to insert at the end of the list.
* Pass movie data and make a node that saves all of it's info
@param[in]  newdata   name of the movie to be inserted
@param[in]  year   year of the movie to be inserted
@param[in]  IMBDlink   IMDB link to search the url elements
@param[in]  director   director  of the movie to be inserted


*/
    void insert(string new_data, string year, string IMBDlink, string ranking, string director) {
        Movie_node* new_movie_node = new Movie_node;
        Movie_node* last= head;
        new_movie_node->name = new_data;
        new_movie_node->year = year;
        new_movie_node->IMBDlink = IMBDlink;
        new_movie_node->ranking = ranking;
        new_movie_node->director = director;
        new_movie_node->next = NULL;
        /**
* Use HTML methods to get the elements of the IMBD link and save it in the node
*/
        Html html;
        string url=html.get_url(IMBDlink,new_data);
        new_movie_node->image=html.get_pic(url,new_data);
        new_movie_node->Summary=html.get_summary(url);

        new_movie_node->videoURl=html.get_video_url(url);


        if (head == NULL)
        {
            head = new_movie_node;
            return;
        }

        while (last->next != NULL)
            last = last->next;

        last->next = new_movie_node;
        return;
    }

    /*!
*Linked list method to search a string value
* Use tmp node to search the node
@param[in]  value  value to be searched in the list
@return True or False that depends on value

*/


    bool search(string value){

        Movie_node* tmp=head;
        while (tmp != NULL){
            if (tmp->name == value)
            {

                return true;
            }
            tmp= tmp->next;
        }
        return false;
    }
    /*!
  *Linked list method to search a node with astring value
       * Use tmp node to search the node
  @param[in]  value  value to be searched in the list
  @return Movie_node*, it returns the node in the linked list

  */

    Movie_node* node_search(string value){

        Movie_node* tmp=head;
        while (tmp != NULL){
            if (tmp->name == value)
            {
                return tmp;
            }
            tmp= tmp->next;
        }
        return NULL;
    }


    /*!
  *Linked list method to display the linked list
  * Use tmp node to display each node until linked list is NULL

  */

    void display() {
        Movie_node* ptr=new Movie_node;
        ptr = head;
        while (ptr != NULL) {
            std::cout<< ptr->name <<" ";
            ptr = ptr->next;
        }
    }

    /*!
*Linked list to get the size of the linked list
   * Use tmp node and a counter to get the number of nodes in the list
@return size ,it returns the size of the list.
*/
    int getsize() {
        int size=0;
        Movie_node* ptr=new Movie_node;
        ptr = head;
        while (ptr != NULL) {
            ptr = ptr->next;
            size=size+1;
        }
        return size;
    }

    Movie_node* head = NULL;


    /*!
*Linked list method to insert a node with all the parameters
   * Use an existing list to get the values.
@param[in]  newdata   name of the movie to be inserted
@param[in]  year   year of the movie to be inserted
@param[in]  IMBDlink   IMDB link to search the url elements
@param[in]  director   director  of the movie to be inserted
@param[in]  image   image of the movie previously getted
@param[in]  Summary   Summary of the movie to be inserted
@param[in]  videoUrl   videoUrl of the movie to be inserted

*/
    void insertready(string new_data, string year, string IMBDlink, string ranking, string director, string image, string Summary, string videoUrl) {
        Movie_node* new_movie_node = new Movie_node;
        Movie_node* last= head;
        new_movie_node->name = new_data;
        new_movie_node->year = year;
        new_movie_node->IMBDlink = IMBDlink;
        new_movie_node->ranking = ranking;
        new_movie_node->director = director;
        new_movie_node->image=image;
        new_movie_node->Summary=Summary;
        new_movie_node->videoURl=videoUrl;

        new_movie_node->next = NULL;




        if (head == NULL)
        {
            head = new_movie_node;
            return;
        }

        while (last->next != NULL) {
            last = last->next;
        }

        last->next = new_movie_node;
        return;
    }




};



#endif //PROJECTS_MOVIE_H
