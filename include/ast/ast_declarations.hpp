#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_nodes.hpp"

#include <cmath>
#include <sstream>

class Parameter : public Node
{
private:
    std::string type, id;
public:
    Parameter(const std::string &_type, const std::string &_id)
        : type(_type),
        id(_id)
    {}

    const std::string getId() const
    { return id; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<id;
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        context.add_binding(type,id);
        if(context.get_current_register()<3){
            std::string reg = "a"+std::to_string(context.next_register());
            context.set_binding(id,reg,dst,0);
        } else {
            dst<<"\tlw\t$s0,"<<context.next_register()*4<<"($t1)\n";
            context.set_binding(id,"s0",dst,0);
        }
    }
};

class ParameterList : public Node
{
protected:
    NodePtr list, parameter;
public:
    ParameterList (NodePtr _list, NodePtr _parameter)
            : list(_list),
            parameter(_parameter)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        //parameter list could contain one parameter
       if (list != nullptr) {
            list->translate(0,dst);
            dst << ", ";
        }
        parameter->translate(0,dst);
    }

    unsigned int get_num() const
    {
        const ParameterList* params = dynamic_cast<const ParameterList *>(list);
        unsigned int num = 1;
        if (list != nullptr) {
            num += params->get_num();
        }
        return num;
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        const Parameter* param = dynamic_cast<const Parameter *>(parameter);
        // parameter list could contain one parameter
        if (list != nullptr) {
            list->code_gen(dst, context);
        }
        parameter->code_gen(dst, context);
        // paremter list cannot containg more than 4 parameters (assuming 4 bytes parameters)
        // if (context.get_binding(param->Parameter::getId()) > 12) {
        //     throw std::runtime_error("More than 4 parameters not supported");
        // }
    }
};

class Function : public Node
{
protected:
    NodePtr compound, parameter_list;
    std::string type, identifier;
public:
    Function(std::string &_type, std::string &_identifier, NodePtr _parameter_list, NodePtr _compound)
        : type(_type)
        , identifier(_identifier)
        , parameter_list(_parameter_list)
        , compound(_compound)
    {
    }
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<"def "<<identifier<<"(";
        if (parameter_list != nullptr) parameter_list->translate(0, dst);
        dst<<"):";
        compound->translate(level, dst);
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        if (parameter_list != nullptr) {
            const ParameterList* params = dynamic_cast<const ParameterList *>(parameter_list);
            context.add_function(identifier, params->get_num());
        } else {
            context.add_function(identifier, 0);
        }


        std::stringstream init;
        std::stringstream init2;

        if (context.is_first_text) {
            init2<<"\t.text\t"<<std::endl;
            context.is_first_text = false;
        }

        init2<<"\t.align\t2"<<std::endl;
        init2<<"\t.global\t"<<identifier<<std::endl;
        init2<<"\t.set\tnomips16"<<std::endl;
        init2<<"\t.set\tnomicromips"<<std::endl;
        init2<<"\t.ent\t"<<identifier<<std::endl;
        init2<<"\t.type\t"<<identifier<<", @function"<<std::endl;
        
        init2<<identifier<<":"<<std::endl; //.frame goes after the identifier
        init<<"\t.set\tnoreorder"<<std::endl;
        init<<"\t.set\tnomacro"<<std::endl;

