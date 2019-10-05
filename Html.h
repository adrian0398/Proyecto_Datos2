//
// Created by adrian on 15/9/19.
//

#ifndef PROJECTS_HTML_H
#define PROJECTS_HTML_H

#include <iostream>
#include <string>
#include <curl/curl.h> //your directory may be different
#include <regex>
#include <json/json.h>
#include <gtk/gtk.h>



using namespace std;

class Html {


//will hold the url's contents


public:


    static size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {

        data->append((char*) ptr, size * nmemb);

        return size * nmemb;

    }
    string get_url(string Imbdlink, string name);


    string get_pic(string response_string, string name);
    string get_summary(string response_string);

    string get_video_url(string response_string);


    void get_video_trailer(string response_string );



};


#endif //PROJECTS_HTML_H
