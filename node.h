#ifndef NODE_H_
#define NODE_H_

template<class T>
class node
{
  public:
    node():first(nullptr),second(nullptr),third(nullptr),fourth(nullptr){}

    node* first;
    node* second;
    node* third;
    node* fourth;

    std::pair<double,double> x;
    std::pair<double,double> y;

    std::vector<std::pair<std::pair<double,double>,T> > objects;
};

#endif
