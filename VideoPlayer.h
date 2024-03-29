//
// Created by adrian on 19/9/19.
//

/**
 * @file VideoPlayer.h
 * @author Adrian Lopez
 * @date 19 Sep 2019
 * @brief Class for playing the video in streaming
 *
 * The class creates another gtk window and shows details of the movie and streams the video.
 */



#ifndef PROJECTS_VIDEOPLAYER_H
#define PROJECTS_VIDEOPLAYER_H
#include <gtk/gtk.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <string>

#include <gdk/gdk.h>

#include <gdk/gdkx.h>
#include <iostream>


/**
* A class to play videos and show a second window to show important details of the movie
*/
class VideoPlayer {
/**
* Structure to contain all info of streaming and pass it throught methods
*/

    typedef struct _CustomData {
        /*@{*/
        GstElement *playbin;  /**< pipeline */

        GtkWidget *slider;     /**< slider to pause and play  */
        GtkWidget *streams_list;    /**< Text widget to display info */
        gulong slider_update_signal_id; /**< slider update*/

        GstState state;      /**< playing state */
        gint64 duration;       /**< duration of stream */
        /*@}*/
    } CustomData;


/*!
This function is called when the GUI toolkit creates the physical window that will hold the video.
 * and pass it to GStreamer.
@param[in]  *widget   Main window widget
@param[in]  *data    data passed
*/

    static void realize_cb (GtkWidget *widget, CustomData *data) {
        GdkWindow *window = gtk_widget_get_window (widget);
        guintptr window_handle;

        if (!gdk_window_ensure_native (window))
            g_error ("Couldn't create native window needed for GstVideoOverlay!");

        /* Retrieve window handler from GDK */
#if defined (GDK_WINDOWING_WIN32)
        window_handle = (guintptr)GDK_WINDOW_HWND (window);
#elif defined (GDK_WINDOWING_QUARTZ)
        window_handle = gdk_quartz_window_get_nsview (window);
#elif defined (GDK_WINDOWING_X11)
        window_handle = GDK_WINDOW_XID (window);
#endif
        /* Pass it to playbin, which implements VideoOverlay and will forward it to the video sink */
        gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (data->playbin), window_handle);
    }

/*!
This function is called when the play button is clicked.
@param[in]  *button   Button object
@param[in]  *data    data passed
*/
    static void play_cb (GtkButton *button, CustomData *data) {
        gst_element_set_state (data->playbin, GST_STATE_PLAYING);
    }

/*!
This function is called when the play button is clicked.
@param[in]  *button   Button object
@param[in]  *data    data passed
*/
    static void pause_cb (GtkButton *button, CustomData *data) {
        gst_element_set_state (data->playbin, GST_STATE_PAUSED);
    }

/*!
This function is called when the play stop is clicked.

@param[in]  *button   Button object
@param[in]  *data    data passed
*/
    static void stop_cb (GtkButton *button, CustomData *data) {
        gst_element_set_state (data->playbin, GST_STATE_READY);
    }

/*!
This function is called when the main window is closed.
@param[in]  *Widget   window closed
@param[in]  *data    data passed
 @param[in]  *event   closed event
*/
    static void delete_event_cb (GtkWidget *widget, GdkEvent *event, CustomData *data) {

        std::cout<<"sali"<<std::endl;

        gtk_main_quit();
    }
/*!
This function obtains the info of the elements
@param[in]  *GSTElement
@param[in]  *element   elements info
*/
    static void info(const GstElement *const element)
    {
        std::cout << "count: " << GST_OBJECT_REFCOUNT(element) << std::endl;

    }

/*!
This function is called  to draw to enable streaming, Cairo is a 2D graphics library which we use here to clean the video window.
@param[in]  *widget  Where the video is
@param[in]  *data    data passed that is the info of the video
*/
    static gboolean draw_cb (GtkWidget *widget, cairo_t *cr, CustomData *data) {
        if (data->state < GST_STATE_PAUSED) {
            GtkAllocation allocation;

            gtk_widget_get_allocation (widget, &allocation);
            cairo_set_source_rgb (cr, 0, 0, 0);
            cairo_rectangle (cr, 0, 0, allocation.width, allocation.height);
            cairo_fill (cr);
        }

        return FALSE;
    }
