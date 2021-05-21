
#include "Node.h"

Node::Node(std::shared_ptr<Tile> tile, std::shared_ptr<Node> next)
{
   // TODO
   this->tile = tile;
   this->next = next;
}

Node::~Node()
{
}
