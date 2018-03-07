#ifndef ast_nodes_hpp
#define ast_nodes_hpp

#include <string>
#include <iostream>
#include <map>
#include <unordered_map>

#include <memory>
#include <regex>

class Node;

typedef const Node *NodePtr;
static const std::regex reNum("^-?[0-9]+$");
static const std::regex reId("^[a-z][a-z0-9]*$");

static int NameUnq=0;

static std::string makeName(std::string base)
{
    return "_"+base+"_"+std::to_string(NameUnq++);
}

class Node
{
protected:
    static std::unordered_map<std::string,NodePtr>& getStack()  { static std::unordered_map<std::string,NodePtr> stack; return stack; }
    static std::unordered_map<std::string,NodePtr>& getGlobals()  { static std::unordered_map<std::string,NodePtr> globals; return globals; }
public:
    virtual ~Node()
    {}

    //! Tell node to translate itself to the given stream
    virtual void translate(int level, std::ostream &dst) const =0;

    //! Generate the mips code to the given stream
    virtual void code_gen(std::ostream &dst) const
    { throw std::runtime_error("Not implemented."); }
};

class Statement2 : public Node
{
public:
    //! Tell node to translate itself to the given stream
    virtual void translate(int level, std::ostream &dst) const =0;

    //! Generate the mips code to the given stream
    virtual void code_gen(std::ostream &dst) const override
    { throw std::runtime_error("Statement Not implemented."); }
};

class Expression : public Node
{
public:
    //! Tell node to translate itself to the given stream
    virtual void translate(int level, std::ostream &dst) const =0;

    //! Generate the mips code to the given stream
    virtual void code_gen(std::ostream &dst) const override
    { throw std::runtime_error("Expressions Not implemented."); }
};


#endif
