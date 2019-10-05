//
// Created by adrian on 26/9/19.
//


/**
 * @file Pagina.cpp
 * @author Adrian Lopez
 * @date 26 Sep 2019
 * @brief File containing methods of Pagina
 *
 * This class is the one that controls the display, resize and movies in memory of the program
 */

#include "Pagina.h"
#include "MovieComponent.h"

/*!
This function is called to draw in the main window the number of movies that can fit for a size

*/

void Pagina::draw() {

    for(int i=0; i<g_list_length(children);i++) {
        gtk_widget_destroy(GTK_WIDGET(g_list_nth_data(children,i)));
    }
    children=NULL;





    Movie_node* tmp=movies->head;

    int numdecolumna=1;
    int numdefila=1;
    while (tmp != NULL) {
        int posx;
        int posy;
        if (numdecolumna>moviesinx){
            numdecolumna=1;
            numdefila=numdefila+1;
        }


        posx=espacios+(numdecolumna-1)*movie_width+(numdecolumna-1)*x_space_in_between;
        posy=espacios+(numdefila-1)*movie_height+(numdefila-1)*y_space_in_between;
        MovieComponent* movieComponent= new MovieComponent();
        mainbox=movieComponent->newmovie_box(tmp,prefsize);
        gtk_fixed_put(GTK_FIXED(fixed),mainbox,posx,posy);

        children=g_list_append(children,mainbox);

        tmp= tmp->next;
        numdecolumna=numdecolumna+1;


    }



}

/*!
This function is called to draw in the main window the movies if a scroll event is detected
*/

void Pagina::draw2() {


    for(int i=0; i<g_list_length(children);i++) {
        gtk_widget_destroy(GTK_WIDGET(g_list_nth_data(children,i)));

    }
    children=NULL;


/**
* If page num is 1 only actual and posterior pages are kept
*/

    if(pagenum==1){
        contador=0;
        Movie_node *tmp = biggerlist->head;

        int numdecolumna = 1;
        int numdefila = 1;
        while (tmp != NULL) {
            contador=contador+1;
            int posx;
            int posy;
            if (numdecolumna > moviesinx) {
                numdecolumna = 1;
                numdefila = numdefila + 1;
            }

/**
* Set window positions
*/
            posx = espacios + (numdecolumna - 1) * movie_width + (numdecolumna - 1) * x_space_in_between;
            posy = espacios + (numdefila - 1) * movie_height + (numdefila - 1) * y_space_in_between;

            if(contador==moviesiny*moviesinx+1){
                numdefila=1;

            }
            if(contador>moviesiny*moviesinx){
                posy = espacios + (numdefila - 1) * movie_height + (numdefila - 1) * y_space_in_between+window_height;
            }





            MovieComponent *movieComponent = new MovieComponent();
            mainbox = movieComponent->newmovie_box(tmp, prefsize);
            gtk_fixed_put(GTK_FIXED(fixed), mainbox, posx, posy);

            children = g_list_append(children, mainbox);

            tmp = tmp->next;
            numdecolumna = numdecolumna + 1;

    }
    }
    else {
        /**
* If the num page is other than oone 3 pages need to be saves, previous, actual ande next.
*/
        contador=0;
        Movie_node *tmp = biggerlist->head;

        int numdecolumna = 1;
        int numdefila = 1;
        while (tmp != NULL) {
            contador=contador+1;
            int posx;
            int posy;
            if (numdecolumna > moviesinx) {
                numdecolumna = 1;
                numdefila = numdefila + 1;
            }


            posx = espacios + (numdecolumna - 1) * movie_width + (numdecolumna - 1) * x_space_in_between;
            posy = espacios + (numdefila - 1) * movie_height + (numdefila - 1) * y_space_in_between-window_height;


            if(contador==moviesiny*moviesinx+1){
                numdefila=1;

            }

            if(contador>moviesiny*moviesinx&&contador<2*moviesiny*moviesinx+1){
                posy = espacios + (numdefila - 1) * movie_height + (numdefila - 1) * y_space_in_between;
            }
            if(contador==2*moviesiny*moviesinx+1){
                numdefila=1;
            }
            if(contador>2*moviesiny*moviesinx){
                posy = espacios + (numdefila - 1) * movie_height + (numdefila - 1) * y_space_in_between+window_height;
            }







/**
* Fix the components in the window
*/


            MovieComponent *movieComponent = new MovieComponent();
            mainbox = movieComponent->newmovie_box(tmp, prefsize);
            gtk_fixed_put(GTK_FIXED(fixed), mainbox, posx, posy);

            children = g_list_append(children, mainbox);

            tmp = tmp->next;
            numdecolumna = numdecolumna + 1;


        }
    }


}




