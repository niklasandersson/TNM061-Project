#include "SceneService.h"

SceneService::SceneService(std::string fileName, Console* console)
: RenderingService("SceneService")
{
	_console = console;
	_positionTime = 0;
	setConsoleCommands();
	_fpsText = new TextObject(10,500);
	_fpsText->setVisible(false);
	_isJumping = false;
	_g = 55.0f;
	_v0 = 30.0f;
	_isGrid = false;	


	_horizontalAngle = 3.1415f;
	_verticalAngle = 0;

	glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
	glfwDisable(GLFW_MOUSE_CURSOR); 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDepthFunc(GL_LESS);
	glEnable( GL_BLEND );
  	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER , GL_LINEAR);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER , GL_LINEAR);

	

	initializePart1();
	//-----------------
	// Shadow map code
	//-----------------

	/*_depthMapProgram = LoadShaders("../../Shaders/depthMap.vs", "../../Shaders/depthMap.fs");
	_depthMatrix = glGetUniformLocation(_depthMapProgram, "depthMVP");

	_framebuffer = 0;
	glGenFramebuffers(1, &_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

	glGenTextures(1, &_depthMap);
	glBindTexture(GL_TEXTURE_2D, _depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _depthMap, 0);
	glDrawBuffer(GL_NONE);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		_isTerminationPending = true;
		_terminationMessage = "Could not initialize framebuffer";
	}*/
	
	//--------------------
	// Shadow map code end
	//--------------------

	//lights
		
	
	_frameTime = glfwGetTime();
	_numberOfFrames = 0;
	std::cout << "6 trace" << std::endl;

	std::cout << "Number of lights active in scene: " << _numberOfLights << std::endl;
}

void
SceneService::initializeBuffers()
{
	_numberOfObjects = _sceneObjects.size();
	std::cout << "*****************************Number of SceneObjects: " << _numberOfObjects << std::endl;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	_programIDs = new GLuint[_numberOfObjects];
	_vertexSizes = new int[_numberOfObjects];
	_totalVertexSize = 0;
	_totalNormalSize = 0;
	_totalUvSize = 0;
	std::cout << "1 trace" << std::endl;

	for (unsigned int i = 0; i < _numberOfObjects; i++)
	{
		_totalVertexSize += _sceneObjects[i]->getNumberOfVertex();
		_totalNormalSize += _sceneObjects[i]->getNumberOfNormal();
		_totalUvSize += _sceneObjects[i]->getNumberOfUv();
		_vertexSizes[i] = _sceneObjects[i]->getNumberOfVertex();
		//std::cout << "Sizes: " << _vertexSizes[i] << std::endl;
	}
	//std::cout << "Total size: " << _totalVertexSize << std::endl;
	std::cout << "2 trace" << std::endl;

	_vertexBuffer = new GLfloat[_totalVertexSize];
	std::cout << "2.1 trace" << std::endl;
	_normalBuffer = new GLfloat[_totalNormalSize];
	std::cout << "2.2 trace" << std::endl;
	_uvBuffer = new GLfloat[_totalUvSize];
	std::cout << "3 trace" << std::endl;
	


	int vertexCounter = 0;
	int normalCounter = 0;
	int uvCounter = 0;
	//
	for (unsigned int i = 0; i < _numberOfObjects; i++)
	{
		GLfloat* vertexBuffer = _sceneObjects[i]->getVertexBuffer();

		GLfloat* normalBuffer = _sceneObjects[i]->getNormalBuffer();

 	 	GLfloat* uvBuffer = _sceneObjects[i]->getUvBuffer();

 	 	for (int j = 0; j < _sceneObjects[i]->getNumberOfVertex() ; j++)
 	 	{
 	 		_vertexBuffer[vertexCounter] = vertexBuffer[j];
 	 		vertexCounter++;
 	 	}

 	 	for (int j = 0; j < _sceneObjects[i]->getNumberOfNormal() ; j++)
 	 	{
 	 		_normalBuffer[normalCounter] = normalBuffer[j];
 	 		normalCounter++;
 	 	}

 	 	for (int j = 0; j < _sceneObjects[i]->getNumberOfUv() ; j++)
 	 	{
 	 		_uvBuffer[uvCounter] = uvBuffer[j];
 	 		uvCounter++;
 	 	}
	} 


	for (int i = 0; i < _numberOfObjects; ++i)
	{
		_sceneObjects[i]->deleteBuffers();
	}
	std::cout << "4 trace" << std::endl;

	glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, (_totalVertexSize) * sizeof(GLfloat), _vertexBuffer, GL_STATIC_DRAW);
	
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, _totalNormalSize * sizeof(GLfloat), _normalBuffer, GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, _totalUvSize * sizeof(GLfloat), _uvBuffer, GL_STATIC_DRAW);
	
	std::cout << "5 trace" << std::endl;


	
 	
	_shaderPrograms = new GLuint[_numberOfObjects];
	_mvpMatrixLocations = new GLuint[_numberOfObjects];
	_viewMatrixLocations = new GLuint[_numberOfObjects];
	_modelMatrixLocations = new GLuint[_numberOfObjects];
	_diffuseTextureLocations = new GLuint[_numberOfObjects];
	_alphaTextureLocations = new GLuint[_numberOfObjects];
	_lightPositionsLocations = new GLuint[_numberOfObjects];
	_lightColorsLocations = new GLuint[_numberOfObjects];
	_lightIntensitiesLocations = new GLuint[_numberOfObjects];
	_lightRadiiLocations = new GLuint[_numberOfObjects];
	_lightTypesLocations = new GLuint[_numberOfObjects]; 
	_numberOfLightsLocations = new GLuint[_numberOfObjects];
	_normalTextureLocations = new GLuint[_numberOfObjects];
	_shadowMapLocation = new GLuint[_numberOfObjects];
	_depthMatrixLocation = new GLuint[_numberOfObjects];
	_timeLocation = new GLuint[_numberOfObjects]; 

	_modelMatrices = new glm::mat4[_numberOfObjects];

	for (int i = 0; i < _numberOfObjects; ++i)
	{
		_shaderPrograms[i] = _sceneObjects[i]->getShaderProgram();
		_mvpMatrixLocations[i] = glGetUniformLocation(_shaderPrograms[i], "MVP");
		_viewMatrixLocations[i] = glGetUniformLocation( _shaderPrograms[i], "V" );
		_modelMatrixLocations[i] = glGetUniformLocation( _shaderPrograms[i], "M" );
		_diffuseTextureLocations[i] = glGetUniformLocation( _shaderPrograms[i], "DiffuseTextureSampler" );
		_alphaTextureLocations[i] = glGetUniformLocation( _shaderPrograms[i], "AlphaTextureSampler" );

		_numberOfLightsLocations[i] = glGetUniformLocation(_shaderPrograms[i], "numberOfLights");
		_lightPositionsLocations[i] = glGetUniformLocation(_shaderPrograms[i], "lightPositions"); 
		_lightColorsLocations[i] = glGetUniformLocation(_shaderPrograms[i], "lightColors"); 
		_lightIntensitiesLocations[i] = glGetUniformLocation(_shaderPrograms[i], "lightIntensities"); 
		_lightRadiiLocations[i] = glGetUniformLocation(_shaderPrograms[i], "lightRadii"); 
		_lightTypesLocations[i] = glGetUniformLocation(_shaderPrograms[i], "lightTypes");
		
		_modelMatrices[i] = _sceneObjects[i]->getModelMatrix();
		_normalTextureLocations[i] = glGetUniformLocation(_shaderPrograms[i], "NormalTextureSampler");
		_shadowMapLocation[i] = glGetUniformLocation(_shaderPrograms[i], "ShadowMapSampler");
		_depthMatrixLocation[i] = glGetUniformLocation(_shaderPrograms[i], "DepthBiasMVP");
		_timeLocation[i] = glGetUniformLocation(_shaderPrograms[i], "Time");

	}

	_viewMatrix = _camera->getViewMatrixPointer();
	_projectionMatrix = _camera->getProjectionMatrix();
	
}

