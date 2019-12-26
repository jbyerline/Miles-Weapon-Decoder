//
//  Queue.cpp
//  Miles_Weapon_Decoder
//
//  Created by Jacob Byerline on 10/13/19.
//  Copyright © 2019 Jacob Byerline. All rights reserved.
//  cssc0927
#include <iostream>
#include "Queue.hpp"
#define BUFFSIZE 100000

void Queue::loadValue(int newValue){
    Node * newNode = new Node();
    newNode->value = newValue;
    //If there are no Nodes in the queue
    if(head == nullptr && tail == nullptr){
        head = newNode;
        tail = newNode;
    }
    // .next adds newNode to the back of the line
    // then set tail to the back of the line
    else{
        newNode->next = tail;
        tail = newNode;
    }
}

int Queue::nextValue(){
    // If there is people in line
    if(!(head == nullptr && tail == nullptr)){
        // If there is one person in line
        if(head == tail){
            Node returnValue = *head;
            head = nullptr;
            tail = nullptr;
            return returnValue.value;
        }
        // If there is more than one person in line
        else{
            Node *value = tail;
            while(value->next != head){
                value = value->next;
            }
            Node returnValue = *head;
            head = value;
            value->next = nullptr;
            return returnValue.value;
        }
    }
    return -1;
}

bool Queue::isEmpty(){
    // Returns true or false if the queue is empty
    if(head == nullptr && tail == nullptr){
        return true;
    }
    else
        return false;
}

void Queue::normalize(){
    if (!isEmpty()) {
        Node *currentNode = tail;
        // Loop through queue
        while(currentNode != head){
            // Subtract the value at the head from each value in the queue
            currentNode->value -= head->value;
            currentNode = currentNode->next;
        }
        currentNode->value -= head->value;
    }
}

 int * Queue::peek(int num){
     static int arr[BUFFSIZE];
     // Set target equal to last node
     Node * target = head;
     // Check if queue is empty
     if(!(isEmpty())){
         // Search for input number of values in queue
         for (int i = 0; i < num; i++){
             //Start at end of line and work way to target
             Node * current = tail;
             //If target is end of line, add to array and return
             if (target == tail) {
                 *(arr + i) = target->value;
                 return arr;
             }
             //Moving towards target
             while(current->next != target){
                 current = current->next;
             }
             //Found target, add value to array and set target one node closer to tail, then restart search
             *(arr + i) = target->value;
             target = current;
         }
     }
     
     return arr;
 }

int Queue::size(){
    int count = 0;
    // If queue is not empty
    if (tail != nullptr){
        count = 1;
        // Set temp variable to tail so you dont overwrite tail
        Node *temp = tail;
        // While next value in queue is not null
        while(temp->next != nullptr){
            // temp is equal to next value
            temp = temp->next;
            // iterate count to count number of items in queue
            count++;
        }
    }
    return count;
}
