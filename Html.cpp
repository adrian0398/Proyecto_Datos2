//
// Created by adrian on 15/9/19.
//

/**
 * @file Html.cpp
 * @author Adrian Lopez
 * @date  15 Set 2019
 * @brief File containing methods to get Html get request from Imdb.
 *
 * Usage of curl library to read and parse strings to obtain url to images, video and summary.
 */






#include "Html.h"


string Html::get_url(string Imbdlink, string name){
    CURL *curl; //our curl object
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, Imbdlink.c_str());
    std::string response_string;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Html::writeFunction);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);

    return response_string;

}

string Html::get_pic(string response_string, string name){
    string movie_link = "";

    std::string s(response_string);
    std::smatch m;
    std::regex e(
            "\\b(Poster\" title=)[a-zA-Z0-9_\"':\\t\\r\\n\\v\\f!#$%&()*+,./:;=?@\\^_`{|}~\\-\\ñÑáéíóúÁÉÍÓÚ\\s· ]+(.jpg)\\b");   // matches words beginning by "sub"


    std::regex_search(s, m, e);
    for (auto x:m) {
        movie_link.append(x);
    }


    movie_link=movie_link.substr(movie_link.find("https"));
    movie_link=movie_link.substr(0,movie_link.size()-18);


    CURL *image;
    CURLcode imgresult;
    string imagename=name;
    imagename.append(".jpg");
    FILE *fp = nullptr;
    const char *url = movie_link.c_str();
    image = curl_easy_init();
    if (image)
    {
        // Open file
        fp = fopen(imagename.c_str(), "wb");
        if (fp == NULL) cout << "File cannot be opened";

        curl_easy_setopt(image, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(image, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(image, CURLOPT_URL, url);
        // Grab image
        imgresult = curl_easy_perform(image);
        if (imgresult)
            cout << "Cannot grab the image!\n";
    }
    // Clean up the resources
    curl_easy_cleanup(image);
    // Close the file
    fclose(fp);

    GError *error = NULL;
    GdkPixbuf *pix = gdk_pixbuf_new_from_file (imagename.c_str(), &error);
    if (pix == NULL) {
        g_printerr ("Error loading file: #%d %s\n", error->code, error->message);
        g_error_free (error);
        exit (1);
    }

    return imagename;
}

string Html::get_summary(string response_string){
    std::string s(response_string);

    std::smatch m1;
    std::regex e1(
            "\\b(summary)[a-zA-Z0-9_\"':\\t\\r\\n\\v\\f!#$%&()*+,./:;=?>@\\^_`{|}~\\-\\ ]+(.)\\b");   // matches words beginning by "sub"


    string movie_history = "";
    std::regex_search(s, m1, e1);
    for (auto x1:m1) {
        movie_history.append(x1);
    }
    // History modify

    movie_history=movie_history.substr(14,movie_history.size()-22);


    return movie_history;
}

string Html::get_video_url(string response_string){
    string data="";
    std::string s(response_string);
    std::smatch m2;
    std::regex e2 ("\\b(href)[a-zA-Z0-9_\"':\\t\\r\\n\\v\\f!#$%&()*+,./:;=?>@\\^_`{|}~\\-\\ ]+(video)\\b");   // matches words beginning by "sub"


    string movie_video="";
    std::regex_search (s,m2,e2);
    for (auto x2:m2) {
        movie_video.append(x2) ;
    }

    //Video modify



    movie_video=movie_video.substr(6,movie_video.find("class"));
    movie_video=movie_video.substr(0,movie_video.size()-8);
    movie_video=movie_video.insert(0,"https://www.imdb.com");
    movie_video=movie_video.replace(movie_video.find("video/imdb"),10,"videoplayer");


    //search in video URL
    CURL* curl1; //our curl object


    curl1 = curl_easy_init();

    if(curl1) {
        curl_easy_setopt(curl1, CURLOPT_URL, movie_video.c_str());
        //**//* example.com is redirected, so we tell libcurl to follow redirection *//**//*
        curl_easy_setopt(curl1, CURLOPT_WRITEFUNCTION, Html::writeFunction);

        curl_easy_setopt(curl1, CURLOPT_WRITEDATA, &data);
        curl_easy_setopt(curl1, CURLOPT_FOLLOWLOCATION, true);
        curl_easy_setopt(curl1, CURLOPT_USERAGENT, "Dark Secret Ninja/1.0");


        curl_easy_perform(curl1);
        //cout << endl << data << endl;
        curl_easy_cleanup(curl1);
        curl_global_cleanup();
    }


    string movie_video_ultimate="";
    std::string s3 (data);
    std::smatch m3;
    std::regex e3 ("\\b(window.IMDbReactInitialState.push)[a-zA-Z0-9_\"':\\t\\r\\n\\v\\f!#$%&()*+,./:;=?>@\\^_`{|}~\\-\\ ]+(videoMature)\\b");   // matches words beginning by "sub"

    std::regex_search (s3,m3,e3);
    for (auto x3:m3) {
        movie_video_ultimate.append(x3) ;
    }
    movie_video_ultimate=data.substr(data.find("window.IMDbReactInitialState.push("),data.size()-1);
    movie_video_ultimate= movie_video_ultimate.substr(0,movie_video_ultimate.find(");"));
    movie_video_ultimate= movie_video_ultimate.replace(0,34,"");



    Json::Value root;
    Json::Reader reader;

    bool parsingSuccessful = reader.parse( movie_video_ultimate, root, false);
    if ( !parsingSuccessful )
    {
        cout << "Error parsing the string" << endl;
    }

    const Json::Value mynames = root["videos"];
    const Json::Value mynames2 = mynames["videoMetadata"];


    string aux;

    for (auto const& id : mynames2.getMemberNames()) {
        aux=id;
    }

    const Json::Value mynames3 = mynames2[aux];

    const Json::Value myname4= mynames3["encodings"];
    const Json::Value myname5=myname4[0];

    const Json::Value myname6=myname5["videoUrl"];


    //end search in video URL

    return  myname6.asString();
}

void Html::get_video_trailer(string response_string ){

    CURL *video;
    CURLcode videoresult;
    FILE *fp1 = nullptr;
    const char *url1 = response_string.c_str();
    video = curl_easy_init();
    if (video)
    {


        // Open file
        fp1 = fopen("trailer.mp4", "wb");
        if (fp1 == NULL) cout << "File cannot be opened";

        curl_easy_setopt(video, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(video, CURLOPT_WRITEDATA, fp1);
        curl_easy_setopt(video, CURLOPT_URL, url1);
        // Grab image
        videoresult = curl_easy_perform(video);
        if (videoresult)
            cout << "Cannot grab the image1!\n";
    }
    // Clean up the resources
    curl_easy_cleanup(video);
    // Close the file
    fclose(fp1);


}