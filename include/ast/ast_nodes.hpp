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

class Expression : public Node
{
public:

    //! Generate the mips code to the given stream
    virtual void code_gen(std::ostream &dst, Context &context) const override
    { throw std::runtime_error("Expressions Not implemented."); }
};

class Context {
private:
    int _size = 0;
    int current_register = -1;
    std::unordered_map<std::string,int> bindings;
    std::unordered_map<std::string,std::string> types;
    Context* parent;
public:
    Context(Context* _parent)
        : parent(_parent)
    {}

    int get_binding(std::string key) {
        std::unordered_map<std::string,int>::iterator it = bindings.find(key);
        
        if (it == bindings.end()) {
            if (parent != nullptr) return parent->get_binding(key);
            else throw std::runtime_error("error: '" + key + "' undeclared");
        }
        else
            return it->second;
    }

    std::string get_type(std::string key) {
        std::unordered_map<std::string,std::string>::iterator it = types.find(key);
        
        if (it == types.end())
            if (parent != nullptr) return parent->get_type(key);
            else throw std::runtime_error("error: '" + key + "' undeclared");
        else
            return it->second;
    }

    int get_size (std::string const& type) const {
        if (type == "int") return 4;
        else throw std::runtime_error("type: " + type + "not implemented");
    }

    void add_binding(std::string type, std::string key) {

        int bytes = get_size(type);

        std::unordered_map<std::string,int>::iterator it = bindings.find(key);
            
        if (it == bindings.end()) {
            bindings[key] = _size;
            _size += bytes;

            types[key] = type;
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

    int reset_last_register(){
        current_register--;
        return current_register;
    }

    void reset_registers() {
        current_register = -1;
    }
};

#endif