/*!
This function is called  when the slider change the position so a refresh is needed.
@param[in]  *range  range of the slider.
@param[in]  *data    data passed that is the info of the video
*/
    static void slider_cb (GtkRange *range, CustomData *data) {
        gdouble value = gtk_range_get_value (GTK_RANGE (data->slider));
        gst_element_seek_simple (data->playbin, GST_FORMAT_TIME,
                                 static_cast<GstSeekFlags>(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT),
                                 (gint64)(value * GST_SECOND));
    }


/*!
 * Creation of GTK widgets and use of callbacks
@param[in]  *movie_name  movie info to be display on the main window
@param[in]  *movie_summary movie info to be display on the main window
@param[in]  *movie_director  movie info to be display on the main window
@param[in]  *movie_imagename  movie info to be display on the main window
@param[in]  *movie_movie_ranking  movie info to be display on the main window
@param[in]  *data    data passed that is the info of the video
*/

    static void create_ui (CustomData *data,std::string movie_name,std::string movie_year,std::string movie_summary,std::string movie_director,std::string movie_imagename,std::string movie_ranking) {
        GtkWidget *main_window;  /* The uppermost window, containing all other windows */
        GtkWidget *video_window; /* The drawing area where the video will be shown */
        GtkWidget *main_box;     /* VBox to hold main_hbox and the controls */
        GtkWidget *main_hbox;    /* HBox to hold the video_window and the stream info text widget */
        GtkWidget *controls;     /* HBox to hold the buttons and the slider */
        GtkWidget *play_button, *pause_button, *stop_button; /* Buttons */

        main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
        gtk_window_set_title(GTK_WINDOW(main_window),"TEC_Flix");

        gtk_window_set_resizable (GTK_WINDOW(main_window), FALSE);
        GtkWidget *prueba;
        prueba= gtk_layout_new(NULL, NULL);
        //gtk_container_add(GTK_CONTAINER (main_window), prueba);
        GtkWidget *image;
        image = gtk_image_new_from_file("background_tecflix.jpg");
        gtk_layout_put(GTK_LAYOUT(prueba), image, 0, 0);


        //callbacks in the program
        g_signal_connect (G_OBJECT (main_window), "delete-event", G_CALLBACK (delete_event_cb), data);

        video_window = gtk_drawing_area_new ();
        gtk_widget_set_double_buffered (video_window, FALSE);
        g_signal_connect (video_window, "realize", G_CALLBACK (realize_cb), data);
        g_signal_connect (video_window, "draw", G_CALLBACK (draw_cb), data);

        play_button = gtk_button_new_from_icon_name ("media-playback-start", GTK_ICON_SIZE_SMALL_TOOLBAR);
        g_signal_connect (G_OBJECT (play_button), "clicked", G_CALLBACK (play_cb), data);

        pause_button = gtk_button_new_from_icon_name ("media-playback-pause", GTK_ICON_SIZE_SMALL_TOOLBAR);
        g_signal_connect (G_OBJECT (pause_button), "clicked", G_CALLBACK (pause_cb), data);

        stop_button = gtk_button_new_from_icon_name ("media-playback-stop", GTK_ICON_SIZE_SMALL_TOOLBAR);
        g_signal_connect (G_OBJECT (stop_button), "clicked", G_CALLBACK (stop_cb), data);

        data->slider = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
        gtk_scale_set_draw_value (GTK_SCALE (data->slider), 0);
        data->slider_update_signal_id = g_signal_connect (G_OBJECT (data->slider), "value-changed", G_CALLBACK (slider_cb), data);

        data->streams_list = gtk_text_view_new ();
        gtk_text_view_set_left_margin (GTK_TEXT_VIEW(data->streams_list), 0);
        gtk_text_view_set_editable (GTK_TEXT_VIEW (data->streams_list), FALSE);

        controls = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_box_pack_start (GTK_BOX (controls), play_button, FALSE, FALSE, 2);
        gtk_box_pack_start (GTK_BOX (controls), pause_button, FALSE, FALSE, 2);
        gtk_box_pack_start (GTK_BOX (controls), stop_button, FALSE, FALSE, 2);
        gtk_box_pack_start (GTK_BOX (controls), data->slider, TRUE, TRUE, 2);

/**
* Creation of the window gui, with labels and the stream video.
*/


        GtkWidget* fixed;
        GtkWidget* namelbl;
        GtkWidget* yearlbl;
        GtkWidget* summarylbl;
        GtkWidget* directorlbl;
        GtkWidget* rankinglbl;
        GtkWidget* imager;

        fixed= gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(prueba), fixed);
        namelbl=gtk_label_new(movie_name.c_str());
        //gtk_label_set_line_wrap(GTK_LABEL(namelbl),TRUE);
        movie_year="Year: "+movie_year;
        yearlbl=gtk_label_new(movie_year.c_str());

        summarylbl=gtk_label_new(movie_summary.c_str());

        movie_director="Director: "+movie_director;
        directorlbl=gtk_label_new(movie_director.c_str());

        movie_ranking="Ranking: "+movie_ranking;
        rankinglbl=gtk_label_new(movie_ranking.c_str());

        std::string tmp=gtk_label_get_text(GTK_LABEL(namelbl));
        std::string style ="Arial bold ";
        int sizenum=60/tmp.length() * 5+20;
        std::string size = std::to_string(sizenum);
        style += size;
        gtk_widget_modify_font (namelbl,pango_font_description_from_string (style.c_str()));
        GdkColor color;
        gdk_color_parse ("white", &color);
        gtk_widget_modify_fg (namelbl, GTK_STATE_NORMAL, &color);
        gtk_fixed_put(GTK_FIXED(fixed), namelbl, 400, 0);

        gtk_widget_modify_font (yearlbl,pango_font_description_from_string ("Arial bold 20"));
        gtk_widget_modify_fg (yearlbl, GTK_STATE_NORMAL, &color);

        gtk_fixed_put(GTK_FIXED(fixed), yearlbl, 50, 150);

        gtk_widget_modify_font (summarylbl,pango_font_description_from_string ("Arial bold 10"));
        gtk_widget_modify_fg (summarylbl, GTK_STATE_NORMAL, &color);

        gtk_fixed_put(GTK_FIXED(fixed), summarylbl, 50, 300);

        gtk_widget_modify_font (directorlbl,pango_font_description_from_string ("Arial bold 20"));
        gtk_widget_modify_fg (directorlbl, GTK_STATE_NORMAL, &color);

        gtk_fixed_put(GTK_FIXED(fixed), directorlbl, 50, 175);

        gtk_widget_modify_font (rankinglbl,pango_font_description_from_string ("Arial bold 20"));
        gtk_widget_modify_fg (rankinglbl, GTK_STATE_NORMAL, &color);

        gtk_fixed_put(GTK_FIXED(fixed), rankinglbl, 50, 200);

        imager=gtk_image_new();
        gtk_image_set_from_file(GTK_IMAGE(imager),movie_imagename.c_str());
        gtk_fixed_put(GTK_FIXED(fixed), imager, 1100, 0);


        main_hbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
        gtk_box_pack_start (GTK_BOX (main_hbox), video_window, TRUE, TRUE, 0);
        //gtk_widget_set_size_request(prueba,10,10);
        //gtk_container_add (GTK_CONTAINER (prueba), data->streams_list);
        main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
        gtk_box_pack_start (GTK_BOX (main_box), prueba, TRUE, TRUE, 0);
        gtk_box_pack_start (GTK_BOX (main_box), main_hbox, TRUE, TRUE, 0);

        gtk_box_pack_start (GTK_BOX (main_box), controls, FALSE, FALSE, 0);
        gtk_container_add (GTK_CONTAINER (main_window), main_box);







        gtk_window_set_default_size (GTK_WINDOW (main_window), 1300, 800);

        gtk_widget_show_all (main_window);
    }

