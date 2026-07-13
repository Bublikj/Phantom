#include <vector>
#include <string>

class GLSLParser{
public:
    static void Parse(const std::string& path,std::string &SourceFShader,std::string &SourceVShader);
};