//
// Created by adrian on 19/9/19.
//


/**
 * @file MovieComponent.cpp
 * @author Adrian Lopez
 * @date 19 Sep 2019
 * @brief Gui movie componet for seing details of the movie
 *
 * The image, year and name of the movie are display in and save in a gtk component for using in the main window
 */

#include "MovieComponent.h"

/*!
This function is called to create the movie box with the year, image and name
@param[in]  *Movie_node  This is the movie node that the method uses to optain all important parameters of the movie and display it
@param[in]  prefwidth   the width that is preffered to set in the main window and it scales the height based on this parameter
*/
GtkWidget* MovieComponent::newmovie_box(Movie_node* movie, int prefwidth){
    movie_year=gtk_label_new("");
    movie_name=gtk_label_new("");
    movie_image=gtk_image_new();
    GtkWidget* mainbox;


    gtk_image_set_from_file(GTK_IMAGE(movie_image),movie->image.c_str());

/**
* Cpix buf to allocate image
*/

    GdkPixbuf *pixbuf =	gtk_image_get_pixbuf(GTK_IMAGE(movie_image));

    pixbuf = gdk_pixbuf_scale_simple(pixbuf, prefwidth,prefwidth*gdk_pixbuf_get_height(pixbuf)/gdk_pixbuf_get_width(pixbuf), GDK_INTERP_BILINEAR);

/**
* Text properties to be display and sizes
*/

    gtk_image_set_from_pixbuf(GTK_IMAGE(movie_image), pixbuf);



    gtk_label_set_text(GTK_LABEL(movie_name),movie->name.c_str());
    gtk_label_set_line_wrap(GTK_LABEL(movie_name),TRUE);
    gtk_label_set_text(GTK_LABEL(movie_year),movie->year.c_str());

    GtkWidget *button2 = gtk_button_new ();

    gtk_button_set_image (GTK_BUTTON (button2), movie_image);
    gtk_widget_set_size_request(button2,20,20);



    mainbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(mainbox,FALSE);
    gtk_widget_set_size_request(mainbox,20,20);

    gtk_box_pack_start (GTK_BOX (mainbox), button2, TRUE,TRUE, 2);
    gtk_box_pack_start (GTK_BOX (mainbox), movie_name, TRUE,TRUE, 2);
    gtk_box_pack_start (GTK_BOX (mainbox), movie_year, TRUE,TRUE, 2);
    gtk_widget_modify_font (movie_name,pango_font_description_from_string ("Arial bold"));
    GdkColor color;
    gdk_color_parse ("white", &color);
    gtk_widget_modify_fg (movie_name, GTK_STATE_NORMAL, &color);
    gtk_widget_modify_font (movie_year,pango_font_description_from_string ("Arial bold"));
    gtk_widget_modify_fg (movie_year, GTK_STATE_NORMAL, &color);
    GdkRGBA colornew;
    gdk_rgba_parse(&colornew, "blue");
    gtk_widget_override_background_color(GTK_WIDGET(movie_name), GTK_STATE_FLAG_NORMAL, &colornew);
    gtk_widget_override_background_color(GTK_WIDGET(movie_year), GTK_STATE_FLAG_NORMAL, &colornew);


    const gchar *key="Movie name";
    /**
* Put data to the object in order to identify it's callback
*/

    g_object_set_data (G_OBJECT(mainbox),key,movie);
    g_signal_connect(button2, "clicked",G_CALLBACK(clicked), g_object_get_data(G_OBJECT(mainbox),key));
    return mainbox;

}