SceneService::~SceneService()
{
	for (unsigned int i = 0; i < _sceneObjects.size(); i++)
	{
		delete _sceneObjects[i]; 
	}

	delete _analyser;
	delete _camera;
	delete _lights;
}

void
SceneService::render()
{	
	_fpsText->setPosition(10, _infoSlot->getWindowHeight() - 190);
	double currentTime = glfwGetTime();
    _numberOfFrames++;
    if(currentTime - _frameTime >= 1)
    {	
    	std::ostringstream stream;
	    stream << "FPS:" << _numberOfFrames;
	  	 //_textSlot->setText(stream.str());
	    _fpsText->setText(stream.str());
	    _numberOfFrames = 0;
	    _frameTime +=1;
    }

		if (_inputSlot->getState() == 0 && _console->isDisplayingInfo() == false)
			{
			if(currentTime - _positionTime > 0.45)	
			{
				_console->getPostionObject()->toggleVisible();
				_positionTime = currentTime;
			}
		} 
		else
		{
			_console->getPostionObject()->setVisible(false);
		}

    glEnableVertexAttribArray(0);
  	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);


     //-----------------
	// Shadow map code
	//-----------------
	/*glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
	glViewport(0,0,1024,1024);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(_depthMapProgram);
	glm::mat4 depthMVP;
	

	glm::vec3 lightPos = _lightPositions[0];
	glm::mat4 depthProjectionMatrix = glm::perspective<float>(45.0f, 1, 0.01f, 1000.0f);
	glm::mat4 depthViewMatrix = glm::lookAt(lightPos, glm::vec3(0,0,0), glm::vec3(0,1,0));

	depthMVP = depthProjectionMatrix * depthViewMatrix;

	glUniformMatrix4fv(_depthMatrix, 1, GL_FALSE, &depthMVP[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, _totalVertexSize);
	
	glm::mat4 biasMatrix = glm::mat4(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
	);

	glm::mat4 depthBiasMVP = biasMatrix * depthMVP;*/
	
	
	//--------------------
	// Shadow map code end
	//--------------------

	glEnable( GL_BLEND );
  	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glViewport(0,0,_infoSlot->getWindowWidth(),_infoSlot->getWindowHeight()); // Render on the whole framebuffer, complete from the lower left corner to the upper right

	

	// Clear the screen
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glEnableVertexAttribArray(1);
  	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
  	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);

  	glEnableVertexAttribArray(2);
  	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
  	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,(void*)0);

	glm::mat4 MV = _projectionMatrix * *_viewMatrix;
 	

 
 		 int verteciesDrawn = 0;
		  for (unsigned int i = 0; i < _numberOfObjects; i++)
		  {	

						glUseProgram(_shaderPrograms[i]);
		  		
						glm::mat4 MVP = MV * _modelMatrices[i];
				 		glUniformMatrix4fv(_mvpMatrixLocations[i], 1, GL_FALSE, &MVP[0][0]);
				 		glUniformMatrix4fv(_viewMatrixLocations[i], 1, GL_FALSE, &(*_viewMatrix)[0][0]);
				 		glUniformMatrix4fv(_modelMatrixLocations[i], 1, GL_FALSE, &(*_modelMatrices)[0][0]);
						
						//light begin

						glUniform1i(_numberOfLightsLocations[i], 1);
						
				 		glUniform3fv(_lightPositionsLocations[i], _numberOfLights, &_lightPositions[0][0]);
				 		glUniform3fv(_lightColorsLocations[i], _numberOfLights, &_lightColors[0][0]);

				 		glUniform1fv(_lightIntensitiesLocations[i], _numberOfLights, _lightIntensities);
				 		glUniform1fv(_lightRadiiLocations[i], _numberOfLights, _lightRadii);

				 		glUniform3iv(_lightTypesLocations[i], _numberOfLights, _lightTypes);

						//glUniformMatrix4fv(_depthMatrixLocation[i], 1, GL_FALSE, &depthBiasMVP[0][0]);
					
						glUniform1f(_timeLocation[i], glfwGetTime());

					//light end
				
						glActiveTexture(GL_TEXTURE0);
			 			glBindTexture(GL_TEXTURE_2D, _sceneObjects[i]->getDiffuseMap());
			 			glUniform1i(_diffuseTextureLocations[i], 0);

					
						glActiveTexture(GL_TEXTURE1);
						glBindTexture(GL_TEXTURE_2D, _sceneObjects[i]->getAlphaMap());
						glUniform1i( _alphaTextureLocations[i], 1);

						glActiveTexture(GL_TEXTURE2);
						glBindTexture(GL_TEXTURE_2D, _sceneObjects[i]->getNormalMap());
						glUniform1i(_normalTextureLocations[i], 2);

						/*glActiveTexture(GL_TEXTURE3);
						glBindTexture(GL_TEXTURE_2D, _depthMap);
						glUniform1i(_shadowMapLocation[i], 3);*/
			

					
						if(!_isGrid)
 						{
			 				glDrawArrays(GL_TRIANGLES, verteciesDrawn/3, (_vertexSizes[i])/3);
			
						} 
						else
						{
							for (int j = 0; j < _vertexSizes[i]; j += 3)
								glDrawArrays(GL_LINE_LOOP, j, 3);
						}

						verteciesDrawn += _vertexSizes[i];
						//glDrawRangeElements(GL_TRIANGLES, indicesDrawn, indicesDrawn + _indexSizes[i], _vertexSizes[i], GL_UNSIGNED_SHORT, (void*)0);
					
					
		  }
		
		
 

