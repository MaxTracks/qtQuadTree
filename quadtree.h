#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <iostream>
#include <utility>
#include <algorithm>
#include <cmath>
#include <limits>
#include "node.h"

template <class T>
class quadtree
{
 public:
  node<T>* getRoot(){return root;}
  quadtree(unsigned int bukkitSize = 1,double xstart = std::numeric_limits<double>::lowest(), 
    double xend = std::numeric_limits<double>::max(), 
    double ystart = std::numeric_limits<double>::max(), 
    double yend = std::numeric_limits<double>::lowest()):xrange(xstart,xend),
    yrange(ystart,yend),bucketSize(bukkitSize),root(nullptr){}
  ~quadtree();
  void destroy(node<T>* nd);
  void inOrder();
  void insert(std::pair<double,double> location,T item);
  bool overlapRect(std::pair<double,double> p1,
               std::pair<double,double> p2, 
               std::pair<double,double> p3, 
               std::pair<double,double> p4);
  bool deleteKey(std::pair<double,double> xy);
  std::vector<std::pair<std::pair<double,double>,T> > searchRange(std::pair<double,double> start,
      std::pair<double,double> end);
  template <class U>
  friend std::ostream& operator<<(std::ostream &out,quadtree<U> &hp);
  
 private:
  std::vector<std::pair<std::pair<double,double>,T> > searchRange(node<T> *nd,
      std::pair<double,double> start,std::pair<double,double> end);
  bool collision(node<T> *nd,std::pair<double,double> location);
  void split(node<T> *nd);
  void inOrder(node<T> *nd);
  void insert(node<T> *tmp, std::pair<double,double> location, T item);

  std::pair<double,double> xrange;
  std::pair<double,double> yrange;
  unsigned int bucketSize;
  node<T> *root;
};

#include "quadtree.cpp"

#endif
