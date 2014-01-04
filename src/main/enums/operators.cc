#include <node.h>
#include "enums.h"

using namespace v8;

#define set(__obj, __name, __value) __obj->Set(String::NewSymbol(__name), Integer::New(__value), ReadOnly)

Handle<Object> operators() 
{
    HandleScope scope;
    Handle<Object> obj = Object::New();
    set(obj, "WRITE",   0);
    set(obj, "READ",    1);
    set(obj, "INCR",    2);
    set(obj, "PREPEND", 4);
    set(obj, "APPEND",  5);
    set(obj, "TOUCH",   8);
    return scope.Close(obj);
}