/*
 		 glm::mat4 Model = _sceneObjects[0]->getModelMatrix();
		glm::mat4 MVP = Projection * View * Model;

 		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
 		glUniformMatrix4fv(matrix_V, 1, GL_FALSE, &View[0][0]);
 		glUniformMatrix4fv(matrix_M, 1, GL_FALSE, &Model[0][0]);
		glUniform3f(light_Sun, 500, 5000, 1500);

		glActiveTexture(GL_TEXTURE0);
 		glBindTexture(GL_TEXTURE_2D, _sceneObjects[0]->getDiffuseMap());
 		glUniform1i(DiffuseTextureHandle, 0);

		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _sceneObjects[0]->getAlphaMap());
		glUniform1i( AlphaTextureHandle, 1);

 		glDrawArrays(GL_TRIANGLES, 0, _totalVertexSize);*/

  /*glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);*/

  
}


void
SceneService::update()
{
	_infoSlot->setIsJumping(_isJumping);

	if(_inputSlot == NULL)
	{
		_isTerminationPending = true;
		_terminationMessage = "No InputHandle";
	}

	if(_infoSlot == NULL)
	{
		_isTerminationPending = true;
		_terminationMessage = "No InfoHandle";
	}

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - _time);
		//std::cout << deltaTime;

	int xpos, ypos;
	glfwGetMousePos(&xpos, &ypos);
	int width , height;
	glfwGetWindowSize(&width,&height);
	glfwSetMousePos(width/2, height/2);

  	_horizontalAngle += _camera->getLookingSpeed() * float(width/2 - xpos );
	_verticalAngle   += _camera->getLookingSpeed() * float( height/2 - ypos );

	glm::vec3 direction(
		cos(_verticalAngle) * sin(_horizontalAngle),
		sin(_verticalAngle),
		cos(_verticalAngle) * cos(_horizontalAngle)
	);

	glm::vec3 right = glm::vec3(
		sin(_horizontalAngle - 3.14f/2.0f),
		0,
		cos(_horizontalAngle - 3.14f/2.0f)
	);

	

    glm::vec3 up = glm::cross( right, direction );
    glm::vec3 xzDirection = glm::vec3(direction.x,0,direction.z);
	glm::vec3 jumpDirection = glm::vec3(0, 1,0);

	if (_inputSlot->isKeyDown(InputHandle::KEY_W))
	{
		direction.x += 0.02*sin(currentTime*7);
		direction.y += 0.01*sin(currentTime*7);
		_camera->addToPosition(xzDirection * deltaTime * _camera->getMovmentSpeed());
	}
	if (_inputSlot->isKeyDown(InputHandle::KEY_S))
	{
		direction.x += 0.02*sin(currentTime*7);
		direction.y += 0.01*sin(currentTime*7);
		_camera->subtractFromPosition(xzDirection * deltaTime * _camera->getMovmentSpeed());
	}
	if (_inputSlot->isKeyDown(InputHandle::KEY_D))
	{
		direction.x += 0.02*sin(currentTime*7);
		direction.y += 0.01*sin(currentTime*7);
		_camera->addToPosition(right * deltaTime * _camera->getMovmentSpeed());
	}
	if (_inputSlot->isKeyDown(InputHandle::KEY_A))
	{
		direction.x += 0.02*sin(currentTime*7);
		direction.y += 0.01*sin(currentTime*7);
		_camera->subtractFromPosition(right * deltaTime * _camera->getMovmentSpeed());
	}

	//Jumping 
	
	
	if (_inputSlot->isKeyDown(InputHandle::KEY_SPACE) && !_isJumping)
	{
		_jumpTime = currentTime;
		_isJumping = true;
	}
	else if(_isJumping)
	{
		float time = currentTime - _jumpTime;
		float tmp = 7 +  _v0 * time - 0.5 * _g * time * time;
		_camera->setYPosition(tmp);

		if(_camera->getPosition().y <= 7)
		{
			_camera->setYPosition(7.0f);
			_jumpTime = 0;
			_isJumping = false;
		}
	}
	// Jumping end

	_camera->setAspectRation( _infoSlot->getWindowWidth() / _infoSlot->getWindowHeight());
	_camera->setViewMatrix(glm::lookAt(
								_camera->getPosition(), 
								_camera->getPosition()+direction, 
								up            
						   ));

	_time = currentTime;
}

