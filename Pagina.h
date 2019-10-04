//
// Created by adrian on 26/9/19.
//

#ifndef PROYECTO1_DATOS2_PAGINA_H
#define PROYECTO1_DATOS2_PAGINA_H

#include <iostream>
#include "Linkedlist.h"
#include "Movie.h"

using namespace std;
class Movie_nodes {
public:
    string name;
    string year;
    string IMBDlink;
    string ranking;
    string Summary;
    string image;
    string videoURl;
    string director;
    Movie_nodes* next;
};

// numero de peli inical, tamanox, tamano y, espacio, altopeli, anchopeli, espaciosotros
//pasar 3+cantidad de pelis
class Pagina {
public:
    Pagina(Linkedlist *movielist, int xSpaceInBetween, int ySpaceInBetween, int windowHeight, int windowWidth,
           int movieHeight, int movieWidth, int espacios, int moviesinx, int moviesiny, GtkWidget *fixed, int pagenum);

    void setmovies();

    void draw();

private:
    Linkedlist* movielist;
    int x_space_in_between;
    int y_space_in_between;
public:
    void setWindowHeight(int windowHeight);

    void setWindowWidth(int windowWidth);

private:
    int window_height;
    int window_width;
    int movie_height;
    int movie_width;
    int espacios;

public:
    void setMovies(Movie *movies);

public:
    GtkWidget *getFixed() const;

public:
    void setFixed(GtkWidget *fixed);

private:
    int moviesinx;

public:
    void setPagenum(int pagenum);

    int getXSpaceInBetween() const;

    int getYSpaceInBetween() const;

    int getMovieHeight() const;

    int getMovieWidth() const;

    int getEspacios() const;

    int getPrefsize() const;

    void setPrefsize(int prefsize);

private:
    int moviesiny;
    int pagenum;
    Movie* movies=new Movie;
    GtkWidget* fixed;
    GtkWidget* mainbox;
    GList *children=NULL, *iter=NULL;
    int prefsize=100;
public:
    int getWindowHeight() const;

    int getWindowWidth() const;

public:
    void setMovielist(Linkedlist *movielist);

    void setMovieHeight(int movieHeight);

    void setMovieWidth(int movieWidth);

private:
    Movie* biggerlist=new Movie;
    //lista de moviecomponents

public:
    Pagina(Linkedlist *movielist);

    void setMoviesinx(int moviesinx);

    void setMoviesiny(int moviesiny);


};


#endif //PROYECTO1_DATOS2_PAGINA_H
