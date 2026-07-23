#include "../../include/Graphic/Shader.hpp"
#include "../../glad/glad.h"
#include "../../include/Core/GLSLParser.hpp"
#include <iostream>
Phantom::Graphic::Shader::Shader() {}

Phantom::Graphic::Shader::Shader(const std::string &path) { Setup(path); }

void Phantom::Graphic::Shader::Setup(const std::string &path) {
  std::string fragmentShaderSource = "";
  std::string vertexShaderSource = "";

  if (GLSLParser::Parse(path, fragmentShaderSource, vertexShaderSource) == 0) {

    unsigned int VertexShader =
        CompileShader(vertexShaderSource.c_str(), GL_VERTEX_SHADER);
    unsigned int FragmentShader =
        CompileShader(fragmentShaderSource.c_str(), GL_FRAGMENT_SHADER);
    unsigned int ShaderProgram = CreateProgram(FragmentShader, VertexShader);
    this->ProgramId = ShaderProgram;
  } else {
    return;
  }
}

void Phantom::Graphic::Shader::Clear() {
  UnUsing();
  glDeleteProgram(ProgramId);
}

void Phantom::Graphic::Shader::Using() { glUseProgram(ProgramId); }

void Phantom::Graphic::Shader::UnUsing() {
  glUseProgram(0);
}

void Phantom::Graphic::Shader::setInt(const std::string &name, int value) {
  glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void Phantom::Graphic::Shader::setVec2Int(const std::string &name, int x, int y) {
  glUniform2i(glGetUniformLocation(ProgramId, name.c_str()), x, y);
}

void Phantom::Graphic::Shader::setVec3Int(const std::string &name, int x, int y, int z) {
  glUniform3i(glGetUniformLocation(ProgramId, name.c_str()), x, y, z);
}

void Phantom::Graphic::Shader::setVec4Int(const std::string &name, int x, int y, int z,
                                 int w) {
  glUniform4i(glGetUniformLocation(ProgramId, name.c_str()), x, y, z, w);
}

void Phantom::Graphic::Shader::setFloat(const std::string &name, float value) {
  glUniform1f(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void Phantom::Graphic::Shader::setVec2Float(const std::string &name, float x, float y) {
  glUniform2f(glGetUniformLocation(ProgramId, name.c_str()), x, y);
}

void Phantom::Graphic::Shader::setVec3Float(const std::string &name, float x, float y,
                                   float z) {
  glUniform3f(glGetUniformLocation(ProgramId, name.c_str()), x, y, z);
}

void Phantom::Graphic::Shader::setVec4Float(const std::string &name, float x, float y,
                                   float z, float w) {
  glUniform4f(glGetUniformLocation(ProgramId, name.c_str()), x, y, z, w);
}

void Phantom::Graphic::Shader::setDouble(const std::string &name, double value) {
  glUniform1d(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void Phantom::Graphic::Shader::setVec2Double(const std::string &name, double x,
                                    double y) {
  glUniform2d(glGetUniformLocation(ProgramId, name.c_str()), x, y);
}

void Phantom::Graphic::Shader::setVec3Double(const std::string &name, double x, double y,
                                    double z) {
  glUniform3d(glGetUniformLocation(ProgramId, name.c_str()), x, y, z);
}

void Phantom::Graphic::Shader::setVec4Double(const std::string &name, double x, double y,
                                    double z, double w) {
  glUniform4d(glGetUniformLocation(ProgramId, name.c_str()), x, y, z, w);
}

void Phantom::Graphic::Shader::setBool(const std::string &name, bool value) {
  glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void Phantom::Graphic::Shader::setVec2Bool(const std::string &name, bool x, bool y) {
  glUniform2i(glGetUniformLocation(ProgramId, name.c_str()), x, y);
}

void Phantom::Graphic::Shader::setVec3Bool(const std::string &name, bool x, bool y,
                                  bool z) {
  glUniform3i(glGetUniformLocation(ProgramId, name.c_str()), x, y, z);
}

void Phantom::Graphic::Shader::setVec4Bool(const std::string &name, bool x, bool y,
                                  bool z, bool w) {
  glUniform4i(glGetUniformLocation(ProgramId, name.c_str()), x, y, z, w);
}

unsigned int Phantom::Graphic::Shader::getID() { return ProgramId; }

unsigned int Phantom::Graphic::Shader::CompileShader(const char *source,
                                            GLenum TypeShader) {
  unsigned int ShaderID = 0;
  int success;
  char log[512];
  ShaderID = glCreateShader(TypeShader);
  glShaderSource(ShaderID, 1, &source, NULL);
  glCompileShader(ShaderID);

  glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(ShaderID, 512, NULL, log);
    if (TypeShader == GL_FRAGMENT_SHADER) {
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                << log << std::endl;
      return ShaderID;
    }

    else if (TypeShader == GL_VERTEX_SHADER) {
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                << log << std::endl;
      return ShaderID;
    }
  }

  return ShaderID;
}

unsigned int Phantom::Graphic::Shader::CreateProgram(unsigned int FragShader,
                                            unsigned int VertShader) {

  int success;
  char infoLog[512];

  if (FragShader == 0 || VertShader == 0) {
    std::cerr << "ERROR: Invalid shader ID passed to CreateProgram"
              << std::endl;
    return 0;
  }

  // 2. Проверка, что шейдеры скомпилированы
  glGetShaderiv(VertShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    std::cerr << "ERROR: Vertex shader not compiled!" << std::endl;
    return 0;
  }

  glGetShaderiv(FragShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    std::cerr << "ERROR: Fragment shader not compiled!" << std::endl;
    return 0;
  }

  unsigned int shaderProgram = 0;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, VertShader);
  glAttachShader(shaderProgram, FragShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    return shaderProgram;
  }

  Using();

  glDeleteShader(VertShader);
  glDeleteShader(FragShader);

  return shaderProgram;
}

Phantom::Graphic::Shader::~Shader() { Clear(); }
