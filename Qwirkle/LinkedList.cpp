
#include "LinkedList.h"

LinkedList::LinkedList()
{
   head = nullptr;
   length = 0;
}

LinkedList::~LinkedList()
{
   head = nullptr;
}

int LinkedList::size()
{
   return length;
}

std::shared_ptr<Tile> LinkedList::get(int i)
{
   if (i < 0 || i >= length)
   {
      throw std::out_of_range("Index i out of bound");
   }

   int count = 0;
   std::shared_ptr<Node> current = head;
   std::shared_ptr<Tile> value = current->tile;

   // get tile at index i
   while (count < i)
   {
      current = current->next;
      ++count;
      value = current->tile;
   }
   return value;
}

void LinkedList::addFront(std::shared_ptr<Tile> tile)
{
   addAt(0, tile);
}

void LinkedList::addBack(std::shared_ptr<Tile> tile)
{
   addAt(length, tile);
}

void LinkedList::deleteFront()
{
   deleteAt(0);
}

void LinkedList::deleteBack()
{
   deleteAt(length - 1);
}

void LinkedList::addAt(int i, std::shared_ptr<Tile> data)
{
   int index = 0;
   std::shared_ptr<Node> current = head;
   std::shared_ptr<Node> previous = nullptr;

   // finding index i node in the linked list
   while (index < i)
   {
      previous = current;
      current = current->next;
      ++index;
   }

   std::shared_ptr<Node> newNode = std::make_shared<Node>(data, current);
   if (previous != nullptr)
   {
      // add the new node
      previous->next = newNode;
   }
   else
   {
      head = newNode;
   }
   length++;
}

void LinkedList::deleteAt(int i)
{

   int index = 0;
   std::shared_ptr<Node> current = head;
   std::shared_ptr<Node> previous = nullptr;

   // finding the index i node in the linked list
   while (index < i)
   {
      previous = current;
      current = current->next;
      ++index;
   }

   // head condition
   if (previous != nullptr)
      previous->next = current->next;
   else
   {
      head = head->next;
   }
   length--;
}

std::shared_ptr<Tile> LinkedList::get(Colour c, Shape s, int &position)
{
   std::shared_ptr<Node> current = head;
   bool found = false;
   std::shared_ptr<Tile> t = nullptr;
   int i = 0;

   // looping through the link list
   while (current != nullptr && !found)
   {
      std::shared_ptr<Tile> tile = current->tile;
      bool isTile = tile->colour == c && tile->shape == s;
      if (isTile)
      {
         t = current->tile;
         found = true;
      }
      else
      {
         // next node
         current = current->next;
         i++;
      }
   }
   position = i;
   return t;
}

std::ostream &operator<<(std::ostream &out, LinkedList &list)
{
   int i = 0;
   int length = list.size();
   while (i != length)
   {
      // output format for the linekdlist
      std::shared_ptr<Tile> tile = list.get(i);
      if (i == length - 1)
      {
         out << tile->colour << tile->shape;
      }
      else
      {
         out << tile->colour << tile->shape << ",";
      }
      i++;
   }
   return out;
}