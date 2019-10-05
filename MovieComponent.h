//
// Created by adrian on 19/9/19.
//

#ifndef PROJECTS_MOVIECOMPONENT_H
#define PROJECTS_MOVIECOMPONENT_H

#include <gtk/gtk.h>
#include "Movie.h"
#include "VideoPlayer.h"

class MovieComponent {

    public:
    MovieComponent() {
    }

    VideoPlayer videoplayer_used;
    int posX = 0;
    int posY = 0;
    GtkWidget *mainbox;
        GtkWidget *movie_name;
        GtkWidget *movie_image;
        GtkWidget *movie_year;


    GtkWidget* newmovie_box(Movie_node* movie, int prefwidth);


    static void clicked (GtkWidget *widget, gpointer *data)
    {   VideoPlayer videoplayer;
        Movie_node* movie= reinterpret_cast<Movie_node *>(data);
        videoplayer.start_videoplayer(movie->name,movie->year,movie->Summary,movie->director,movie->image,movie->ranking,movie->videoURl);

    }

};




#endif //PROJECTS_MOVIECOMPONENT_H
