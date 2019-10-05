//
// Created by adrian on 15/9/19.
//

/**
 * @file Html.h
 * @author Adrian Lopez
 * @date 15 Set 2019
 * @brief Header file to declare functions dor Html get request
 *
 */

#ifndef PROJECTS_HTML_H
#define PROJECTS_HTML_H

#include <iostream>
#include <string>
#include <curl/curl.h> //your directory may be different
#include <regex>
#include <json/json.h>
#include <gtk/gtk.h>



using namespace std;
/*!
*This class uses the IMBD link of the movies to search for the poster, the summary and the video
*/
class Html {


//will hold the url's contents

/*!
This function is called to write to a string to make a html get request.
*/
public:


    static size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {

        data->append((char*) ptr, size * nmemb);

        return size * nmemb;

    }
/*!
This function is called to get url from URL
 @param[in]  nam of the movie
@param[in]  Imbdlink to search
@return string url
*/
    string get_url(string Imbdlink, string name);

/*!
This function is called to get pic from URL
@param[in]  response_string   URL to search
 @param[in]  name of the movie
 @return string pic
*/

    string get_pic(string response_string, string name);

/*!
This function is called to get summary from URL
@param[in]  response_string   URL to search
 @param[in]  name of the movie
 @return string summary
*/
    string get_summary(string response_string);
/*!
This function is called to get video trailer from URL
@param[in]  *response_string   URL to search
 @return string video url
*/
    string get_video_url(string response_string);

/*!
This function is called to get video trailer from URL
@param[in]  *response_string   URL to search
 @param[in]  *name of the movie
 @return string video_trailer
*/
    void get_video_trailer(string response_string );



};


#endif //PROJECTS_HTML_H
