//
// Created by adrian on 26/9/19.
//

#include "Pagina.h"
#include "MovieComponent.h"

void Pagina::draw() {
    Movie_node* tmp=movies->head;
    cout<<"losers---------------------------"<<endl;
    int numdecolumna=1;
    int numdefila=1;
    while (tmp != NULL) {
        int posx;
        int posy;
        if (numdecolumna>moviesinx){
            numdecolumna=1;
            numdefila=numdefila+1;
        }
        std::cout<< tmp->name <<" ";



        posx=espacios+(numdecolumna-1)*movie_width+(numdecolumna-1)*x_space_in_between;
        posy=espacios+(numdefila-1)*movie_height+(numdefila-1)*y_space_in_between;
        MovieComponent* movieComponent= new MovieComponent();
        mainbox=movieComponent->newmovie_box(tmp);
        gtk_fixed_put(GTK_FIXED(fixed),mainbox,posx,posy);



        tmp= tmp->next;
        numdecolumna=numdecolumna+1;

    }



}



Pagina::Pagina(Linkedlist *movielist, int xSpaceInBetween, int ySpaceInBetween, int windowHeight, int windowWidth,
               int movieHeight, int movieWidth, int espacios, int moviesinx, int moviesiny, GtkWidget *fixed, int pagenum)
        : movielist(movielist), x_space_in_between(xSpaceInBetween), y_space_in_between(ySpaceInBetween),
          window_height(windowHeight), window_width(windowWidth), movie_height(movieHeight), movie_width(movieWidth),
          espacios(espacios), moviesinx(moviesinx), moviesiny(moviesiny), fixed(fixed), pagenum(pagenum) {




}

void Pagina::setmovies() {
    int begin=3+(pagenum-1)*(moviesinx*moviesiny);
    int end=3+(pagenum)*(moviesinx*moviesiny)-1;
    Node* tmp=movielist->head;
    cout<<moviesiny<<" "<<moviesinx<<"aquiiiiiiiiiiiiiii"<<begin<<" "<< end<<endl;
    for(int i=0;i<end;i++){
        if(i>=begin){
            cout<<"entre------------------"<<tmp->name<<endl;
            movies->insert(tmp->name,tmp->year,tmp->IMBDlink,tmp->ranking,tmp->director);

        }
        tmp=tmp->next;
    }


}


void recalcular(){}