/*!
 * This method is call to refresh the UI
@param[in]  *data    data passed that is the info of the video
*/
    static gboolean refresh_ui (CustomData *data) {
        gint64 current = -1;

        if (data->state < GST_STATE_PAUSED)
            return TRUE;


        if (!GST_CLOCK_TIME_IS_VALID (data->duration)) {
            if (!gst_element_query_duration (data->playbin, GST_FORMAT_TIME, &data->duration)) {
                g_printerr ("Could not query current duration.\n");
            } else {
                /* Set the range of the slider to the clip duration, in SECONDS */
                gtk_range_set_range (GTK_RANGE (data->slider), 0, (gdouble)data->duration / GST_SECOND);
            }
        }


        return TRUE;
    }

/*!
 * Call when new metadata is descover
@param[in]  *data    data passed that is the info of the video
 @param[in]  *playbin  pipeline
*/
    static void tags_cb (GstElement *playbin, gint stream, CustomData *data) {

        gst_element_post_message (playbin,
                                  gst_message_new_application (GST_OBJECT (playbin),
                                                               gst_structure_new_empty ("tags-changed")));
    }

/*!
 * This method is call if some error ocurre in execution
 @param[in]  *bus bus that passes the data
 @param[in]  *msg error message
@param[in]  *data    data passed that is the info of the video
*/
    static void error_cb (GstBus *bus, GstMessage *msg, CustomData *data) {
        GError *err;
        gchar *debug_info;


        gst_message_parse_error (msg, &err, &debug_info);
        g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
        g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
        g_clear_error (&err);
        g_free (debug_info);


        gst_element_set_state (data->playbin, GST_STATE_READY);
    }

