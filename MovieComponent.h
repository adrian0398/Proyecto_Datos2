//
// Created by adrian on 19/9/19.
//


/**
 * @file MovieComponent.h
 * @author Adrian Lopez
 * @date 19 Sep 2019
 * @brief Header file to declare methods of the Movie Component
 *
 * Variables declared for usage in the .h to ensure linkage
 */

#ifndef PROJECTS_MOVIECOMPONENT_H
#define PROJECTS_MOVIECOMPONENT_H

#include <gtk/gtk.h>
#include "Movie.h"
#include "VideoPlayer.h"

/**
* Component to display poster, year and title of the movie
*/
class MovieComponent {

    public:
    MovieComponent() {
    }

        GtkWidget *movie_name;  /**< widget to display name */
        GtkWidget *movie_image;/**< widget to display image*/
        GtkWidget *movie_year;/**< widget to display year */


    GtkWidget* newmovie_box(Movie_node* movie, int prefwidth);


    /**< if the movie is clicked open videoplayer and display info and stream it's video*/

    /*!
If the movie is clicked open videoplayer and display info and stream it's video

@param[in]  *widget   Main window widget to display the info and video
@param[in]  *data    data passed
*/
    static void clicked (GtkWidget *widget, gpointer *data)
    {   VideoPlayer videoplayer;
        Movie_node* movie= reinterpret_cast<Movie_node *>(data);
        videoplayer.start_videoplayer(movie->name,movie->year,movie->Summary,movie->director,movie->image,movie->ranking,movie->videoURl);

    }

};




#endif //PROJECTS_MOVIECOMPONENT_H
