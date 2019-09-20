//
// Created by adrian on 14/9/19.
//

#ifndef PROJECTS_LINKEDLIST_H
#define PROJECTS_LINKEDLIST_H

#include <string>
#include <iostream>



using namespace std;

class Node {
public:
    string name;
    string director;
    string year;
    string IMBDlink;
    string ranking;
    Node* next;
};

class Linkedlist {


private:
    void display(){
        Node* ptr=new Node;
        ptr = head;
        while (ptr != NULL) {
            std::cout<< ptr->name <<" ";
            ptr = ptr->next;
        }
    }

public:
    void insert(string new_data, string year, string IMBDlink, string ranking,string director) {
        Node* new_node=new Node;
        Node* last=head;
        new_node->name = new_data;
        new_node->year = year;
        new_node->IMBDlink = IMBDlink;
        new_node->ranking = ranking;
        new_node->director = director;
        new_node->next = NULL;


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
        Node* tmp=head;
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

    Node* head = new Node;
};


#endif //PROJECTS_LINKEDLIST_H