/**
* Class constructor
*/

Pagina::Pagina(Linkedlist *movielist, int xSpaceInBetween, int ySpaceInBetween, int windowHeight, int windowWidth,
               int movieHeight, int movieWidth, int espacios, int moviesinx, int moviesiny, GtkWidget *fixed, int pagenum)
        : movielist(movielist), x_space_in_between(xSpaceInBetween), y_space_in_between(ySpaceInBetween),
          window_height(windowHeight), window_width(windowWidth), movie_height(movieHeight), movie_width(movieWidth),
          espacios(espacios), moviesinx(moviesinx), moviesiny(moviesiny), fixed(fixed), pagenum(pagenum) {




}

/**
* Set movies in the lists that are used to change pages.
 * movies and biggerlist are changed and the movies are inserted are deleted depending on size, number of elements
*/


void Pagina::setmovies() {


    free(movies);
    movies = new Movie;

    int begin = 3 + (pagenum - 1) * (moviesinx * moviesiny);
    int end = 3 + (pagenum) * (moviesinx * moviesiny);
    Node *tmp = movielist->head;

    for (int i = 0; i < end; i++) {
        if (i >= begin) {

            if (biggerlist->search(tmp->name)) {
                cout << "enmemoria------------------" << tmp->name << endl;
                Movie_node *tmp6 = biggerlist->node_search(tmp->name);
                movies->insertready(tmp6->name, tmp6->year, tmp6->IMBDlink, tmp6->ranking, tmp6->director, tmp6->image,
                                    tmp6->Summary, tmp6->videoURl);
            } else {
                cout << "noenmemoria------------------" << tmp->name << endl;
                movies->insert(tmp->name, tmp->year, tmp->IMBDlink, tmp->ranking, tmp->director);
            }

        }
        tmp = tmp->next;
    }

    /**
* For higher pages three pages are needed
*/
    if (pagenum > 1) {
        begin = 3 + (pagenum - 2) * (moviesinx * moviesiny);
        end = 3 + (pagenum - 1) * (moviesinx * moviesiny);
        Node *tmp1 = movielist->head;

        for (int i = 0; i < end; i++) {
            if (i >= begin) {


                if (biggerlist->search(tmp1->name)) {
                    cout << "enmemoria------------------" << tmp1->name << endl;
                    Movie_node *tmp7 = biggerlist->node_search(tmp1->name);
                    biggerlist->insertready(tmp7->name, tmp7->year, tmp7->IMBDlink, tmp7->ranking, tmp7->director,
                                            tmp7->image, tmp7->Summary, tmp7->videoURl);
                } else {
                    cout << "noenmemoria------------------" << tmp1->name << endl;
                    biggerlist->insert(tmp1->name, tmp1->year, tmp1->IMBDlink, tmp1->ranking, tmp1->director);
                }

            }
            tmp1 = tmp1->next;
        }

    }


    Movie_node *tmp5 = movies->head;
    while (tmp5 != NULL) {
        biggerlist->insertready(tmp5->name, tmp5->year, tmp5->IMBDlink, tmp5->ranking, tmp5->director, tmp5->image,
                                tmp5->Summary, tmp5->videoURl);
        tmp5 = tmp5->next;
    }


    begin = 3 + (pagenum) * (moviesinx * moviesiny);
    end = 3 + (pagenum + 1) * (moviesinx * moviesiny);
    Node *tmp2 = movielist->head;

    for (int i = 0; i < end; i++) {
        if (i >= begin) {

            if (biggerlist->search(tmp2->name)) {
                cout << "enmemoria------------------" << tmp2->name << endl;
                Movie_node *tmp8 = biggerlist->node_search(tmp2->name);
                biggerlist->insertready(tmp8->name, tmp8->year, tmp8->IMBDlink, tmp8->ranking, tmp8->director,
                                        tmp8->image, tmp8->Summary, tmp8->videoURl);
            } else {
                cout << "noenmemoria------------------" << tmp2->name << endl;
                biggerlist->insert(tmp2->name, tmp2->year, tmp2->IMBDlink, tmp2->ranking, tmp2->director);
            }

        }
        tmp2 = tmp2->next;
    }


    /**
* Change list and show only elements that are needed
*/

    if (biggerlist->getsize() > 3 * moviesinx * moviesiny) {

        int contador = ((biggerlist->getsize()) - (3 * moviesinx * moviesiny));

        for (int i = 0; i < contador; i++) {

            biggerlist->removeFirstNode();

        }



    }


    /**
* Delete images that are not needed to free memory.
*/
    const fs::path root = "/home/adrian/CLionProjects/Proyecto1_Datos2";
    const string ext = ".jpg";
    vector<fs::path> ret;

    get_all(root, ext, ret);

    for (int i = 0; i < ret.size(); ++i) {

        Movie_node *tmp10 = biggerlist->head;

        bool encontrado=false;
        while (tmp10 != NULL) {

           if (ret[i]==tmp10->image.c_str()||ret[i]=="background_tecflix.jpg"){

               encontrado=true;
           }
            tmp10 = tmp10->next;
        }
        if(encontrado==false){
            remove(ret[i].c_str());
            delete(tmp10);
        }

}









}

