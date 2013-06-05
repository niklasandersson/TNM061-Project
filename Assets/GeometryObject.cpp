#include "GeometryObject.h"

GeometryObject::GeometryObject(std::string mesh, ShaderObject* shader, glm::mat4 model)
{
	_hasAlphaMap = false;
	initializeMesh(mesh);
	initializeShader(shader);
	initializeModel(model);
}

GeometryObject::GeometryObject(std::string mesh, ShaderObject* shader, std::string diffuseMap, glm::mat4 model)
{
	_hasAlphaMap = false;
	initializeMesh(mesh);
	initializeShader(shader);
	initializeDiffuseMap(diffuseMap);
	initializeModel(model);
}

GeometryObject::GeometryObject(std::string mesh, ShaderObject* shader, std::string diffuseMap, std::string alphaMap, glm::mat4 model)
{
	_hasAlphaMap = true;
	initializeMesh(mesh);
	initializeShader(shader);
	initializeDiffuseMap(diffuseMap);
	initializeAlphaMap(alphaMap);
	initializeModel(model);
}

GeometryObject::GeometryObject(std::string mesh, ShaderObject* shader, std::string diffuseMap, std::string alphaMap, std::string normalMap, glm::mat4 model)
{
	_hasAlphaMap = true;
	initializeMesh(mesh);
	initializeShader(shader);
	initializeDiffuseMap(diffuseMap);
	initializeAlphaMap(alphaMap);
	initializeNormalMap(normalMap);
	initializeModel(model);
}

GeometryObject::GeometryObject(std::vector<float>& vertex, std::vector<float>& uv, std::vector<float>& normal, ShaderObject* shader, std::string diffuseMap, std::string alphaMap, std::string normalMap, glm::mat4 model)
{
	_hasAlphaMap = true;

	_vertex = vertex;
	_uv = uv;
	_normal = normal;

	_vertexSize = _vertex.size();
	_normalSize =_normal.size();
	_uvSize = _uv.size();

	_vertexBuffer = new GLfloat[_vertexSize];
	_uvBuffer = new GLfloat[_uvSize];
	_normalBuffer = new GLfloat[_normalSize];
	
	for (unsigned int i = 0; i < _vertexSize; i++)
		_vertexBuffer[i] = _vertex[i];

	for (unsigned int i = 0; i < _uvSize; i++)
		_uvBuffer[i] = _uv[i];

	for (unsigned int i = 0; i < _normalSize; i++)
		_normalBuffer[i] = _normal[i];

	_vertex.clear();
	_normal.clear();
	_uv.clear();

	initializeShader(shader);
	initializeDiffuseMap(diffuseMap);
	initializeAlphaMap(alphaMap);
	initializeModel(model);
	initializeNormalMap(normalMap);

}


