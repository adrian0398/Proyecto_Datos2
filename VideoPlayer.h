//
// Created by adrian on 19/9/19.
//

#ifndef PROJECTS_VIDEOPLAYER_H
#define PROJECTS_VIDEOPLAYER_H
#include <gtk/gtk.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <string>

#include <gdk/gdk.h>

#include <gdk/gdkx.h>



class VideoPlayer {
/* Structure to contain all our information, so we can pass it around */
    typedef struct _CustomData {
        GstElement *playbin;           /* Our one and only pipeline */

        GtkWidget *slider;              /* Slider widget to keep track of current position */
        GtkWidget *streams_list;        /* Text widget to display info about the streams */
        gulong slider_update_signal_id; /* Signal ID for the slider update signal */

        GstState state;                 /* Current state of the pipeline */
        gint64 duration;                /* Duration of the clip, in nanoseconds */
    } CustomData;

/* This function is called when the GUI toolkit creates the physical window that will hold the video.
 * At this point we can retrieve its handler (which has a different meaning depending on the windowing system)
 * and pass it to GStreamer through the VideoOverlay interface. */
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

/* This function is called when the PLAY button is clicked */
    static void play_cb (GtkButton *button, CustomData *data) {
        gst_element_set_state (data->playbin, GST_STATE_PLAYING);
    }

/* This function is called when the PAUSE button is clicked */
    static void pause_cb (GtkButton *button, CustomData *data) {
        gst_element_set_state (data->playbin, GST_STATE_PAUSED);
    }

/* This function is called when the STOP button is clicked */
    static void stop_cb (GtkButton *button, CustomData *data) {
        gst_element_set_state (data->playbin, GST_STATE_READY);
    }

/* This function is called when the main window is closed */
    static void delete_event_cb (GtkWidget *widget, GdkEvent *event, CustomData *data) {
        stop_cb (NULL, data);
        gtk_main_quit ();
    }

/* This function is called everytime the video window needs to be redrawn (due to damage/exposure,
 * rescaling, etc). GStreamer takes care of this in the PAUSED and PLAYING states, otherwise,
 * we simply draw a black rectangle to avoid garbage showing up. */
    static gboolean draw_cb (GtkWidget *widget, cairo_t *cr, CustomData *data) {
        if (data->state < GST_STATE_PAUSED) {
            GtkAllocation allocation;

            /* Cairo is a 2D graphics library which we use here to clean the video window.
             * It is used by GStreamer for other reasons, so it will always be available to us. */
            gtk_widget_get_allocation (widget, &allocation);
            cairo_set_source_rgb (cr, 0, 0, 0);
            cairo_rectangle (cr, 0, 0, allocation.width, allocation.height);
            cairo_fill (cr);
        }

        return FALSE;
    }

/* This function is called when the slider changes its position. We perform a seek to the
 * new position here. */
    static void slider_cb (GtkRange *range, CustomData *data) {
        gdouble value = gtk_range_get_value (GTK_RANGE (data->slider));
        gst_element_seek_simple (data->playbin, GST_FORMAT_TIME,
                                 static_cast<GstSeekFlags>(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT),
                                 (gint64)(value * GST_SECOND));
    }

/* This creates all the GTK+ widgets that compose our application, and registers the callbacks */

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
        movie_year="Year: "+movie_year;
        yearlbl=gtk_label_new(movie_year.c_str());

        summarylbl=gtk_label_new(movie_summary.c_str());

        movie_director="Director: "+movie_director;
        directorlbl=gtk_label_new(movie_director.c_str());


        movie_ranking="Ranking: "+movie_ranking;
        rankinglbl=gtk_label_new(movie_ranking.c_str());

        gtk_widget_modify_font (namelbl,pango_font_description_from_string ("Arial bold 80"));
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

/* This function is called periodically to refresh the GUI */
    static gboolean refresh_ui (CustomData *data) {
        gint64 current = -1;

        /* We do not want to update anything unless we are in the PAUSED or PLAYING states */
        if (data->state < GST_STATE_PAUSED)
            return TRUE;

        /* If we didn't know it yet, query the stream duration */
        if (!GST_CLOCK_TIME_IS_VALID (data->duration)) {
            if (!gst_element_query_duration (data->playbin, GST_FORMAT_TIME, &data->duration)) {
                g_printerr ("Could not query current duration.\n");
            } else {
                /* Set the range of the slider to the clip duration, in SECONDS */
                gtk_range_set_range (GTK_RANGE (data->slider), 0, (gdouble)data->duration / GST_SECOND);
            }
        }

        if (gst_element_query_position (data->playbin, GST_FORMAT_TIME, &current)) {
            /* Block the "value-changed" signal, so the slider_cb function is not called
             * (which would trigger a seek the user has not requested) */
            g_signal_handler_block (data->slider, data->slider_update_signal_id);
            /* Set the position of the slider to the current pipeline positoin, in SECONDS */
            gtk_range_set_value (GTK_RANGE (data->slider), (gdouble)current / GST_SECOND);
            /* Re-enable the signal */
            g_signal_handler_unblock (data->slider, data->slider_update_signal_id);
        }
        return TRUE;
    }

/* This function is called when new metadata is discovered in the stream */
    static void tags_cb (GstElement *playbin, gint stream, CustomData *data) {
        /* We are possibly in a GStreamer working thread, so we notify the main
         * thread of this event through a message in the bus */
        gst_element_post_message (playbin,
                                  gst_message_new_application (GST_OBJECT (playbin),
                                                               gst_structure_new_empty ("tags-changed")));
    }

/* This function is called when an error message is posted on the bus */
    static void error_cb (GstBus *bus, GstMessage *msg, CustomData *data) {
        GError *err;
        gchar *debug_info;

        /* Print error details on the screen */
        gst_message_parse_error (msg, &err, &debug_info);
        g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
        g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
        g_clear_error (&err);
        g_free (debug_info);

        /* Set the pipeline to READY (which stops playback) */
        gst_element_set_state (data->playbin, GST_STATE_READY);
    }

/* This function is called when an End-Of-Stream message is posted on the bus.
 * We just set the pipeline to READY (which stops playback) */
    static void eos_cb (GstBus *bus, GstMessage *msg, CustomData *data) {
        g_print ("End-Of-Stream reached.\n");
        gst_element_set_state (data->playbin, GST_STATE_READY);

    }

/* This function is called when the pipeline changes states. We use it to
 * keep track of the current state. */
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


        /* Connect to interesting signals in playbin */
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

        /* Start playing */
        ret = gst_element_set_state (data.playbin, GST_STATE_PLAYING);
        if (ret == GST_STATE_CHANGE_FAILURE) {
            g_printerr ("Unable to set the pipeline to the playing state.\n");
            gst_object_unref (data.playbin);
        }

        /* Register a function that GLib will call every second */
        g_timeout_add_seconds (1, (GSourceFunc)refresh_ui, &data);

        /* Start the GTK main loop. We will not regain control until gtk_main_quit is called. */
        gtk_main ();

        /* Free resources */
        gst_element_set_state (data.playbin, GST_STATE_NULL);
        gst_object_unref (data.playbin);
    }
};


#endif //PROJECTS_VIDEOPLAYER_H