        int param_num = 1;
        std::stringstream inner_compiled; 
        Context inner_context = new Context(context);
        if(parameter_list != NULL){
            parameter_list->code_gen(inner_compiled,inner_context);
            param_num = inner_context.next_register();
            inner_context.reset_registers(); //after the parameter list
        }
        if(param_num>4){
            param_num = param_num - 3;
        } else param_num = 1;
        FnTracker.push_back(identifier+"END");
        inner_context.set_mem(param_num*4+40);
        compound->code_gen(inner_compiled, inner_context);
        if (Node::getRData()) {
            dst<<"\t.rdata"<<std::endl;
            dst<<Node::getGlobalDec().str();
        }
        dst<<init2.str();
        dst<<"\t.frame\t$fp,"<<inner_context.size()<<",$31"<<std::endl;
        dst<<init.str();
        dst<<"\taddiu\t$t1,$sp,0\n";
        dst<<"\taddiu\t$sp,$sp,-"<<inner_context.size()<<std::endl;
        dst<<"\tsw\t$31, 0($sp)\n";
        dst<<"\tsw\t$30, 4($sp)\n";
        dst<<"\tsw\t$29, 8($sp)\n";
        dst<<"\tsw\t$28, 12($sp)\n";
        dst<<"\tsw\t$s7,"<< param_num*4+12 <<"($sp)\n";
        dst<<"\tsw\t$s6,"<< param_num*4+16 <<"($sp)\n";
        dst<<"\tsw\t$s5,"<< param_num*4+20 <<"($sp)\n";
        dst<<"\tsw\t$s4,"<< param_num*4+24 <<"($sp)\n";
        dst<<"\tsw\t$s3,"<< param_num*4+28 <<"($sp)\n";
        dst<<"\tsw\t$s2,"<< param_num*4+32 <<"($sp)\n";
        dst<<"\tsw\t$s1,"<< param_num*4+36 <<"($sp)\n";
        dst<<"\tsw\t$s0,"<< param_num*4+40 <<"($sp)\n";
        dst<<"\tmove\t$fp,$sp"<<std::endl;
        dst<<inner_compiled.str();
        // dst << "\taddiu	$sp,$sp," << inner_context.size()<<std::endl;
        dst<<FnTracker[0]<<":\n";

        switch(context.get_size(type)) {//return value must be sign extended to the correct num of bits
            case 1:
                dst<<"\tsll\t$v0,$v0,24"<<std::endl;
                dst<<"\tsra\t$v0,$v0,24"<<std::endl;
                break;
            case 2:
                dst<<"\tsll\t$v0,$v0,16"<<std::endl;
                dst<<"\tsra\t$v0,$v0,16"<<std::endl;
                break;
            case 12:
                dst<<"\tsll\t$v1,$v1,16"<<std::endl;    
                dst<<"\tsra\t$v1,$v1,16"<<std::endl;
                break;
        }

        dst<<"\tlw\t$31, 0($sp)\n";
        dst<<"\tlw\t$30, 4($sp)\n";
        dst<<"\tlw\t$29, 8($sp)\n";
        dst<<"\tlw\t$28, 12($sp)\n";
        dst<<"\tlw\t$s7,"<< param_num*4+12 <<"($sp)\n";
        dst<<"\tlw\t$s6,"<< param_num*4+16 <<"($sp)\n";
        dst<<"\tlw\t$s5,"<< param_num*4+20 <<"($sp)\n";
        dst<<"\tlw\t$s4,"<< param_num*4+24 <<"($sp)\n";
        dst<<"\tlw\t$s3,"<< param_num*4+28 <<"($sp)\n";
        dst<<"\tlw\t$s2,"<< param_num*4+32 <<"($sp)\n";
        dst<<"\tlw\t$s1,"<< param_num*4+36 <<"($sp)\n";
        dst<<"\tlw\t$s0,"<< param_num*4+40 <<"($sp)\n";
        dst<<"\tj\t$31"<<std::endl;
        dst <<"\taddiu\t$sp,$sp,"<<inner_context.size()<<std::endl;
        dst<<"\n\t.set\tmacro"<<std::endl;
        dst<<"\t.set\treorder"<<std::endl;
        dst<<"\t.end\t"<<identifier<<"\n\t";
        dst<<".size\t"<<identifier<<", .-"<<identifier<<std::endl;
        FnTracker.erase(FnTracker.begin());
    }
};