void
GeometryObject::initializeMesh(std::string mesh)
{
	loadOBJ(mesh.c_str(), _vertex, _uv, _normal);
	//std::cout << "Geo size: " << _vertex.size() << std::endl;

	_vertexSize = _vertex.size();
	_normalSize =_normal.size();
	_uvSize = _uv.size();

	_vertexBuffer = new GLfloat[_vertexSize];
	_uvBuffer = new GLfloat[_uvSize];
	_normalBuffer = new GLfloat[_normalSize];
	
	for (unsigned int i = 0; i < _vertexSize; i++)
		_vertexBuffer[i] = _vertex[i];

	for (unsigned int i = 0; i < _uvSize; i++)
		_uvBuffer[i] = _uv[i];

	for (unsigned int i = 0; i < _normalSize; i++)
		_normalBuffer[i] = _normal[i];

	_vertex.clear();
	_normal.clear();
	_uv.clear();


/*
	std::vector<unsigned short> out_indices;
	std::vector<glm::vec3> out_vertices;
	std::vector<glm::vec2> out_uvs;
	std::vector<glm::vec3> out_normals;

	indexVBO(_vertex, _uv, _normal, out_indices, out_vertices, out_uvs, out_normals);

	_vertexSize = out_vertices.size();
	_normalSize = out_normals.size();
	_uvSize = out_uvs.size();
	_indexSize = out_indices.size();

	_vertexBuffer = new GLfloat[_vertexSize];
	_uvBuffer = new GLfloat[_uvSize];
	_normalBuffer = new GLfloat[_normalSize];

	
	int vertexNumber = 0;
	for (int i = 0; i < _vertexSize; i += 3)
	{
		_vertexBuffer[i] = out_vertices[vertexNumber].x;
		_vertexBuffer[i + 1] = out_vertices[vertexNumber].y;
		_vertexBuffer[i + 2] = out_vertices[vertexNumber].z;
		vertexNumber++;
	}

	int uvNumber = 0;
	for (int i = 0; i < _uvSize; i += 2)
	{
		_uvBuffer[i] = out_uvs[uvNumber].x;
		_uvBuffer[i + 1] = out_uvs[uvNumber].y;
		uvNumber++;
	}

	int normalNumber = 0;
	for (int i = 0; i < _normalSize; i += 3)
	{
		_normalBuffer[i] = out_normals[normalNumber].x;
		_normalBuffer[i + 1] = out_normals[normalNumber].y;
		_normalBuffer[i + 2] = out_normals[normalNumber].z;
		normalNumber++;
	}

	_indices = new unsigned short[_indexSize];

	for (int i = 0; i < _indexSize; ++i)
	{
		_indices[i] = out_indices[i];
	}

	_vertexSize = vertexNumber*3;
	_normalSize = normalNumber*3;
	_uvSize = uvNumber*2;
*/
	
	
}

void
GeometryObject::initializeShader(ShaderObject* shader)
{
	_shader = shader;
	_shaderProgram = _shader->ShaderObject::getShaderProgram();
}

void
GeometryObject::initializeDiffuseMap(std::string diffuseMap)
{
	_diffuseMap = loadDDS(diffuseMap.c_str());
}

void
GeometryObject::initializeAlphaMap(std::string alphaMap)
{
	_alphaMap = loadDDS(alphaMap.c_str());
}

void
GeometryObject::initializeNormalMap(std::string normalMap)
{
	_normalMap = loadDDS(normalMap.c_str());
}

void
GeometryObject::initializeModel(glm::mat4 model)
{
	_model = model;
}

GeometryObject::~GeometryObject()
{
	delete _shader;
}

ShaderObject* 
GeometryObject::getShader()
{
	return _shader;
}

int
GeometryObject::getNumberOfVertex()
{
	return _vertexSize;
}

int
GeometryObject::getNumberOfUv()
{
	return _uvSize;
}

int
GeometryObject::getNumberOfNormal()
{
	return _normalSize;
}

int
GeometryObject::getNumberofIndex()
{
	return _indexSize;
}

GLuint&
GeometryObject::getShaderProgram()
{
	return _shaderProgram;
}

GLfloat*
GeometryObject::getVertexBuffer()
{
	return _vertexBuffer;
}

GLfloat*
GeometryObject::getUvBuffer()
{
	return _uvBuffer;
}

GLfloat*
GeometryObject::getNormalBuffer()
{
	return _normalBuffer;
}

unsigned short*
GeometryObject::getIndexBuffer()
{
	return _indices;
}

GLuint&
GeometryObject::getDiffuseMap()
{
	return _diffuseMap;
}

GLuint&
GeometryObject::getAlphaMap()
{
	return _alphaMap;
}

GLuint&
GeometryObject::getNormalMap()
{
	return _normalMap;
}

glm::mat4
GeometryObject::getModelMatrix()
{
	return _model;
}

void
GeometryObject::setModelMatrix(glm::mat4 model)
{
	_model = model;
}

bool
GeometryObject::hasAlphaMap()
{
	return _hasAlphaMap;
}

void
GeometryObject::deleteBuffers()
{
	delete _vertexBuffer;
	delete _normalBuffer;
	delete _uvBuffer;
}