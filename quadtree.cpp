#include "quadtree.h"

template<class T>
quadtree<T>::~quadtree()
{
	if(root != nullptr) destroy(root);
}

/*
 * Name: getSubQuad
 * Description: Get the next lowest quadrent which a point is located.
 * Arguments: current node, x/y location
 * Modifies: none
 * Returns: node<T>*
 */
template <class T>
node<T>* quadtree<T>::getSubQuad( node<T> *nd, cord location )
{
  if(location.first <= ((nd->x.first + nd->x.second)/2.0))
  {
    if(location.second > ((nd->y.first + nd->y.second)/2.0))
      nd = nd->first;
    else
      nd = nd->third;
  }
  else
  {
    if(location.second > ((nd->y.first + nd->y.second)/2.0))
      nd = nd->second;
    else
      nd = nd->fourth;
  }
  return nd;
}

/*
 * Name: createNode
 * Description: Create a node with a specified x, y range.
 * Arguments: x first, x second, y first, y second
 * Modifies: none
 * Returns: node<T>*
 */
template <class T>
node<T>* quadtree<T>::createNode(double xfirst, double xsecond, 
                                 double yfirst, double ysecond)
{
  node<T> *nn = new node<T>();

  nn->x.first = xfirst;
  nn->x.second = xsecond;
  nn->y.first = yfirst;
  nn->y.second = ysecond;

  return nn;
}

/*
 * Name: insert
 * Description: Add a given item at a specific location into the tree
 *              while splitting if the number of objects in a node
 *              exeeds the bucket size.
 * Arguments: location (standard pair x,y), item 
 * Modifies: root and the following nodes
 * Returns: void
 */
template <class T>
void quadtree<T>::insert( cord location, T item )
{
  std::pair<cord,T> data;
  node<T> *tmp = root;

  data.first = location;
  data.second = item; 

	if(root == nullptr)
	{
    node<T> *nn = createNode(xrange.first, xrange.second, 
                             yrange.first, yrange.second);
    nn->objects.push_back(data);
    root = nn;
	}
	else
	{
    while(1)
    {
      if(tmp->first == nullptr)
      {
        if(bucketSize == tmp->objects.size())
        {
          if(collision(tmp,location))
            return;
          split(tmp);
        } else {
          tmp->objects.push_back(data);
          return;
        }
      } else {
        tmp = getSubQuad(tmp,location);
      }    
    }
    }
}

/*
 * Name: split
 * Description: transforms a quad tree node into four quadrents
 * Arguments: node pointer (nd)
 * Modifies: node pointer (nd)
 * Returns: void
 */
template <class T>
void quadtree<T>::split(node<T> *nd)
{
  double xmid = (nd->x.second + nd->x.first) / 2.0;
  double ymid = (nd->y.second + nd->y.first) / 2.0;

  nd->first = createNode(nd->x.first,xmid,nd->y.first,ymid);
  nd->second = createNode(xmid,nd->x.second,nd->y.first,ymid);
  nd->third = createNode(nd->x.first,xmid,ymid,nd->y.second);
  nd->fourth = createNode(xmid,nd->x.second,ymid,nd->y.second);

  for(auto i:nd->objects)
  {
    insert(i.first,i.second);
  }

  nd->objects.clear();
}

/*
 * Name: destroy
 * Description: Recursively delete all sub nodes including the given node.
 * Arguments: node<T>*
 * Modifies: nd and all sub nodes
 * Returns: void
 */
template<class T>
void quadtree<T>::destroy(node<T> *nd)
{
	if(nd != nullptr)
	{
		destroy(nd->first);
		destroy(nd->second);
		destroy(nd->third);
		destroy(nd->fourth);
		delete nd;
	}
}

/*
 * Name: inOrder
 * Description: Call the recursive inOrder function.
 * Arguments: none
 * Modifies: none
 * Returns: void
 */
template <class T>
void quadtree<T>::inOrder()
{
  inOrder(root);
}

/*
 * Name: inOrder
 * Description: Outputs each object and then all sub quadrents 
 *              objects recursively.
 * Arguments: node<T>*
 * Modifies: none
 * Returns: void
 */
template <class T>
void quadtree<T>::inOrder(node<T> *nd)
{
  if(nd == nullptr) return;

  for(auto i:nd->objects)
  {
    std::cout << "X:" << i.first.first << " Y:" << i.first.second 
      << " -(object)- " << i.second << std::endl;
  }

  inOrder(nd->first);
  inOrder(nd->second);
  inOrder(nd->third);
  inOrder(nd->fourth);
}