class FunctionDeclaration : public Node
{
protected:
    NodePtr compound, parameter_list;
    std::string type, identifier;
public:
    FunctionDeclaration(std::string &_type, std::string &_identifier, NodePtr _parameter_list)
        : type(_type)
        , identifier(_identifier)
        , parameter_list(_parameter_list)
    {
    }
    virtual void translate(int level, std::ostream &dst) const override
    {
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        if (parameter_list != nullptr) {
            const ParameterList* params = dynamic_cast<const ParameterList *>(parameter_list);
            context.add_function(identifier, params->get_num());
        } else {
            context.add_function(identifier, 0);
        }
        context.add_declaration(identifier);
    }
};

class List : public Node {
public:
    virtual void code_gen(std::ostream &dst, Context &context) const override //required by Node
    {
    }
    virtual void code_gen(std::ostream &dst, Context &context, const std::string &type) const =0;
};

class DeclarationList : public List
{
private:
    std::string id;
    NodePtr list, value;
public:
    DeclarationList(NodePtr _list, const std::string &_id, NodePtr _value)
        : list(_list),
        id(_id),
        value(_value)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        if (value != nullptr) {
            dst<<id<<"=";
            value->translate(0, dst);
        } else dst<<id<<"=0";
    }

    

    virtual void code_gen(std::ostream &dst, Context &context, const std::string &type) const override
    {
        context.add_binding(type, id);
        if (value != nullptr) {
            value->code_gen(dst, context);
            dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
            context.set_binding(id,"s0",dst,0);
        }
        if (list != nullptr) {
            const List* declarations = dynamic_cast<const List *>(list);
            declarations->code_gen(dst, context,type);
        }
    }
};

class PointerDeclarationList : public List
{
private:
    std::string id;
    NodePtr list, value;
public:
    PointerDeclarationList(NodePtr _list, const std::string &_id, NodePtr _value)
        : list(_list),
        id(_id),
        value(_value)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("PointerDeclarationList::translate is not implemented.");
    }

    virtual void code_gen(std::ostream &dst, Context &context, const std::string &type) const override
    {
        context.add_binding(type, id);
        if (value != nullptr) {
            value->code_gen(dst, context);
            dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
            context.set_binding(id,"s0",dst,0);
        }
        if (list != nullptr) {
            const List* declarations = dynamic_cast<const List *>(list);
            declarations->code_gen(dst, context,type);
        }
    }
};

class VariableDeclaration : public Node
{
private:
    std::string type;
    NodePtr list;
public:
    VariableDeclaration(const std::string &_type, NodePtr _list)
        : type(_type),
        list(_list)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        list->translate(level,dst);
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        const List* declarations = dynamic_cast<const List *>(list);
        declarations->code_gen(dst, context,type);
    }
};

class InitParams : public Node
{
protected:
    NodePtr list, expr;
public:
    InitParams(NodePtr _list, NodePtr _expr)
            : list(_list),
            expr(_expr)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("InitParams::translate is not implemented.");
    }

    //undefined behaviour
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("InitParams::code_gen more input parameters to this function need to be supplied");
    }

    virtual void code_gen(std::ostream &dst, Context &context,const int& mem,const int& type_size, int& current) const
    {
        if (list != nullptr) {
            const InitParams* params = dynamic_cast<const InitParams *>(list);
            params->code_gen(dst, context, mem,type_size, current);
            current++;
        }
        expr->code_gen(dst,context);
        dst<<"\tlw\t$s0"<<","<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tsw\t$s0"<<","<<mem+type_size*current<<"($fp)"<<std::endl;
    }
};

class ArrayDeclarationList : public List
{
private:
    std::string id;
    int size;
    NodePtr list, init;
public:
    ArrayDeclarationList(NodePtr _list, const std::string &_id, int _size, NodePtr _init)
        : list(_list),
        id(_id),
        size(_size),
        init(_init)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("ArrayDeclarationList::translate is not implemented.");
    }

    virtual void code_gen(std::ostream &dst, Context &context, const std::string &type) const override
    {
        context.add_arr_binding(type,id,size);
        if (init != nullptr) {
            const InitParams* params = dynamic_cast<const InitParams *>(init);
            int num = 0;
            params->code_gen(dst,context, context.get_binding(id), context.get_size(type),num);
        }
        if (list != nullptr) {
            const List* declarations = dynamic_cast<const List *>(list);
            declarations->code_gen(dst, context,type);
        }
    }
};

