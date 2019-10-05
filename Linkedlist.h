//
// Created by adrian on 14/9/19.
//

/**
 * @file Linkedlist.h
 * @author Adrian Lopez
 * @date 14 Sep 2019
 * @brief File to create normal linked list of Nodes
 *
 * Declares methods for easy manipulation of linked lists
 */

#ifndef PROJECTS_LINKEDLIST_H
#define PROJECTS_LINKEDLIST_H

#include <string>
#include <iostream>



using namespace std;
/*!
*Node that saves the data of the movie
*/

class Node {
public:
    string name;  /**< Movie name from CSV*/
    string director;  /**< Movie director from CSV*/
    string year;   /**< Movie year from CSV*/
    string IMBDlink; /**< Movie IMBDlin form CSV*/
    string ranking; /**< Movie ranking from CSV*/
    Node* next;  /**< reference*/
};
/*!
*Linked list to save all the movies get from the csv
*/
class Linkedlist {

    /*!
   *Linked list method to display the linked list
   * Use tmp node to display each node until linked list is NULL

   */
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
