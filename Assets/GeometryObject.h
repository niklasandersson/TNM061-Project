#ifndef GEOMETRYOBJECT_H
#define GEOMETRYOBJECT_H

#include "ShaderObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glfw.h>

#include <iostream>
#include <vector>
#include <string>

#include "../Utils/Load.h"
#include "../Utils/vboindexer.h"

class GeometryObject
{
	public:
		GeometryObject(std::string mesh, ShaderObject* shader, glm::mat4 model);
		GeometryObject(std::string mesh, ShaderObject* shader, std::string diffuseMap, glm::mat4 model);
		GeometryObject(std::string mesh, ShaderObject* shader, std::string diffuseMap, std::string alphaMap, glm::mat4 model);
		GeometryObject(std::string mesh, ShaderObject* shader, std::string diffuseMap, std::string alphaMap, std::string normalMap, glm::mat4 model);
		GeometryObject(std::vector<float>& vertex, std::vector<float>& uv, std::vector<float>& normal, ShaderObject* shader, std::string diffuseMap, std::string alphaMap, std::string normalMap, glm::mat4 model);

		~GeometryObject();

		ShaderObject* getShader();
		GLuint& getShaderProgram();

		int getNumberOfVertex();
		int getNumberOfUv();
		int getNumberOfNormal();
		int getNumberofIndex();

		GLfloat* getVertexBuffer();
		GLfloat* getUvBuffer();
		GLfloat* getNormalBuffer();
		unsigned short* getIndexBuffer();

		GLuint& getDiffuseMap();
		GLuint& getAlphaMap();
		GLuint& getNormalMap();

		bool hasAlphaMap();

		void deleteBuffers();

		glm::mat4 getModelMatrix();
		void setModelMatrix(glm::mat4 model);


	private:
		ShaderObject* _shader;
		GLuint _shaderProgram;

		GLuint _diffuseMap;
		GLuint _diffuseMapHandle;
		GLuint _specularMap;
		GLuint _specularMapHandle;
		GLuint _alphaMap;
		GLuint _normalMap;
		GLuint _alphaMapHandle;

		bool _hasAlphaMap;

		glm::vec3 _position;

		std::vector<GLfloat> _vertex;
		std::vector<GLfloat> _uv;
		std::vector<GLfloat> _normal;

		GLfloat* _vertexBuffer;
		GLfloat* _uvBuffer;
		GLfloat* _normalBuffer;
		unsigned short* _indices;


		int _vertexSize;
		int _normalSize;
		int _uvSize;
		int _indexSize;

		glm::mat4 _model;

		void initializeMesh(std::string mesh);
		void initializeShader(ShaderObject* shader);
		void initializeDiffuseMap(std::string diffuseMap);
		void initializeAlphaMap(std::string alphaMap);
		void initializeNormalMap(std::string normalMap);
		void initializeModel(glm::mat4 model);

};

#endif