//currently global variable can only be a number (but in c it can be an expression evaluated at compile time)
class GlobalDeclarationList : public List
{
private:
    std::string id;
    NodePtr list;
public:
    GlobalDeclarationList(NodePtr _list, const std::string &_id)
        : list(_list),
        id(_id)
    {
        getGlobals().push_back(id);
    }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<id<<"=0";
    }

    virtual void code_gen(std::ostream &dst, Context &context, const std::string &type) const override
    {
        dst<<"\t.comm\t"<<id<<","<<context.get_size(type)<<","<<context.get_size(type)<<"\n";
        if (list != nullptr) {
            const List* declarations = dynamic_cast<const List *>(list);
            declarations->code_gen(dst, context,type);
        }
    }
};

class GlobalDeclarationList2 : public List
{
private:
    std::string id;
    NodePtr list;
    int value;
public:
    GlobalDeclarationList2(NodePtr _list, const std::string &_id, const int _value)
        : list(_list),
        id(_id),
        value(_value)
    {
        getGlobals().push_back(id);
    }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<id<<"="<<value;
    }

    virtual void code_gen(std::ostream &dst, Context &context, const std::string &type) const override
    {
        dst<<"\t.globl\t"<<id<<std::endl;
        if (context.is_first_global) {
            dst<<"\t.data"<<std::endl;
            context.is_first_global = false;
        }
        dst<<"\t.align\t2"<<std::endl;
        dst<<"\t.type\t"<<id<<", @object"<<std::endl;
        dst<<"\t.size\t"<<id<<", "<<context.get_size(type)<<std::endl;
        dst<<id<<":"<<std::endl;
        dst<<"\t.word\t"<<(int)value<<std::endl;
        if (list != nullptr) {
            const List* declarations = dynamic_cast<const List *>(list);
            declarations->code_gen(dst, context,type);
        }
    }
};

class GlobalPointerDeclarationList : public List
{
private:
    std::string id;
    NodePtr list;
public:
    GlobalPointerDeclarationList(NodePtr _list, const std::string &_id)
        : list(_list),
        id(_id)
    {
        getGlobals().push_back(id);
    }

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("GlobalPointerDeclarationList::translate is not implemented.");
    }

    virtual void code_gen(std::ostream &dst, Context &context, const std::string &type) const override
    {
        dst<<"\t.comm\t"<<id<<","<<context.get_size(type)<<","<<context.get_size(type)<<"\n";
        if (list != nullptr) {
            const List* declarations = dynamic_cast<const List *>(list);
            declarations->code_gen(dst, context,type);
        }
    }
};

class GlobalPointerDeclarationList2 : public List
{
private:
    std::string id;
    NodePtr list;
    int value;
public:
    GlobalPointerDeclarationList2(NodePtr _list, const std::string &_id, const int _value)
        : list(_list),
        id(_id),
        value(_value)
    {
        getGlobals().push_back(id);
    }

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("GlobalPointerDeclarationList2::translate is not implemented.");
    }

    virtual void code_gen(std::ostream &dst, Context &context, const std::string &type) const override
    {
        dst<<"\t.globl\t"<<id<<std::endl;
        if (context.is_first_global_ptr) {
            dst<<"\t.section\t.data.rel,\"aw\",@progbits"<<std::endl;
            context.is_first_global_ptr = false;
        }
        dst<<"\t.align\t2"<<std::endl;
        dst<<"\t.type\t"<<id<<", @object"<<std::endl;
        dst<<"\t.size\t"<<id<<", "<<context.get_size(type)<<std::endl;
        dst<<id<<":"<<std::endl;
        dst<<"\t.word\t"<<(int)value<<std::endl;
        if (list != nullptr) {
            const List* declarations = dynamic_cast<const List *>(list);
            declarations->code_gen(dst, context,type);
        }
    }
};

