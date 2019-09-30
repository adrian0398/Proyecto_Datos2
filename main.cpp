#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include "Linkedlist.h"
#include "Movie.h"
#include "VideoPlayer.h"
#include "MovieComponent.h"
#include "Pagina.h"
#include <math.h>


string name="";
string director="";
string year="";
string score="";
string IMBDlink="";
GtkWidget* memorylbl;



VideoPlayer videoPlayer;


void memory_display();
void next_clicked(GtkWidget* window, GdkEvent* ev, gpointer userdata)
{
    g_print ("next");
}

void previous_clicked(GtkWidget* window, GdkEvent* ev, gpointer userdata)
{
    g_print ("previous");
}

void scroll_cb(GtkWidget* window, GdkEvent* ev, gpointer userdata)
{   if(ev->scroll.direction==0){
        g_print ("scrolled up");
}
    if(ev->scroll.direction==1) {
        g_print("scrolled down");
    }
}

void resize_cb(GtkWidget* window, GdkEvent* ev, gpointer userdata)
{
    g_print ("resized!");
    cout<<gtk_widget_get_allocated_height(window);
    cout<<gtk_widget_get_allocated_width(window);
    g_print ("resized!");
    memory_display();
}

void memory_display() {
    /*int tSize = 0, resident = 0, share = 0;
    ifstream buffer("/proc/self/statm");
    buffer >> tSize >> resident >> share;
    buffer.close();
    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    int rss = resident * page_size_kb;
    string memorydip="Memory usage: "+std::to_string(rss)+ " KB";
    GdkColor color;
    gdk_color_parse ("white", &color);
    gtk_widget_modify_fg (memorylbl, GTK_STATE_NORMAL, &color);
    gtk_label_set_text(GTK_LABEL(memorylbl), memorydip.c_str());*/
}

void on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    switch (event->keyval) {
        case GDK_KEY_o:
            printf("key pressed: %s\n", "zoom out");
            break;
        case GDK_KEY_i:
            printf("key pressed: %s\n", "zoom in");
            break;

    }

}

int num_moviex(int window_width,int espacios,int x_space_in_between, int movie_width){
    int moviesinx=floor((window_width-(2*espacios)+x_space_in_between)/(x_space_in_between+movie_width));
    return moviesinx;
}

int num_moviey(int window_height,int espacios,int y_space_in_between, int movie_height){
    int moviesiny=floor((window_height-(2*espacios)+y_space_in_between)/(y_space_in_between+movie_height));
    return moviesiny;
}


int main(int argc, char *argv[]) {
    int x_space_in_between;
    int y_space_in_between;
    int window_height;
    int window_width;
    int movie_height;
    int movie_width;
    int espacios;
    int moviesinx;
    int moviesiny;
    int pagina=1;

    Linkedlist* l=new Linkedlist;
    Movie* movie=new Movie;
    Movie* indisplay=new Movie;

    GtkWidget *window;
    GtkWidget *layout;
    GtkWidget *image;
    GtkWidget *image2;
    GtkWidget *button;
    GtkWidget *container;
    GtkWidget *containermovie;
    GtkWidget *title;
    GtkWidget *image20;
    GtkWidget *yearstring;
    GtkWidget *previous;
    GtkWidget *next;
    gtk_init(&argc, &argv);

    x_space_in_between=50;
    y_space_in_between=x_space_in_between;
    espacios=x_space_in_between;
    movie_width=100;
    movie_height=147;
    window_width=1300;
    window_height=800;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), window_width, window_height);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window),"TEC_Flix");

    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER (window), layout);
    gtk_widget_show(layout);

    image = gtk_image_new_from_file("background_tecflix.jpg");
    gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);



    container = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER (layout), container);
    gtk_widget_show(container);









    g_signal_connect_swapped(G_OBJECT(window), "destroy",
                             G_CALLBACK(gtk_main_quit), NULL);


    using namespace std;


    ifstream in("movie_metadata_used.csv");


    std::string linea;
    while(std::getline(in,linea))
    {
        int row_counter=0;
        std::stringstream   stream(linea);
        std::string         valor;

        std::cout << "Contenido de la linea:\n";
        while(std::getline(stream,valor,','))
        {
            switch (row_counter) {
                case (0):
                        director=valor;
                    break;
                case (1):
                        name=valor;
                    break;
                case (2):
                    IMBDlink=valor;
                    break;
                case (3):
                    year=valor;
                    break;
                case (4):
                    score=valor;
                    break;
            }
            std::cout << "valor leido: " << valor<<row_counter << '\n';
            row_counter++;
        }
        l->insert(name,year,IMBDlink,score,director);
        std::cout << "Fin de la linea\n";
    }

    std::cout<<"Buscar----------------------"<<endl;
    //l->search("Whiplash");


