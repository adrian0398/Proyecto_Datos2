//
// Created by adrian on 20/8/19.
//

#ifndef SOCKETSERVER_LINKEDLIST_H
#define SOCKETSERVER_LINKEDLIST_H

#include <iostream>
using namespace std;
struct Movie_node {
    string name;
    string year;
    string ranking;
    string IMBDlink;
    struct Movie_node *next;
};
struct Movie_node* head = NULL;
void insert(string new_data, string year, string IMBDlink, string ranking) {
    struct Movie_node* new_node = (struct Movie_node*) malloc(sizeof(struct Movie_node));
    new_node->name = new_data;
    new_node->year = year;
    new_node->IMBDlink = IMBDlink;
    new_node->ranking = ranking;
    new_node->next = head;
    head = new_node;
}
void display() {
    struct Movie_node* ptr;
    ptr = head;
    while (ptr != NULL) {
        cout<< ptr->name <<" ";
        ptr = ptr->next;
    }
}

void search(string value){
    while (head != NULL){
        if (head->name == value)
        {
            printf("key found\n");
            cout <<head->name<<head->year<<head->ranking<<head->IMBDlink;
            return;
        }
        head = head->next;
    }
    printf("Key not found\n");
}




/*int main() {
    insert("Nemo","2009","gjf","54");
    insert("Cars","2010","ds","45");
    insert("Big","2020","aa","64");
    insert("Whiplash","2035","sss","32");
    insert("IronMan","2010","ddd","23");
    cout<<"The linked list is: ";
    display();
    search("Whiplash");
    return 0;
}*/

#endif //SOCKETSERVER_LINKEDLIST_H
