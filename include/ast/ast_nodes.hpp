#ifndef ast_nodes_hpp
#define ast_nodes_hpp

#include <string>
#include <iostream>
#include <map>
#include <unordered_map>
#include <memory>
#include <regex>
#include <cassert>

class Node;

typedef Node *NodePtr;
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
    NodePtr m_parent = 0;
    static std::unordered_map<std::string,NodePtr>& getGlobals()  { static std::unordered_map<std::string,NodePtr> globals; return globals; }
public:
    virtual ~Node()
    {}

    void setParent(NodePtr parent) {
        assert(!m_parent);
        m_parent = parent;
    }

    //! Tell node to translate itself to the given stream
    virtual void translate(int level, std::ostream &dst) const =0;

    //! Generate the mips code to the given stream
    virtual void code_gen(std::ostream &dst) const
    { throw std::runtime_error("Not implemented."); }

    virtual NodePtr get_binding(std::string key) const
    {
        if (m_parent = 0) {//we've reached the top of the program
            std::unordered_map<std::string,NodePtr>::iterator it = getGlobals().find(key);
             if (it == bindings.end())
                std::cout<<"use of undeclared identifier '"<<key<<"'";
            else
                return it->second;
        }
        else mparent->get_binding();
    }

    virtual void create_binding(std::string key, NodePtr node)
    { mparent->get_binding(); }
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
