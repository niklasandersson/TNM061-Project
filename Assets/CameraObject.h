#ifndef CAMERAOBJECT_H
#define CAMERAOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CameraObject
{

	public:
		CameraObject(float fov, float ratio, float rangeFrom, float rangeTo, 
								glm::vec3 position, glm::vec3 lookAt, glm::vec3 orientation);

		void setProjectionMatrix(glm::mat4 projection);
		void setViewMatrix(glm::mat4 view);
		void addToPosition(glm::vec3 position);
		void subtractFromPosition(glm::vec3 position);
		void setPosition(glm::vec3 position);
		void setYPosition(float yPos);
		void setLookingAt(glm::vec3 lookingAt);
		void setOrientation(glm::vec3 orientation);
		void setFieldOfView(float fov);
		void setAspectRation(float aspectRatio);
		void setClippingRangeNear(float clippingRangeNear);
		void setClippingRangeFar(float clippingRangeFar);
		void setMovmentSpeed(float movmentSpeed);
		void setLookingSpeed(float lookingSpeed);

		glm::vec3& getPosition();
		glm::vec3& getLookingAt();
		glm::vec3& getOrientation();
		float& getFieldOfView();
		float& getAspectRatio();
		float& getClippingRangeNear();
		float& getClippingRangeFar();
		float& getMovmentSpeed();
		float& getLookingSpeed();

		glm::mat4& getProjectionMatrix();
		glm::mat4& getViewMatrix();
		glm::mat4* getViewMatrixPointer();


	private:
		glm::mat4 _projection;
		glm::mat4 _view;

		glm::vec3 _position;
		glm::vec3 _lookingAt;
		glm::vec3 _orientation;

		float _fov;
		float _aspectRatio;
		float _clippingRangeNear;
		float _clippingRangeFar;

		float _movmentSpeed;
		float _lookingSpeed;
};

#endif