//debe iniciar en 3
    int begin=4133;
    int end=4137;
    Node* tmp=l->head;
    for(int i=0;i<=end;i++){
        if(i>=begin){
            cout<<"entre------------------"<<tmp->name<<endl;
            movie->insert(tmp->name,tmp->year,tmp->IMBDlink,tmp->ranking,tmp->director);

        }
        tmp=tmp->next;
    }

    Html html11;
    title=gtk_label_new("");
    yearstring=gtk_label_new("");
    image20=gtk_image_new();



    GtkWidget* mainbox;
    GtkWidget *fixed;
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(layout), fixed);

    MovieComponent* movieComponent= new MovieComponent();
    mainbox=movieComponent->newmovie_box(movie->node_search("30 Nights of Paranormal Activity with the Devil Inside the Girl with the Dragon Tattoo"));
    gtk_fixed_put(GTK_FIXED(fixed),mainbox,20,20);

    MovieComponent* movieComponent2= new MovieComponent();
    mainbox=movieComponent2->newmovie_box(movie->node_search("Never Back Down 2: The Beatdown"));
    gtk_fixed_put(GTK_FIXED(fixed),mainbox,220,20);

    cout<<"AQUI"<<window_width<<espacios<<x_space_in_between<<movie_width<<endl;
    moviesinx=num_moviex(window_width,espacios,x_space_in_between, movie_width);
    moviesiny=num_moviey(window_height,espacios,y_space_in_between, movie_height);
    /*MovieComponent* movieComponent3= new MovieComponent();
    mainbox3=movieComponent3->newmovie_box(movie->node_search("Pirates of the Caribbean: At World's End"));
    MovieComponent* movieComponent4= new MovieComponent();
    mainbox4=movieComponent2->newmovie_box(movie->node_search("The Dark Knight Rises"));
    MovieComponent* movieComponent5= new MovieComponent();
    mainbox5=movieComponent3->newmovie_box(movie->node_search("Star Wars: Episode VII - The Force Awakens"));
    MovieComponent* movieComponent6= new MovieComponent();
    mainbox6=movieComponent2->newmovie_box(movie->node_search("John Carter"));*/

    /*gtk_fixed_put(GTK_FIXED(fixed),mainbox3,420,20);
    gtk_fixed_put(GTK_FIXED(fixed),mainbox4,620,20);
    gtk_fixed_put(GTK_FIXED(fixed),mainbox5,820,20);
    gtk_fixed_put(GTK_FIXED(fixed),mainbox6,1020,20);*/
    Pagina* actual=new Pagina(l, x_space_in_between, y_space_in_between, window_height, window_width,
            movie_height, movie_width, espacios, moviesinx, moviesiny, fixed, pagina);

    actual->setmovies();
    actual->draw();
    memorylbl=gtk_label_new("");

    next=gtk_button_new();
    previous=gtk_button_new();

    gtk_button_set_label(GTK_BUTTON(next),"next");
    gtk_button_set_label(GTK_BUTTON(previous),"previous");


    gtk_fixed_put(GTK_FIXED(fixed),next,10,770);
    gtk_fixed_put(GTK_FIXED(fixed),previous,1200,770);

    gtk_fixed_put(GTK_FIXED(fixed),memorylbl,1100,0);

    //Movie_node* movieNode1= movie->node_search("Avatar");
    //const gchar *key="Movie name";
    //g_object_set_data (G_OBJECT(mainbox),key,movieNode1);

    g_signal_connect(next, "clicked", G_CALLBACK(next_clicked), NULL);
    g_signal_connect(previous, "clicked", G_CALLBACK(previous_clicked), NULL);

    g_signal_connect(window, "scroll-event", G_CALLBACK(scroll_cb), NULL);
    g_signal_connect(window, "configure-event", G_CALLBACK(resize_cb), NULL);
    g_signal_connect (window, "key_press_event", G_CALLBACK (on_key_press), NULL);

    gtk_widget_show_all(window);


    gtk_main();
    //remove("Spectre.jpg");
    //Html html11;
    //html11.get_video_trailer(movie->node_search("Avatar")->videoURl);
    //l->search("Iron Man 3");
    //movie->search("Cavite");






}


