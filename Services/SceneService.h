#ifndef SCENESERVICE_H
#define SCENESERVICE_H

#include "RenderingService.h"

#include "../Utils/Load.h"
#include "../Utils/PngAnalyser.h"
#include "../Utils/Shader.h"
#include "../Utils/vboindexer.h"
#include "../Utils/Console.h"

#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>

#include "../Assets/GeometryObject.h"
#include "../Assets/ShaderObject.h"
#include "../Assets/CameraObject.h"
#include "../Assets/LightObject.h"
#include "../Assets/TextObject.h"
#include "../Handles/InputHandle.h"
#include "../Handles/InfoHandle.h"
#include "../Handles/TextHandle.h"

class SceneService : public RenderingService
{
	public:
		SceneService(std::string fileName, Console* console);
		~SceneService();

		void render();
		void update();

		void attachInputHandle(InputHandle* inputHandle);
		void attachInfoHandle(InfoHandle* infoHandle);
		void attachTextHandle(TextHandle* textHandle);

		bool isRendered() const;

	private:
		PngAnalyser* _analyser;
		std::vector<GeometryObject*> _sceneObjects;

		GLuint _matrixMvp;
		GLuint _matrixV;
		GLuint _matrixM;
		GLuint _vertexPosition_modelspace;

		CameraObject* _camera;
		glm::mat4* _viewMatrix;
		glm::mat4 _projectionMatrix;
		glm::mat4* _modelMatrices;

		InputHandle* _inputSlot;
		InfoHandle* _infoSlot;
		TextHandle* _textSlot;

		float _horizontalAngle;
		float _verticalAngle;
		double _time;
		double _frameTime;
		int _numberOfFrames;
		bool _isJumping;
		float _jumpTime;
		float _v0;
		float _g;
	
		GLuint VertexArrayID;
		GLuint vertexbuffer;			
		GLuint normalbuffer;
		GLuint uvbuffer;
		GLuint indexbuffer;

		GLuint* _programIDs;
		GLfloat* _vertexBuffer;
		GLfloat* _normalBuffer;
		GLfloat* _uvBuffer;

		unsigned short* _indexBuffer;

		int _totalVertexSize;
		int _totalNormalSize;
		int _totalUvSize;
		int _totalIndexSize;

		int* _vertexSizes;
		int* _indexSizes;
		GLuint* _textures;

		bool _isRendered;
		GLFWmutex th_mutex;

		GLuint _depthMapProgram;
		GLuint* _depthMatrixLocation;
		GLuint _depthMap;
		GLuint _framebuffer;
		GLuint* _shadowMapLocation;
		GLuint _depthMatrix;

		GLuint* _shaderPrograms;
		GLuint* _mvpMatrixLocations;
		GLuint* _viewMatrixLocations;
		GLuint* _modelMatrixLocations;
		GLuint* _diffuseTextureLocations;
		GLuint* _alphaTextureLocations;
		GLuint* _normalTextureLocations;
		GLuint* _timeLocation;

		int _numberOfObjects;
		//lights
		LightObject* _lights;
		GLuint _numberOfLights;
		glm::vec3* _lightPositions;
		glm::vec3* _lightColors;
		float* _lightIntensities;
		float* _lightRadii;
		int* _lightTypes; 

		
		GLuint* _lightPositionsLocations;
		GLuint* _lightColorsLocations;
		GLuint* _lightSpecularColorsLocations;
		GLuint* _lightIntensitiesLocations;
		GLuint* _lightSpecularIntensitiesLocations;
		GLuint* _lightRadiiLocations;
		GLuint* _lightTypesLocations; 
		GLuint* _numberOfLightsLocations;

		TextObject* _fpsText;
		//end lights
		void loadScene(std::string fileName);
		char _scenePositions[8][8];

		void loadSceneOBJ(const char* path);

		bool _isGrid;
		void toggleGrid(bool doIt);
		void showFramerate(bool doIt);
		void useBF(bool doIt);
		void loadMap(std::string map);

		void setConsoleCommands();
		Console* _console;
		double _positionTime;

		void initializeBuffers();
		void initializePart1();
		void initializePart2();
		void initializePart3();
		void initializeAuto();
		void clearSceneObjects();
};

#endif