void
SceneService::setConsoleCommands()
{
	_console->quickAdd("showGrid", this, &SceneService::toggleGrid);
	_console->quickAdd("showFPS", this, &SceneService::showFramerate);
	_console->quickAdd("useBF", this, &SceneService::useBF);
	_console->quickAdd("loadMap", this, &SceneService::loadMap);
}

void
SceneService::loadScene(std::string fileName)
{

	
	//_sceneObjects.push_back(new GeometryObject("../../Meshes/pointlightTest.obj", new ShaderObject("../../Shaders/standardModelTransform.vs","../../Shaders/standardLightCalc.fs"), "../../Textures/DirtyConcrete.dds", "../../Textures/no_alpha.DDS", glm::mat4(1.0f)));

//_sceneObjects.push_back(new GeometryObject("../../Meshes/pointlightTest.obj", new ShaderObject("../../Shaders/room1.vs","../../Shaders/room1.fs"), "../../Textures/slide1_diffuse.dds", "../../Textures/no_alpha.dds", "../../Textures/normal.dds", glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0))));
	
//_sceneObjects.push_back(new GeometryObject("../../Meshes/skyBox.obj", new ShaderObject("../../Shaders/lightTexDiff.vs","../../Shaders/sky.fs"), "../../Textures/testBox.DDS", "../../Textures/no_alpha.DDS",glm::translate(glm::mat4(1.0f), glm::vec3(1,-500,1))));

		
	

	//_sceneObjects.push_back(new GeometryObject("../../Meshes/palmtree.obj", new ShaderObject("../../Shaders/standardModelTransform.vs","../../Shaders/standardLightCalc.fs"), "../../Textures/palmtree.DDS", "../../Textures/palmtree_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0))));

	/*_sceneObjects.push_back(new GeometryObject("../../Meshes/palmtree.obj", new ShaderObject("../../Shaders/lightTexDiff.vs","../../Shaders/lightTexDiff.fs"), "../../Textures/palmtree.DDS", "../../Textures/palmtree_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0))));
	_sceneObjects.push_back(new GeometryObject("../../Meshes/bamboopalm.obj", new ShaderObject("../../Shaders/lightTexDiff.vs","../../Shaders/lightTexDiff.fs"), "../../Textures/bamboopalm.DDS", "../../Textures/bamboopalm_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(10,0,10))));
	_sceneObjects.push_back(new GeometryObject("../../Meshes/hightree.obj", new ShaderObject("../../Shaders/lightTexDiff.vs","../../Shaders/lightTexDiff.fs"), "../../Textures/hightree.DDS", "../../Textures/hightree_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(20,0,20))));
	_sceneObjects.push_back(new GeometryObject("../../Meshes/groundpalm.obj", new ShaderObject("../../Shaders/lightTexDiff.vs","../../Shaders/lightTexDiff.fs"), "../../Textures/groundpalm.DDS", "../../Textures/groundpalm_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(30,0,30))));
	_sceneObjects.push_back(new GeometryObject("../../Meshes/smallplant.obj", new ShaderObject("../../Shaders/lightTexDiff.vs","../../Shaders/lightTexDiff.fs"), "../../Textures/smallplant.DDS", "../../Textures/smallplant_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(40,0,40))));
	*/// Testar lite*/
	//_sceneObjects.push_back(new GeometryObject("../../Meshes/heli.obj", new ShaderObject("../../Shaders/lightTexDiff.vs","../../Shaders/lightTexDiff.fs"), "../../Textures/heli.DDS", "../../Textures/no_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(40,0,40))));
	/*_sceneObjects.push_back(new GeometryObject("../../Meshes/apc.obj", new ShaderObject("../../Shaders/shadow.vs","../../Shaders/shadow.fs"), "../../Textures/apc.DDS", "../../Textures/no_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(40,0,40))));
	_sceneObjects.push_back(new GeometryObject("../../Meshes/tent.obj", new ShaderObject("../../Shaders/shadow.vs","../../Shaders/shadow.fs"), "../../Textures/tent.DDS", "../../Textures/no_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(40,0,40))));
	_sceneObjects.push_back(new GeometryObject("../../Meshes/truck.obj", new ShaderObject("../../Shaders/lightTexDiff.vs","../../Shaders/lightTexDiff.fs"), "../../Textures/truck.DDS", "../../Textures/no_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(40,0,40))));
	_sceneObjects.push_back(new GeometryObject("../../Meshes/uav.obj", new ShaderObject("../../Shaders/lightTexDiff.vs","../../Shaders/lightTexDiff.fs"), "../../Textures/uav.DDS", "../../Textures/no_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(40,0,40))));
	_sceneObjects.push_back(new GeometryObject("../../Scenes/scene1.obj", new ShaderObject("../../Shaders/lightTexDiff.vs","../../Shaders/lightTexDiff.fs"), "../../Textures/fueltank_diffuse.DDS", "../../Textures/no_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(2,0,-6))));
	_sceneObjects.push_back(new GeometryObject("../../Meshes/sandbags.obj", new ShaderObject("../../Shaders/lightTexDiff.vs","../../Shaders/lightTexDiff.fs"), "../../Textures/sandbags_diffuse.DDS", "../../Textures/no_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(2,0,-6))));
		//_sceneObjects.push_back(new GeometryObject("../../Scenes/scene1.obj", new ShaderObject("../../Shaders/lightTexDiff.vs","../../Shaders/lightTexDiff.fs"), "../../Textures/fueltank_diffuse.DDS", "../../Textures/no_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(2,0,-6))));
	*/
	//loadSceneOBJ("../../Scenes/room1.obj");
loadSceneOBJ("../../Scenes/part2.obj");
}

