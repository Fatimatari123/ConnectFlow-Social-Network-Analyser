#pragma once
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) {
            data = val;
            next = NULL;
        }
    };

    Node* frontNode;
    Node* rearNode;
    int total;

public:
    Queue() {
        frontNode = NULL;
        rearNode = NULL;
        total = 0;
    }

    void enqueue(T val) {
        Node* newNode = new Node(val);
        if (frontNode == NULL) {
            frontNode = newNode;
            rearNode = newNode;
        }
        else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        total++;
    }

    T dequeue() {
        if (frontNode == NULL) {
            return T();
        }
        Node* temp = frontNode;
        T val = frontNode->data;
        frontNode = frontNode->next;
        delete temp;
        total--;
        return val;
    }

    bool isEmpty() {
        return frontNode == NULL;
    }

    int size() {
        return total;
    }
};

#endif
