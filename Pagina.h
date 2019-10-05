//
// Created by adrian on 26/9/19.
//

/**
 * @file Pagina.h
 * @author Adrian Lopez
 * @date 26 Sep 2019
 * @brief Header file of Pagina that contains the methods that are used to manipulate pages.
 *
 * Control of the pages and getter and setters to change and manipulate variables from main
 */



#ifndef PROYECTO1_DATOS2_PAGINA_H
#define PROYECTO1_DATOS2_PAGINA_H

#include <iostream>
#include "Linkedlist.h"
#include "Movie.h"
#include <list>
#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = ::boost::filesystem;

/**
* A class node that save variables to the object
*/
class Movie_nodes {
public:
    string name; /**< Movie name*/
    string year; /**< Year of the movie */
    string IMBDlink; /**< link that is used to search with curl */
    string ranking; /**< movie ranking*/
    string Summary;/**< movie summary*/
    string image; /**< movieiimage that will be display in the main window*/
    string videoURl; /**< Url of the video that is obtain from the page */
    string director; /**< Director of the video t */
    Movie_nodes* next; /**< Next reference*/
};

// numero de peli inical, tamanox, tamano y, espacio, altopeli, anchopeli, espaciosotros
//pasar 3+cantidad de pelis
/**
* A class that manages automatically the pages and set and get variables from them
*/

class Pagina {
public:
    Pagina(Linkedlist *movielist, int xSpaceInBetween, int ySpaceInBetween, int windowHeight, int windowWidth,
           int movieHeight, int movieWidth, int espacios, int moviesinx, int moviesiny, GtkWidget *fixed, int pagenum);

    void setmovies();

    void draw();
    void draw2();

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
    string ch [12];
    int contador;
public:
    int getPagenum() const;

public:
    const string *getCh() const;

public:
    GList *getChildren() const;

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
    void get_all(const fs::path& root, const string& ext, vector<fs::path>& ret);


};


#endif //PROYECTO1_DATOS2_PAGINA_H