void
SceneService::attachInputHandle(InputHandle* inputHandle)
{
	_inputSlot = inputHandle;
}

void
SceneService::attachInfoHandle(InfoHandle* infoHandle)
{
	_infoSlot = infoHandle;
}

void
SceneService::attachTextHandle(TextHandle* textHandle)
{
	_textSlot = textHandle;
	_textSlot->addText(_fpsText);
}

void 
SceneService::loadSceneOBJ(const char* path)
{
	vector<float> VT;
	vector<float> UV;
	vector<float> NS;

	cout << "SCENELoading: " << path << endl;

	vector<unsigned int> IVT, IUV, INS;  // Index

  vector<glm::vec3> VT_temp, NS_temp;
	vector<glm::vec3> UV_temp;

  ifstream file(path);

  if(file.good())
		cout << "Succeeded open the file: " << path << endl;
	else
		cout << "Failed open the file: " << path << endl;

	string line = "";

	char cTrash;
	string sTrash;

	glm::vec3 vertex, normal;
	glm::vec3 uv;

	unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
	
	bool first = true;
	std::string lastName = "fueltank";
	while (getline(file, line)) 
	{

		istringstream is(line);
				
		if (line[0] == 'v')
		{
			if (line[1] == ' ')
			{
				is >> sTrash >> ws >> vertex.x >> ws >> vertex.y >> ws >> vertex.z;
				VT_temp.push_back( vertex );
			}
			else if (line[1] == 'n')
			{
				is >> sTrash >> ws >> normal.x >> ws >> normal.y >> ws >> normal.z;
				NS_temp.push_back( normal );
			}
			else if (line[1] == 't')
			{
				is >> sTrash >> ws >> uv.x >> ws >> uv.y;

				uv.y = -uv.y;

				UV_temp.push_back(uv);
			}
		}
		else if (line[0] == 'f')
		{
			is >> sTrash >> ws >> vertexIndex[0] >> cTrash >> uvIndex[0] >> cTrash >> normalIndex[0] >> ws
                         >> vertexIndex[1] >> cTrash >> uvIndex[1] >> cTrash >> normalIndex[1] >> ws
                         >> vertexIndex[2] >> cTrash >> uvIndex[2] >> cTrash >> normalIndex[2];

			IVT.push_back(vertexIndex[0]);
			IVT.push_back(vertexIndex[1]);
			IVT.push_back(vertexIndex[2]);

			IUV.push_back(uvIndex[0]);
			IUV.push_back(uvIndex[1]);
      IUV.push_back(uvIndex[2]);

			INS.push_back(normalIndex[0]);
			INS.push_back(normalIndex[1]);
			INS.push_back(normalIndex[2]);
		}  	
		else if (line[0] == '#' && !first) 
		{
			std::string obj = "object";
			std::string temp;
			std::string name;
			is >> sTrash >> ws >> temp >> ws >> name;
			if (temp == obj) {
			//	std::cout << "LOADSCENEOBJ NEW OBJECT: " <<name << std::endl;
				// Create New Object
				for(unsigned int i=0 ; i < IVT.size(); i++)
				{
					glm::vec3 vertex = VT_temp[ IVT[i]-1 ];
					VT.push_back( vertex.x );
					VT.push_back( vertex.y );
					VT.push_back( vertex.z );   
				}

				for (unsigned int i = 0; i < INS.size(); i++)
				{
					glm::vec3 normal = NS_temp[ INS[i]-1 ];
					NS.push_back( normal.x );
					NS.push_back( normal.y );
					NS.push_back( normal.z );
				}

				for (unsigned int i = 0; i < IUV.size(); i++)
				{
					glm::vec3 uv = UV_temp[ IUV[i]-1 ];
					UV.push_back( uv.x );
					UV.push_back( uv.y );
				}

				// Store object
				std::cout << "___________________SCENE:_____________________________PUSHBACK: " << lastName << std::endl;
				std::string temp2 = "../../Textures/" + lastName + "_diffuse.DDS";
				std::string temp3 = "../../Textures/" + lastName + "_normal.DDS";
				std::string temp4 = "../../Textures/" + lastName + "_alpha.DDS";
				std::string temp5 = "../../Shaders/" + lastName + ".vs";
				std::string temp6 = "../../Shaders/" + lastName + ".fs";
				std::cout << "temp2 = " << temp2 << std::endl;
			//	temp2 = "../../Textures/palmtree.DDS";
				_sceneObjects.push_back(new GeometryObject(VT, UV, NS, new ShaderObject(temp5.c_str(),temp6.c_str()), temp2.c_str(), temp4.c_str(), temp3.c_str(), glm::translate(glm::mat4(1.0f), glm::vec3(2,0,-6))));
	
				// Clear vectors
				VT.clear();
				UV.clear();
				NS.clear();

				// Vet ej om dessa ska clearas
			/*	IVT.clear();
				IUV.clear();
				INS.clear(); */

				std::cout << "__________________________________DONE_______________________________________" << std::endl;
				lastName = name;
			}
		}
		else if (line[0] == '#' && first) 
		{
			std::string obj = "object";
			std::string temp;
			std::string name;
			is >> sTrash >> ws >> temp >> ws >> name;
			if (temp == obj) {
				first = false;
			//	std::cout << "First is false: " << name << std::endl;
				lastName = name;
			}
		}

	}
	
	file.close();
	

	for(unsigned int i=0 ; i < IVT.size(); i++)
  {
		glm::vec3 vertex = VT_temp[ IVT[i]-1 ];
		VT.push_back( vertex.x );
		VT.push_back( vertex.y );
		VT.push_back( vertex.z );   
	}

	for (unsigned int i = 0; i < INS.size(); i++)
	{
		glm::vec3 normal = NS_temp[ INS[i]-1 ];
		NS.push_back( normal.x );
		NS.push_back( normal.y );
		NS.push_back( normal.z );
	}

	for (unsigned int i = 0; i < IUV.size(); i++)
	{
		glm::vec3 uv = UV_temp[ IUV[i]-1 ];
		UV.push_back( uv.x );
		UV.push_back( uv.y );
	}

	// Store last object
		std::string temp2 = "../../Textures/" + lastName + "_diffuse.DDS";
		std::string temp3 = "../../Textures/" + lastName + "_normal.DDS";
		std::string temp4 = "../../Textures/" + lastName + "_alpha.DDS";
		std::string temp5 = "../../Shaders/" + lastName + ".vs";
		std::string temp6 = "../../Shaders/" + lastName + ".fs";
	_sceneObjects.push_back(new GeometryObject(VT, UV, NS, new ShaderObject(temp5.c_str(),temp6.c_str()), temp2.c_str(), temp4.c_str(), temp3.c_str(), glm::translate(glm::mat4(1.0f), glm::vec3(2,0,-6))));

}

