//
// Created by adrian on 14/9/19.
//

#ifndef PROJECTS_MOVIE_H
#define PROJECTS_MOVIE_H

#include <string>
#include <iostream>
#include <gtk/gtk.h>
#include "Html.h"
#include "Linkedlist.h"


using namespace std;


class Movie_node {


public:
    string name;
    string year;
    string IMBDlink;
    string ranking;
    string Summary;
    string image;
    string videoURl;
    string director;
    Movie_node* next=NULL;

};


class Movie { ;

public:
    void removeFirstNode()
    {

        // Move the head pointer to the next node
        Movie_node* temp = head;
        head = head->next;

        delete temp;

    }

    void insert(string new_data, string year, string IMBDlink, string ranking, string director) {
        Movie_node* new_movie_node = new Movie_node;
        Movie_node* last= head;
        new_movie_node->name = new_data;
        new_movie_node->year = year;
        new_movie_node->IMBDlink = IMBDlink;
        new_movie_node->ranking = ranking;
        new_movie_node->director = director;
        new_movie_node->next = NULL;
        Html html;
        string url=html.get_url(IMBDlink,new_data);
        new_movie_node->image=html.get_pic(url,new_data);
        new_movie_node->Summary=html.get_summary(url);
        cout<<"vea--------------------------------------";
        cout<<new_movie_node->Summary;
        new_movie_node->videoURl=html.get_video_url(url);


        if (head == NULL)
        {
            head = new_movie_node;
            return;
        }

        while (last->next != NULL)
            last = last->next;

        last->next = new_movie_node;
        return;
    }

    bool search(string value){

        Movie_node* tmp=head;
        while (tmp != NULL){
            if (tmp->name == value)
            {

                return true;
            }
            tmp= tmp->next;
        }
        return false;
    }

    Movie_node* node_search(string value){

        Movie_node* tmp=head;
        while (tmp != NULL){
            if (tmp->name == value)
            {
                return tmp;
            }
            tmp= tmp->next;
        }
        return NULL;
    }




    void display() {
        Movie_node* ptr=new Movie_node;
        ptr = head;
        while (ptr != NULL) {
            std::cout<< ptr->name <<" ";
            ptr = ptr->next;
        }
    }

    int getsize() {
        int size=0;
        Movie_node* ptr=new Movie_node;
        ptr = head;
        while (ptr != NULL) {
            ptr = ptr->next;
            size=size+1;
        }
        return size;
    }

    Movie_node* head = NULL;
    void insertready(string new_data, string year, string IMBDlink, string ranking, string director, string image, string Summary, string videoUrl) {
        Movie_node* new_movie_node = new Movie_node;
        Movie_node* last= head;
        new_movie_node->name = new_data;
        new_movie_node->year = year;
        new_movie_node->IMBDlink = IMBDlink;
        new_movie_node->ranking = ranking;
        new_movie_node->director = director;
        new_movie_node->image=image;
        new_movie_node->Summary=Summary;
        new_movie_node->videoURl=videoUrl;

        new_movie_node->next = NULL;






        if (head == NULL)
        {
            head = new_movie_node;
            return;
        }

        while (last->next != NULL) {
            last = last->next;
        }

        last->next = new_movie_node;
        return;
    }




};



#endif //PROJECTS_MOVIE_H
