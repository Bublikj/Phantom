#pragma once
#include <string>
namespace Phantom {

class GLSLParser{
public:
    static int Parse(const std::string& path,std::string &SourceFShader,std::string &SourceVShader);
};
}