void
SceneService::toggleGrid(bool doIt)
{
	_isGrid = doIt;
}

void
SceneService::showFramerate(bool doIt)
{
	_fpsText->setVisible(doIt);
}

void
SceneService::useBF(bool doIt)
{
	if(doIt)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER , GL_LINEAR);
  		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER , GL_LINEAR);
	}else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER , GL_NEAREST );
	  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER , GL_NEAREST );
	}
}

void
SceneService::loadMap(std::string map)
{
	if(map == "part1")
	{	
		clearSceneObjects();
		initializePart1();
	}else if(map == "part2")
	{	
		clearSceneObjects();
		initializePart2();
	}else if(map == "auto")
	{
		clearSceneObjects();
		initializeAuto();
	}else if(map == "part3")
	{
		clearSceneObjects();
		initializePart3();
	}


}

void
SceneService::clearSceneObjects()
{
		for (unsigned int i = 0; i < _sceneObjects.size(); i++)
		{
			delete _sceneObjects[i]; 
		}
		_sceneObjects.clear();

		delete _programIDs;
		delete _vertexSizes;
		delete _vertexBuffer;
		delete _normalBuffer;
		delete _uvBuffer;
		delete _camera;
		delete _lights;
		
}

void
SceneService::initializePart1()
{

	_camera = new CameraObject(45.0f, 4/3, 0.1f, 300.0f,
														 glm::vec3(-50,7,-8),  // Position
														 glm::vec3(0,0.5,0),   // Look at
														 glm::vec3(0,1,0));  // Orientation

	loadSceneOBJ("../../Scenes/part1.obj");
	initializeBuffers();
	_lights = new LightObject(12);
	_lights->addPointLight(glm::vec3(30,10,30), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 1
	_lights->addPointLight(glm::vec3(35,10,175), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 2
	_lights->addPointLight(glm::vec3(-185,10,115), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 3
	_lights->addPointLight(glm::vec3(-160,10,350), glm::vec3(0.18,0.46,1.0), 5, 1); //bakom slide 4
	_lights->addPointLight(glm::vec3(15,10,285), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 5
	_lights->addPointLight(glm::vec3(-50,10,200), glm::vec3(0.7,0.5,0.6), 10, 1); // Tanken


	_lights->addPointLight(glm::vec3(0,15,90), glm::vec3(0.18,1.0,0.46), 1, 1); //sign 1
	_lights->addPointLight(glm::vec3(-100,15,150), glm::vec3(0.18,1.0,0.46), 1, 1); //sign 2
	_lights->addPointLight(glm::vec3(-160,15,250), glm::vec3(0.18,1.0,0.46), 1, 1); //sign 3
	_lights->addPointLight(glm::vec3(-70,15,310), glm::vec3(0.18,1.0,0.46), 1, 1); //sign 4
	_lights->addPointLight(glm::vec3(0,15,420), glm::vec3(0.18,1.0,0.46), 1, 1); //sign 5
		
		

	_numberOfLights = _lights->getNumberOfLights();

	_lightPositions = _lights->getPositions();
	_lightColors = _lights->getColors();
	_lightIntensities = _lights->getIntensities();
	_lightRadii = _lights->getRadii();
	_lightTypes = _lights->getLightTypes();
}

void
SceneService::initializePart2()
{
	_camera = new CameraObject(45.0f, 4/3, 0.1f, 1000.0f,
														 glm::vec3(40,7,-40),  // Position
														 glm::vec3(-1,0.2,0.7),   // Look at
														 glm::vec3(0,1,0));  // Orientation

	loadSceneOBJ("../../Scenes/part2.obj");
	initializeBuffers();
	_lights = new LightObject(12);
	_lights->addPointLight(glm::vec3(-2,10,40), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 1
	_lights->addPointLight(glm::vec3(-30,10,-30), glm::vec3(0.18,0.46,1.0), 4, 1); //minerals
	_lights->addPointLight(glm::vec3(150,10,-40), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 2
	_lights->addPointLight(glm::vec3(190,10,-40), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 3
	_lights->addPointLight(glm::vec3(190,10,10), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 4
	_lights->addPointLight(glm::vec3(240,10,150), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 5
	_lights->addPointLight(glm::vec3(200,10,40), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 6
_lights->addPointLight(glm::vec3(20,20,160), glm::vec3(0.18,0.46,1.0), 3, 1);

	_lights->addPointLight(glm::vec3(90,15,0), glm::vec3(0.18,1.0,0.46), 1, 1); //sign 1
	_lights->addPointLight(glm::vec3(160,10,100), glm::vec3(0.18,1.0,0.46), 1, 1); //sign 2
		
		

	_numberOfLights = _lights->getNumberOfLights();

	_lightPositions = _lights->getPositions();
	_lightColors = _lights->getColors();
	_lightIntensities = _lights->getIntensities();
	_lightRadii = _lights->getRadii();
	_lightTypes = _lights->getLightTypes();
}

void
SceneService::initializeAuto()
{

	_camera = new CameraObject(45.0f, 4/3, 0.1f, 300.0f,
														 glm::vec3(5,7,20),  // Position
														 glm::vec3(0,-1,0),   // Look at
														 glm::vec3(0,1,0));  // Orientation

	_analyser = new PngAnalyser("../../Images/img.png");
	for (unsigned int i = 0; i < _analyser->getX(); i++)
	{
		for (unsigned int j = 0; j < _analyser->getY(); ++j)
		{
			int color = _analyser->getColor(i,j);
			if(color == 1)
				_sceneObjects.push_back(new GeometryObject("../../Meshes/bitObject_tile.obj", new ShaderObject("../../Shaders/room.vs","../../Shaders/room.fs"), "../../Textures/bitTexture_tile.dds", "../../Textures/no_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(10*i,1,10*j))));

			else if(color == 2)
				_sceneObjects.push_back(new GeometryObject("../../Meshes/bitObject_wall.obj", new ShaderObject("../../Shaders/room.vs","../../Shaders/room.fs"), "../../Textures/bitTexture_tile.dds", "../../Textures/no_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(10*i,1,10*j))));
			else if(color == 0)
			{
				_sceneObjects.push_back(new GeometryObject("../../Meshes/bitObject_tile.obj", new ShaderObject("../../Shaders/room.vs","../../Shaders/room.fs"), "../../Textures/bitTexture_tile.dds", "../../Textures/no_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(10*i,1,10*j))));
				_sceneObjects.push_back(new GeometryObject("../../Meshes/vase.obj", new ShaderObject("../../Shaders/room.vs","../../Shaders/room.fs"), "../../Textures/vase_diffuse.DDS", "../../Textures/no_alpha.DDS", glm::translate(glm::mat4(1.0f), glm::vec3(10*i,1,10*j))));

			}
		}
	}

	initializeBuffers();
	_lights = new LightObject(12);
	_lights->addPointLight(glm::vec3(30,10,30), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 1
	_lights->addPointLight(glm::vec3(35,10,175), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 2
	_lights->addPointLight(glm::vec3(-185,10,115), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 3
	_lights->addPointLight(glm::vec3(-160,10,350), glm::vec3(0.18,0.46,1.0), 5, 1); //bakom slide 4
	_lights->addPointLight(glm::vec3(15,10,285), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 5
	_lights->addPointLight(glm::vec3(30,10,510), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 6


	_lights->addPointLight(glm::vec3(0,15,90), glm::vec3(0.18,1.0,0.46), 1, 1); //sign 1
	_lights->addPointLight(glm::vec3(-100,15,150), glm::vec3(0.18,1.0,0.46), 1, 1); //sign 2
	_lights->addPointLight(glm::vec3(-160,15,250), glm::vec3(0.18,1.0,0.46), 1, 1); //sign 3
	_lights->addPointLight(glm::vec3(-70,15,310), glm::vec3(0.18,1.0,0.46), 1, 1); //sign 4
	_lights->addPointLight(glm::vec3(0,15,420), glm::vec3(0.18,1.0,0.46), 1, 1); //sign 5
		
		

	_numberOfLights = _lights->getNumberOfLights();

	_lightPositions = _lights->getPositions();
	_lightColors = _lights->getColors();
	_lightIntensities = _lights->getIntensities();
	_lightRadii = _lights->getRadii();
	_lightTypes = _lights->getLightTypes();

}

void
SceneService::initializePart3()
{
	_camera = new CameraObject(45.0f, 4/3, 0.1f, 1000.0f,
														 glm::vec3(150,7,-20),  // Position
														 glm::vec3(-1,0.2,0.7),   // Look at
														 glm::vec3(0,1,0));  // Orientation

	loadSceneOBJ("../../Scenes/part2.obj");
	initializeBuffers();
	_lights = new LightObject(12);
	_lights->addPointLight(glm::vec3(-2,10,40), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 1
	_lights->addPointLight(glm::vec3(-30,10,-30), glm::vec3(0.18,0.46,1.0), 4, 1); //minerals
	_lights->addPointLight(glm::vec3(150,10,-40), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 2
	_lights->addPointLight(glm::vec3(190,10,-40), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 3
	_lights->addPointLight(glm::vec3(190,10,10), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 4
	_lights->addPointLight(glm::vec3(240,10,150), glm::vec3(0.18,0.46,1.0), 2, 1); //bakom slide 5
	_lights->addPointLight(glm::vec3(20,20,160), glm::vec3(0.18,0.46,1.0), 3, 1);

	_lights->addPointLight(glm::vec3(90,15,0), glm::vec3(0.18,1.0,0.46), 1, 1); //sign 1
	_lights->addPointLight(glm::vec3(160,10,100), glm::vec3(0.18,1.0,0.46), 1, 1); //sign 2
		
		

	_numberOfLights = _lights->getNumberOfLights();

	_lightPositions = _lights->getPositions();
	_lightColors = _lights->getColors();
	_lightIntensities = _lights->getIntensities();
	_lightRadii = _lights->getRadii();
	_lightTypes = _lights->getLightTypes();
}

