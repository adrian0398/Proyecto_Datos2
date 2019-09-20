//
// Created by adrian on 19/9/19.
//

#ifndef PROJECTS_MOVIECOMPONENT_H
#define PROJECTS_MOVIECOMPONENT_H

#include <gtk/gtk.h>
class MovieComponent {

    public:

        GtkWidget *movie_name;
        GtkWidget *movie_image;
        GtkWidget *movie_year;
        int sizex;
        int sizey;
        int posx;
        int posy;

    MovieComponent(GtkWidget *movieName, GtkWidget *movieImage, GtkWidget *movieYear, GtkWidget *window);


};


#endif //PROJECTS_MOVIECOMPONENT_H
