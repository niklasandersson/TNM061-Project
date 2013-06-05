#include "TextService.h"

TextService::TextService(std::string texturePath)
: RenderingService("TextService")
{
	_textHandle = new TextHandle();

	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	if(glfwLoadTexture2D(texturePath.c_str(), 0))
	{
		std::cout << "Successfully opened text texture: " << texturePath << std::endl;
	}else
	{
		std::cout << "Failed to open text texture: " << texturePath << std::endl;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);


	glGenBuffers(1, &_vertexBufferID);
	glGenBuffers(1, &_uvBufferID);

	_shaderID = LoadShaders("../../Shaders/Text.vs", "../../Shaders/Text.fs");

	_textureUniformID = glGetUniformLocation(_shaderID, "texture");

	_vertexBuffer = new glm::vec2[10000];
	_uvBuffer = new glm::vec2[10000];
	


	changeText("Hello World");

	_size = 17;

}

TextService::~TextService()
{
	delete _textHandle;
}

TextHandle*
TextService::getTextHandle()
{
	return _textHandle;
}

void
TextService::render()
{
	_vertexBuffer = new glm::vec2[10000];
	_uvBuffer = new glm::vec2[10000];

	int vertexCounter = 0;
	int uvCounter = 0;
	_textLength = 0;

	for (int j = 0; j < _textHandle->getNumberOfTextObjects(); ++j)
	{	
		if (_textHandle->isVisible(j))
		{
			int yMultiplier = 0;
			int lineCounter = 0;
			std::string text = _textHandle->getText(j);
			_textLength += text.size();

			int x = _textHandle->getX(j);
			int y = _textHandle->getY(j);

			for (int i = 0; i < text.size(); ++i)
			{
				if (text[i] == '\n')
				{
					i++;
					yMultiplier++;
					lineCounter = 0;
				}
					

				glm::vec2 vertex_up_left    = glm::vec2( x+lineCounter*_size, y + (yMultiplier + 1)*_size );
				glm::vec2 vertex_up_right   = glm::vec2( x+lineCounter*_size+_size, y + (yMultiplier + 1)*_size);
				glm::vec2 vertex_down_right = glm::vec2( x+lineCounter*_size+_size, y + (yMultiplier)*_size);
				glm::vec2 vertex_down_left  = glm::vec2( x+lineCounter*_size, y + (yMultiplier)*_size);

				_vertexBuffer[vertexCounter] = vertex_up_left;
				vertexCounter++;
				_vertexBuffer[vertexCounter] = vertex_down_left;
				vertexCounter++;
				_vertexBuffer[vertexCounter] = vertex_up_right;
				vertexCounter++;
				_vertexBuffer[vertexCounter] = vertex_down_right;
				vertexCounter++;
				_vertexBuffer[vertexCounter] = vertex_up_right;
				vertexCounter++;
				_vertexBuffer[vertexCounter] = vertex_down_left;
				vertexCounter++;

				char character = text[i];
				float uv_x = (character%16)/16.0f;
				float uv_y = (character/16)/16.0f;

				glm::vec2 uv_up_left    = glm::vec2( uv_x, 1.0f - uv_y );
				glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, 1.0f - uv_y );
				glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, 1.0f - (uv_y + 1.0f/16.0f) );
				glm::vec2 uv_down_left  = glm::vec2( uv_x, 1.0f - (uv_y + 1.0f/16.0f) );


				_uvBuffer[uvCounter] = uv_up_left;
				uvCounter++;
				_uvBuffer[uvCounter] = uv_down_left;
				uvCounter++;
				_uvBuffer[uvCounter] = uv_up_right;
				uvCounter++;
				_uvBuffer[uvCounter] = uv_down_right;
				uvCounter++;
				_uvBuffer[uvCounter] = uv_up_right;
				uvCounter++;
				_uvBuffer[uvCounter] = uv_down_left;
				uvCounter++;

				lineCounter++;
			}
		}
		
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, _textLength * 6 * sizeof(glm::vec2), _vertexBuffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBufferID);
	glBufferData(GL_ARRAY_BUFFER, _textLength * 6 * sizeof(glm::vec2), _uvBuffer, GL_STATIC_DRAW);

	glUseProgram(_shaderID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glUniform1i(_textureUniformID, 0);


	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, _textLength * 6);

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	delete _uvBuffer;
	delete _vertexBuffer;


}


void
TextService::changeText(std::string text)
{
	
	
}

void
TextService::update()
{

}
