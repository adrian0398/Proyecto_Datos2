#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include "Linkedlist.h"
#include "Movie.h"

string name="";
string director="";
string year="";
string score="";
string IMBDlink="";

int main(int argc, char *argv[]) {
    Linkedlist* l=new Linkedlist;
    Movie* movie=new Movie;

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
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 1300, 800);
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



    //Node* tmp;
   /* Linkedlist* l=new Linkedlist;
    FILE *fp = fopen("movie_metadata.csv", "r");

    if (!fp) {
        printf("Can't open file\n");
        return 0;
    }

    char buf[2048];
    int row_count = 0;
    int field_count = 0;
    while (fgets(buf, 2048, fp)) {
        field_count = 0;
        row_count++;

        if (row_count == 1) {
            continue;
        }

        char *field = strtok(buf, ",");


        while (field) {

            if (field_count == 11) {
                printf("Name:\t");
                name =field;
                printf("El tamano es");
                cout <<name.size();

            }
            if (field_count == 23) {
                printf("Year:\t");
                year=field;
            }
            if (field_count == 25) {
                printf("Score:\t");
                score=field;
            }
            if (field_count == 17) {
                printf("IMBD link:\t");
                IMBDlink =field;
            }

            printf("%s\n", field);
            field = strtok(NULL, ",");

            field_count++;
        }
        int len = name.length();




        l->insert(name,year,IMBDlink,score);
        printf("\n");
    }
    printf("Termino----------------------------------------------------------------------------");
    l->search("Whiplash ");
    int begin=0;
    int end=3;
    Node* tmp=l->head;
    for(int i=0;i<=end;i++){
        if(i>=begin){
            Movie* movie=new Movie;
            movie->insert(tmp->name,tmp->year,tmp->IMBDlink,tmp->ranking);
            cout<<"entre------------------"<<tmp->name<<endl;
        }
        tmp=tmp->next;
    }



    l->search("My Date with Drew ");
    fclose(fp);

    return 0;*/




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
    int begin=3;
    int end=5;
    Node* tmp=l->head;
    for(int i=0;i<=end;i++){
        if(i>=begin){
            cout<<"entre------------------"<<tmp->name<<endl;
            movie->insert(tmp->name,tmp->year,tmp->IMBDlink,tmp->ranking);

        }
        tmp=tmp->next;
    }

    Html html11;
    title=gtk_label_new("");
    yearstring=gtk_label_new("");
    image20=gtk_image_new();
    gtk_image_set_from_file(GTK_IMAGE(image20),movie->node_search("Avatar")->image.c_str());
    gtk_label_set_text(GTK_LABEL(title),movie->node_search("Avatar")->name.c_str());
    gtk_label_set_text(GTK_LABEL(yearstring),movie->node_search("Avatar")->year.c_str());
    gtk_fixed_put(GTK_FIXED(container),title,200,200);
    gtk_fixed_put(GTK_FIXED(container),yearstring,500,500);
    gtk_fixed_put(GTK_FIXED(container),image20,300,300);



    gtk_widget_show_all(window);

    gtk_main();
    //Html html11;
    //html11.get_video_trailer(movie->node_search("Avatar")->videoURl);
    //l->search("Iron Man 3");
    //movie->search("Cavite");





}
