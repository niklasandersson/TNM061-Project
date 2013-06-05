
#include "Shader.h"

GLuint LoadShaders(const char* vsPath, const char* fsPath)
{

    GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vsPath, std::ios::in);

    if( VertexShaderStream.good() )
    {
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    } else
        std::cout << "Error reading the vertex-shader." << std::endl;

    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fsPath, std::ios::in);

    if( FragmentShaderStream.good() )
    {
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    } else
        std::cout << "Error reading the fragment-shader." << std::endl;

    GLint Result = GL_FALSE;
    int InfoLogLength;

    std::cout << "Compiling Shader: " << vsPath << std::endl;
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShader, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShader);

    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    char* vsError = new char[InfoLogLength];
    glGetShaderInfoLog(VertexShader, InfoLogLength, NULL, vsError);
    //if(!vsError)
        std::cout << "Vertex-shader error message: " << vsError << std::endl;
    delete [] vsError;


    std::cout << "Compiling Shader: " << fsPath << std::endl;
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShader, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShader);

    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    char* fsError = new char[InfoLogLength];
    glGetShaderInfoLog(FragmentShader, InfoLogLength, NULL, fsError);
   // if(!fsError)
        std::cout << "Fragment-shader error message: " << fsError << std::endl;
    delete [] fsError;

    std::cout << "Linking program." << std::endl;
    GLuint Program = glCreateProgram();
    glAttachShader(Program, VertexShader);
    glAttachShader(Program, FragmentShader);
    glLinkProgram(Program);

    glGetProgramiv(Program, GL_LINK_STATUS, &Result);
    glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &InfoLogLength);
    InfoLogLength = InfoLogLength < 1 ? 1 : InfoLogLength;
    char* programError = new char[InfoLogLength];
    glGetProgramInfoLog(Program, InfoLogLength, NULL, programError);
 //   if(!programError)
        std::cout << "Program-linking error message: " << programError << std::endl;
    delete [] programError;

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    return Program;
}
