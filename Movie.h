//
// Created by adrian on 14/9/19.
//

#ifndef PROJECTS_MOVIE_H
#define PROJECTS_MOVIE_H

#include <string>
#include <iostream>
#include <gtk/gtk.h>
#include "Html.h"



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
    Movie_node* next;

};


class Movie {

private:
    void display() {
        Movie_node* ptr=new Movie_node;
        ptr = head;
        while (ptr != NULL) {
            std::cout<< ptr->name <<" ";
            ptr = ptr->next;
        }
    };

public:
    void insert(string new_data, string year, string IMBDlink, string ranking, string director) {
        Movie_node* new_node = new Movie_node;
        Movie_node* last=head;
        new_node->name = new_data;
        new_node->year = year;
        new_node->IMBDlink = IMBDlink;
        new_node->ranking = ranking;
        new_node->director = director;
        new_node->next = NULL;
        Html html;
        string url=html.get_url(IMBDlink,new_data);
        new_node->image=html.get_pic(url,new_data);
        new_node->Summary=html.get_summary(url);
        cout<<"vea--------------------------------------";
        cout<<new_node->Summary;
        new_node->videoURl=html.get_video_url(url);


        if (head == NULL)
        {
            head = new_node;
            return;
        }

        while (last->next != NULL)
            last = last->next;

        last->next = new_node;
        return;
    }

    void search(string value){

        Movie_node* tmp=head;
        while (tmp != NULL){
            if (tmp->name == value)
            {
                printf("key found\n");
                cout <<tmp->name<<tmp->IMBDlink<<tmp->year;
                return;
            }
            tmp= tmp->next;
        }
        printf("Key not found\n");
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
        printf("Key not found\n");
    }

    Movie_node* head = new Movie_node;
};



#endif //PROJECTS_MOVIE_H
