//
//  Queue.hpp
//  Miles_Weapon_Decoder
//
//  Created by Jacob Byerline on 10/13/19.
//  Copyright © 2019 Jacob Byerline. All rights reserved.
//  cssc0927

class Node{
public:
    int value;
    Node* next;
};

class Queue{
    Node* tail;
    Node* head;
public:
    void loadValue(int); // enqueue
    int nextValue(); // dequeue 
    bool isEmpty();
    void normalize();
    int* peek(int);
    int size();
};
