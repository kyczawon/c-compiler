#ifndef ast_node_hpp
#define ast_node_hpp

#include <string>
#include <iostream>
#include <map>
#include <unordered_map>

#include <memory>

class Node;

typedef const Node *NodePtr;

class Node
{
protected:
    static std::unordered_map<std::string,NodePtr>& getStack()  { static std::unordered_map<std::string,NodePtr> stack; return stack; }
    static std::unordered_map<std::string,NodePtr>& getGlobals()  { static std::unordered_map<std::string,NodePtr> globals; return globals; }
public:
    virtual ~Node()
    {}

    //! Tell and node to translate itself to the given stream
    virtual void translate(int level, std::ostream &dst) const =0;

    //! Evaluate the tree using the given mapping of variables to numbers
    virtual double code_gen(
        const std::map<std::string,double> &bindings
    ) const
    { throw std::runtime_error("Not implemented."); }
};

#endif
