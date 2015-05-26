/* Files: quadtree.h, quadtree.cpp, node.h
 * Author: Max Slocum, Joshua Cavaluzzi
 * Contributors:
 * Description: Templated Quad Tree with basic insert, delete, search range,
 *  display functionality. Can specify bucket size and grid size with
 *  constructor arguments. Default range is the lowest to highest values
 *  contained by double values.
*/

#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <iostream>
#include <utility>
#include <algorithm>
#include <cmath>
#include <limits>
#include "node.h"

typedef std::pair<double,double> cord;

template <class T>
class quadtree
{
public:
    /* Destructor */
    ~quadtree();

    /* Constructor - Default values assigned for bucket size and grid range */
    quadtree( unsigned int bukkitSize = 1,
              double xstart = std::numeric_limits<double>::lowest(),
              double xend = std::numeric_limits<double>::max(),
              double ystart = std::numeric_limits<double>::max(),
              double yend = std::numeric_limits<double>::lowest() ):

        xrange( xstart,xend ), yrange( ystart,yend ),
        bucketSize( bukkitSize ), root( nullptr ) { }

    /* destroy - Delete each node recursively */
    void destroy( node<T>* nd );

    /* inOrder - Output each object in order */
    void inOrder( );

    /* insert - Insert an item into the tree at a given location */
    void insert( cord location, T item );

    /* deleteKey - Remove an object at a certain location */
    bool deleteKey( cord xy );

    /* collision - Check for a collision between objects */
    bool collision( node<T> *nd, cord location );

    /* split - split a node into four quadrents */
    void split( node<T> *nd );

    /* getRoot - Return the root node */
    node<T>* getRoot( ) { return root; }

    /* overlapRect - Determine if two rectangles overlap one another */
    bool overlapRect( cord p1, cord p2, cord p3, cord p4 );

    /* searchRange - Return all objects within the range */
    std::vector<std::pair<cord,T> > searchRange( cord start, cord end );

    /* Overload the output operator to call inOrder */
    template <class U>
    friend std::ostream& operator<<( std::ostream &out,quadtree<U> &hp);

private:
    /* getSubQuad - get the next lowest quadrent where an object is located */
    node<T>* getSubQuad( node<T> *nd, cord location);

    /* createNode - create a new node with given fields */
    node<T>* createNode( double xfirst, double xsecond,
                         double yfirst, double ysecond );

    /* inOrder - Output each node from the current node and lower */
    void inOrder( node<T> *nd );

    /* searchRange - Recursively search each quadrent which overlaps the given
     *range for objects within the range */
    std::vector<std::pair<cord,T> > searchRange( 
        node<T> *nd, cord start, cord end );

    cord xrange;
    cord yrange;
    unsigned int bucketSize;
    node<T> *root;
};

#include "quadtree.cpp"

#endif
