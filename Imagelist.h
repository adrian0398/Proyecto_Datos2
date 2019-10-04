//
// Created by adrian on 4/10/19.
//

#ifndef PROYECTO1_DATOS2_IMAGELIST_H
#define PROYECTO1_DATOS2_IMAGELIST_H

#include <iostream>


using namespace std;

class Image_node {
public:
    char* image_url;
    Image_node* next=NULL;
};

class Imagelist {

private:


public:
    void insert(char* new_data) {
        Image_node* new_node=new Image_node;
        Image_node* last=head;
        new_node->image_url = new_data;
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
        Image_node* tmp=head;
        while (tmp != NULL){
            if (tmp->image_url== value)
            {
                printf("key found\n");
                cout <<tmp->image_url;
                return;
            }
            tmp= tmp->next;
        }
        printf("Key not found\n");
    }
    void deleteKey( char* key)
    {
        // Store head node
        Image_node* temp = head;
        Image_node *prev;

        // If head node itself holds the key or multiple occurrences of key
        while (temp != NULL && temp->image_url == key)
        {
            head = temp->next;   // Changed head
            free(temp);               // free old head
            temp = head;         // Change Temp
        }

        // Delete occurrences other than head
        while (temp != NULL)
        {
            // Search for the key to be deleted, keep track of the
            // previous node as we need to change 'prev->next'
            while (temp != NULL && temp->image_url != key)
            {
                prev = temp;
                temp = temp->next;
            }

            // If key was not present in linked list
            if (temp == NULL) return;

            // Unlink the node from linked list
            prev->next = temp->next;

            free(temp);  // Free memory

            //Update Temp for next iteration of outer loop
            temp = prev->next;
        }
    }

    int getsize() {
        int size=0;
        Image_node* ptr=new Image_node;
        ptr = head;
        while (ptr != NULL) {
            ptr = ptr->next;
            size=size+1;
        }
        return size;
    }












    Image_node* head = NULL;
};




#endif //PROYECTO1_DATOS2_IMAGELIST_H
