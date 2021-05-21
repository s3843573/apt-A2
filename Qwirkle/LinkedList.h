
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <exception>
#include <iostream>

#include <stdexcept>

class LinkedList
{
public:
   // constructors and destructors
   LinkedList();
   ~LinkedList();

   int size();

   // get node at index i
   std::shared_ptr<Tile> get(int i);

   // get node with tile infomation
   std::shared_ptr<Tile> get(Colour c, Shape s, int &position);

   // add node to head
   void addFront(std::shared_ptr<Tile> data);

   // add node to back
   void addBack(std::shared_ptr<Tile> data);

   // add node at index
   void addAt(int i, std::shared_ptr<Tile> data);

   // delete node at index
   void deleteAt(int i);

   // remove front
   void deleteFront();

   // remove back
   void deleteBack();

   friend std::ostream &operator<<(std::ostream &os, LinkedList &other);

private:
   std::shared_ptr<Node> head;

   int length;
};

#endif // ASSIGN2_LINKEDLIST_H