/**
* Show all .jpg files in folder
*/
void Pagina::get_all(const fs::path& root, const string& ext, vector<fs::path>& ret)
{
    if(!fs::exists(root) || !fs::is_directory(root)) return;

    fs::recursive_directory_iterator it(root);
    fs::recursive_directory_iterator endit;

    while(it != endit)
    {
        if(fs::is_regular_file(*it) && it->path().extension() == ext) ret.push_back(it->path().filename());
        ++it;

    }

}


/**
* Setter and getters of variables.
*/


void Pagina::setPagenum(int pagenum) {
    Pagina::pagenum = pagenum;
}

void Pagina::setFixed(GtkWidget *fixed) {
    Pagina::fixed = fixed;
}

GtkWidget *Pagina::getFixed() const {
    return fixed;
}

void Pagina::setMovies(Movie *movies) {
    Pagina::movies = movies;
}

void Pagina::setWindowHeight(int windowHeight) {
    window_height = windowHeight;
}

void Pagina::setWindowWidth(int windowWidth) {
    window_width = windowWidth;
}

void Pagina::setPrefsize(int prefsize) {
    Pagina::prefsize = prefsize;
}

int Pagina::getPrefsize() const {
    return prefsize;
}

int Pagina::getXSpaceInBetween() const {
    return x_space_in_between;
}

void Pagina::setMoviesinx(int moviesinx) {
    Pagina::moviesinx = moviesinx;
}

void Pagina::setMoviesiny(int moviesiny) {
    Pagina::moviesiny = moviesiny;
}

int Pagina::getYSpaceInBetween() const {
    return y_space_in_between;
}

int Pagina::getMovieHeight() const {
    return movie_height;
}

int Pagina::getMovieWidth() const {
    return movie_width;
}

int Pagina::getEspacios() const {
    return espacios;
}

void Pagina::setMovielist(Linkedlist *movielist) {
    Pagina::movielist = movielist;
}

void Pagina::setMovieHeight(int movieHeight) {
    movie_height = movieHeight;
}

void Pagina::setMovieWidth(int movieWidth) {
    movie_width = movieWidth;
}

int Pagina::getWindowHeight() const {
    return window_height;
}

int Pagina::getWindowWidth() const {
    return window_width;
}

GList *Pagina::getChildren() const {
    return children;
}

const string *Pagina::getCh() const {
    return ch;
}

int Pagina::getPagenum() const {
    return pagenum;
}


void recalcular(){}