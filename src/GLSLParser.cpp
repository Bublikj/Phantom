#include"../include/GLSLParser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
int Phantom::GLSLParser::Parse(const std::string &path,
                               std::string &SourceFShader,
                               std::string &SourceVShader) {

  std::ifstream stream(path);

  if (!stream.is_open()) {
    std::cerr << "Error: Could not open the file!" << std::endl;
    return 1;
  }

  std::ostringstream FragmentStream;
  std::ostringstream VertexStream;
  bool IsDelimiter = false;
  std::string line;
  // 3. Read line by line until the end of the file
  while (std::getline(stream, line)) {
    if (line == "//SPLIT_SHADER") {
      IsDelimiter = true;
      break;
    } else {
      FragmentStream << line << "\n";
    }
  }

  while (std::getline(stream, line)) {
    VertexStream << line << "\n";
  }

  SourceFShader = FragmentStream.str();
  SourceVShader = VertexStream.str();
  if (!IsDelimiter) {
    std::cerr << "Not found //SPLIT_SHADER in file " << path << std::endl;
    return 1;
  }

  if (SourceFShader.empty() || SourceVShader.empty()) {
    std::cerr << "Shader is empty for source in file " << path << std::endl;
    return 1;
  }

  // 4. Close the file (optional, as the destructor does this automatically)
  stream.close();
  return 0;
}