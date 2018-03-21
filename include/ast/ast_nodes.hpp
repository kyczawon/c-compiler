#ifndef ast_nodes_hpp
#define ast_nodes_hpp

#include <string>
#include <iostream>
#include <map>
#include <unordered_map>

#include <memory>
#include <regex>

class Node;
class Context;

typedef const Node *NodePtr;
static const std::regex reNum("^-?[0-9]+$");
static const std::regex reId("^[a-z][a-z0-9]*$");

static int NameUnq=0;

static std::string make_name(std::string base)
{
    return "$"+base+std::to_string(NameUnq++);
}

class Node
{
protected:
    static std::unordered_map<std::string,NodePtr>& getGlobals()  { static std::unordered_map<std::string,NodePtr> globals; return globals; }
public:
    virtual ~Node()
    {}

    //! Tell node to translate itself to the given stream
    virtual void translate(int level, std::ostream &dst) const =0;

    //! Generate the mips code to the given stream
    virtual void code_gen(std::ostream &dst, Context &context) const
    { throw std::runtime_error("Not implemented."); }
};

class Statement2 : public Node
{
public:
    //! Tell node to translate itself to the given stream
    virtual void translate(int level, std::ostream &dst) const =0;

    //! Generate the mips code to the given stream
    virtual void code_gen(std::ostream &dst, Context &context) const override
    { throw std::runtime_error("Statement Not implemented."); }
};

class Expression : public Node
{
public:
    //! Tell node to translate itself to the given stream
    virtual void translate(int level, std::ostream &dst) const =0;

    //! Generate the mips code to the given stream
    virtual void code_gen(std::ostream &dst, Context &context) const override
    { throw std::runtime_error("Expressions Not implemented."); }
};

class Context {
private:
    int _size = 0;
    int current_register = -1;
    std::unordered_map<std::string,int> bindings;
    Context* parent;
public:
    Context(Context* _parent)
        : parent(_parent)
    {}
    
    int get_binding(std::string key) {
        std::unordered_map<std::string,int>::iterator it = bindings.find(key);
        
        if (it == bindings.end())
            return parent->get_binding(key);
        else
            return it->second;
    }

    void add_binding(std::string key, int bytes) {
        std::unordered_map<std::string,int>::iterator it = bindings.find(key);
            
        if (it == bindings.end()) {
            bindings[key] = _size;
            _size += bytes;
        }
        else
            std::cout<<"redefinition of '"<<key<<"'";
    }

    int size() {
        return _size;
    }

    int next_register() {
        current_register++;
        return current_register;
    }

    int get_current_register() {
        return current_register;
    }

    void reset_registers() {
        current_register = -1;
    }
};

#endif