class GlobalPointerDeclarationList3 : public List
{
private:
    std::string id,value;
    NodePtr list;
public:
    GlobalPointerDeclarationList3(NodePtr _list, const std::string &_id, const std::string& _value)
        : list(_list),
        id(_id),
        value(_value)
    {
        getGlobals().push_back(id);
    }

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("GlobalPointerDeclarationList3::translate is not implemented.");
    }

    virtual void code_gen(std::ostream &dst, Context &context, const std::string &type) const override
    {
        dst<<"\t.globl\t"<<id<<std::endl;
        if (context.is_first_global_ptr) {
            dst<<"\t.section\t.data.rel,\"aw\",@progbits"<<std::endl;
            context.is_first_global_ptr = false;
        }
        dst<<"\t.align\t2"<<std::endl;
        dst<<"\t.type\t"<<id<<", @object"<<std::endl;
        dst<<"\t.size\t"<<id<<", "<<context.get_size(type)<<std::endl;
        dst<<id<<":"<<std::endl;
        dst<<"\t.word\t"<<value<<std::endl;
        if (list != nullptr) {
            const List* declarations = dynamic_cast<const List *>(list);
            declarations->code_gen(dst, context,type);
        }
    }
};

class GlobalInitParams : public Node
{
protected:
    NodePtr list;
    int value;
public:
    GlobalInitParams(NodePtr _list, int _value)
            : list(_list),
            value(_value)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("GlobalInitParams::translate is not implemented.");
    }

    //undefined behaviour
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        if (list != nullptr) {
            const GlobalInitParams* params = dynamic_cast<const GlobalInitParams *>(list);
            params->code_gen(dst, context);
        }
        dst<<"\t.word\t"<<value<<std::endl;
    }
};

class GlobalArrayDeclarationList : public List
{
private:
    std::string id;
    int size;
    NodePtr list;
public:
    GlobalArrayDeclarationList(NodePtr _list, const std::string &_id, const int _size)
        : list(_list),
        id (_id),
        size(_size)
    {
        getGlobalsArray().push_back(id);
    }

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("GlobalArrayDeclarationList::translate is not implemented.");
    }

    virtual void code_gen(std::ostream &dst, Context &context, const std::string &type) const override
    {
        context.add_arr_type(type, id, size);
        int tot = size*context.get_size(type);
        dst<<"\t.comm\t"<<id<<","<<tot<<","<<context.get_size(type)<<"\n";
        if (list != nullptr) {
            const List* declarations = dynamic_cast<const List *>(list);
            declarations->code_gen(dst, context,type);
        }
    }
};

class GlobalArrayDeclarationList2 : public List
{
private:
    std::string id;
    NodePtr list, init;
    int size;
public:
    GlobalArrayDeclarationList2(NodePtr _list, const std::string &_id, int _size, NodePtr _init)
        : list(_list),
        id(_id),
        size(_size),
        init(_init)
    {
        getGlobalsArray().push_back(id);
    }

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("GlobalArrayDeclarationList2::translate is not implemented.");
    }

    virtual void code_gen(std::ostream &dst, Context &context, const std::string &type) const override
    {
        context.add_arr_type(type, id, size);
        dst<<"\t.globl\t"<<id<<std::endl;
        if (context.is_first_global) {
            dst<<"\t.data"<<std::endl;
            context.is_first_global = false;
        }
        dst<<"\t.align\t2"<<std::endl;
        dst<<"\t.type\t"<<id<<", @object"<<std::endl;
        int tot = context.get_size(type)*size;
        dst<<"\t.size\t"<<id<<", "<<tot<<std::endl;
        dst<<id<<":"<<std::endl;
        init->code_gen(dst,context);
        if (list != nullptr) {
            const List* declarations = dynamic_cast<const List *>(list);
            declarations->code_gen(dst, context,type);
        }
    }
};

#endif
