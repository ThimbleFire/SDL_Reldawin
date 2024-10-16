#ifndef _BASE_H_
#define _BASE_H_

#include <string>

class Base {
    public:
        virtual std::string ToString() const = 0;
    
    public:
        std::string Name;
};

#endif