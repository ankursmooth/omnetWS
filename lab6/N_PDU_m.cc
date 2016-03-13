//
// Generated file, do not edit! Created by nedtool 4.6 from N_PDU.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "N_PDU_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(N_PDU);

N_PDU::N_PDU(const char *name, int kind) : ::cPacket(name,kind)
{
    this->ID_var = 0;
    this->type_var = 0;
    this->sourceAdd_var = 0;
    this->destiAdd_var = 0;
}

N_PDU::N_PDU(const N_PDU& other) : ::cPacket(other)
{
    copy(other);
}

N_PDU::~N_PDU()
{
}

N_PDU& N_PDU::operator=(const N_PDU& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void N_PDU::copy(const N_PDU& other)
{
    this->ID_var = other.ID_var;
    this->type_var = other.type_var;
    this->sourceAdd_var = other.sourceAdd_var;
    this->destiAdd_var = other.destiAdd_var;
}

void N_PDU::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->ID_var);
    doPacking(b,this->type_var);
    doPacking(b,this->sourceAdd_var);
    doPacking(b,this->destiAdd_var);
}

void N_PDU::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->ID_var);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->sourceAdd_var);
    doUnpacking(b,this->destiAdd_var);
}

int N_PDU::getID() const
{
    return ID_var;
}

void N_PDU::setID(int ID)
{
    this->ID_var = ID;
}

const char * N_PDU::getType() const
{
    return type_var.c_str();
}

void N_PDU::setType(const char * type)
{
    this->type_var = type;
}

int N_PDU::getSourceAdd() const
{
    return sourceAdd_var;
}

void N_PDU::setSourceAdd(int sourceAdd)
{
    this->sourceAdd_var = sourceAdd;
}

int N_PDU::getDestiAdd() const
{
    return destiAdd_var;
}

void N_PDU::setDestiAdd(int destiAdd)
{
    this->destiAdd_var = destiAdd;
}

class N_PDUDescriptor : public cClassDescriptor
{
  public:
    N_PDUDescriptor();
    virtual ~N_PDUDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(N_PDUDescriptor);

N_PDUDescriptor::N_PDUDescriptor() : cClassDescriptor("N_PDU", "cPacket")
{
}

N_PDUDescriptor::~N_PDUDescriptor()
{
}

bool N_PDUDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<N_PDU *>(obj)!=NULL;
}

const char *N_PDUDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int N_PDUDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int N_PDUDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *N_PDUDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "ID",
        "type",
        "sourceAdd",
        "destiAdd",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int N_PDUDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='I' && strcmp(fieldName, "ID")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceAdd")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "destiAdd")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *N_PDUDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "string",
        "int",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *N_PDUDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int N_PDUDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    N_PDU *pp = (N_PDU *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string N_PDUDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    N_PDU *pp = (N_PDU *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getID());
        case 1: return oppstring2string(pp->getType());
        case 2: return long2string(pp->getSourceAdd());
        case 3: return long2string(pp->getDestiAdd());
        default: return "";
    }
}

bool N_PDUDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    N_PDU *pp = (N_PDU *)object; (void)pp;
    switch (field) {
        case 0: pp->setID(string2long(value)); return true;
        case 1: pp->setType((value)); return true;
        case 2: pp->setSourceAdd(string2long(value)); return true;
        case 3: pp->setDestiAdd(string2long(value)); return true;
        default: return false;
    }
}

const char *N_PDUDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *N_PDUDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    N_PDU *pp = (N_PDU *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