/*!
 * This method is call if some error ocurre in execution
 @param[in]  *bus bus that passes the data
 @param[in]  *msg error message
@param[in]  *data    data passed that is the info of the video
*/
    static void eos_cb (GstBus *bus, GstMessage *msg, CustomData *data) {
        g_print ("End-Of-Stream reached.\n");
        gst_element_set_state (data->playbin, GST_STATE_READY);

    }

/*!
 * This method is call when the state changed as a callback
 @param[in]  *bus bus that passes the data
 @param[in]  *msg message
@param[in]  *data    data passed that is the info of the video
*/
    static void state_changed_cb (GstBus *bus, GstMessage *msg, CustomData *data) {
        GstState old_state, new_state, pending_state;
        gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
        if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data->playbin)) {
            data->state = new_state;
            g_print ("State set to %s\n", gst_element_state_get_name (new_state));
            if (old_state == GST_STATE_READY && new_state == GST_STATE_PAUSED) {
                /* For extra responsiveness, we refresh the GUI as soon as we reach the PAUSED state */
                refresh_ui (data);
            }
        }
    }


public:
    /*!
 * This method starts the videoplayer
     * Receives the movie properties and inits the gtk, this will put order to other methods.
 @param[in]  movie variables variables of the movie are pass to be saved and display on the window.
*/
    void start_videoplayer(std::string movie_name,std::string movie_year,std::string movie_summary,std::string movie_director,std::string movie_imagename,std::string movie_ranking,std::string movieurl) {
        CustomData data;
        GstStateChangeReturn ret;
        GstBus *bus;

        /* Initialize GTK */

        gtk_init (NULL, NULL);

        /* Initialize GStreamer */
        gst_init (NULL, NULL);

        /* Initialize our data structure */
        memset (&data, 0, sizeof (data));
        data.duration = GST_CLOCK_TIME_NONE;

        /* Create the elements */
        data.playbin = gst_element_factory_make ("playbin", "playbin");

        if (!data.playbin) {
            g_printerr ("Not all elements could be created.\n");
        }

        g_printerr ("aaa//n");
        g_printerr (movie_summary.c_str());
        g_printerr ("bbbbb//n");

        g_object_set (data.playbin, "uri", movieurl.c_str(), NULL);

        /**
* Conect signals to the playbin
*/
        g_signal_connect (G_OBJECT (data.playbin), "video-tags-changed", (GCallback) tags_cb, &data);
        g_signal_connect (G_OBJECT (data.playbin), "audio-tags-changed", (GCallback) tags_cb, &data);
        g_signal_connect (G_OBJECT (data.playbin), "text-tags-changed", (GCallback) tags_cb, &data);

        /* Create the GUI */


        create_ui (&data,movie_name,movie_year,movie_summary,movie_director,movie_imagename,movie_ranking);

        /* Instruct the bus to emit signals for each received message, and connect to the interesting signals */
        bus = gst_element_get_bus (data.playbin);
        gst_bus_add_signal_watch (bus);
        g_signal_connect (G_OBJECT (bus), "message::error", (GCallback)error_cb, &data);
        g_signal_connect (G_OBJECT (bus), "message::eos", (GCallback)eos_cb, &data);
        g_signal_connect (G_OBJECT (bus), "message::state-changed", (GCallback)state_changed_cb, &data);

        gst_object_unref (bus);

/**
* Start streaming and playing.
*/
        ret = gst_element_set_state (data.playbin, GST_STATE_PLAYING);
        if (ret == GST_STATE_CHANGE_FAILURE) {
            g_printerr ("Unable to set the pipeline to the playing state.\n");
            gst_object_unref (data.playbin);
        }


        g_timeout_add_seconds (1, (GSourceFunc)refresh_ui, &data);

        gtk_main ();

/**
* Free memory resources
*/

        gst_element_set_state(data.playbin, GST_STATE_NULL);
        data.state=GST_STATE_NULL;
        gst_object_unref(GST_OBJECT(data.playbin));
        gst_task_cleanup_all();




    }
};


#endif //PROJECTS_VIDEOPLAYER_H