/*
 * Name: deleteKey
 * Description: Deletes an object at a given location. if the object is 
 *              successfuly deleted, true is returned, otherwise false 
 *              is returned.
 * Arguments: x/y coordinates to remove objects from.
 * Modifies: object at xy
 * Returns: bool
 */
template <class T>
bool quadtree<T>::deleteKey( cord xy )
{
  if(root == nullptr) return false;
  node<T> *tmp = root;
	
	while(1)
	{
	  if(tmp->first != nullptr)
	  {
      tmp = getSubQuad(tmp,xy);
  	} else {
  	  for(int i=0;i<tmp->objects.size();i++)
  	  {
  	    if(tmp->objects[i].first == xy) 
  	    {
	        tmp->objects.erase(tmp->objects.begin() + 1);
	        return true;
	      }
	    }
	  }
	}
  return false;
}

/*
 * Name: searchRange
 * Description: Call the recursive searchRange function.
 * Arguments: start point, end point
 * Modifies: none
 * Returns: vector of pairs of objects and their x/y location
 */
template <class T>
std::vector<std::pair<cord,T> > quadtree<T>::searchRange( cord start, cord end )
{
  return searchRange(root,start,end);
}

/*
 * Name: searchRange
 * Description: Recursively search all quadrents within the search range 
 *              and return all objects found within range.
 * Arguments: node, start point, end point
 * Modifies: none
 * Returns: vector of pairs of objects and their x/y location
 */
template <class T>
std::vector<std::pair<cord,T> > quadtree<T>::searchRange( 
    node<T> *nd, cord start,cord end )
{
  std::vector<std::pair<cord, T> > results;
  std::vector<std::pair<cord, T> > quad;
 
  if(nd == nullptr) return results;

  if(nd->first != nullptr)
  {
     cord q1start(nd->first->x.first,nd->first->y.first);
     cord q1end(nd->first->x.second,nd->first->y.second);

     cord q2start(nd->second->x.first,nd->second->y.first);
     cord q2end(nd->second->x.second,nd->second->y.second);

     cord q3start(nd->third->x.first,nd->third->y.first);
     cord q3end(nd->third->x.second,nd->third->y.second);

     cord q4start(nd->fourth->x.first,nd->fourth->y.first);
     cord q4end(nd->fourth->x.second,nd->fourth->y.second);

     if(overlapRect(q1start,q1end,start,end))
      {
        quad = searchRange(nd->first,start,end);
        results.insert(results.end(),quad.begin(),quad.end());
      }

      if(overlapRect(q2start,q2end,start,end))
      {
        quad = searchRange(nd->second,start,end);
        results.insert(results.end(),quad.begin(),quad.end());
      }

      if(overlapRect(q3start,q3end,start,end))
      {
        quad = searchRange(nd->third,start,end);
        results.insert(results.end(),quad.begin(),quad.end());
      }

      if(overlapRect(q4start,q4end,start,end))
      {
        quad = searchRange(nd->fourth,start,end);
        results.insert(results.end(),quad.begin(),quad.end());
      }
    } else {
      for(auto i:nd->objects)
      {
        if(i.first.first < end.first && i.first.first > start.first 
           && i.first.second > end.second && i.first.second < start.second)
          results.push_back(i);
      }
  }

  return results;
}

/*
 * Name: collision
 * Description: Detect a collision between two points.
 * Arguments: node, location
 * Modifies: none
 * Returns: bool
 */
template <class T>
bool quadtree<T>::collision(node<T> *nd,cord location)
{
  for(int i=0;i<nd->objects.size();i++)
  {
    if(nd->objects[i].first.first == location.first 
        && nd->objects[i].first.second == location.second) 
      return true;
  }
  return false;
}

/* 
 * Name: overlapRect
 * Description: Determine if two rectangles overlap
 * Arguments: upper left and lower right point for each square.
 * Modifies: none
 * Returns: bool
 */
template <class T>
bool quadtree<T>::overlapRect( cord p1, cord p2, cord p3, cord p4)
{
  if(p1.first > p4.first || p3.first > p2.first) return false;
  if(p1.second < p4.second || p3.second < p2.second) return false;
  return true;
}

template <class U>
std::ostream& operator<<(std::ostream &out,quadtree<U> &qt)
{
  qt.inOrder();
  return out;
}


