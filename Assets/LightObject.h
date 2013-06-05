#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class LightObject
{
	public:
		LightObject(int maxNumberOfLights);
		~LightObject();

		bool addDirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity);
		bool addPointLight(glm::vec3 direction, glm::vec3 color, float intensity, float radius);
		bool addSpotlight();

		void setMaxNumberOfLights(int maxNumberOfLights);
		int getNumberOfLights();
		int getMaxNumberOfLights();

		glm::vec3* getColors();
		glm::vec3* getPositions();
		float* getIntensities();
		float* getRadii();
		int* getLightTypes();

	private:
		int _maxNumberOfLights;
		int _numberOfLights;
		glm::vec3* _lightPositions;
		glm::vec3* _lightColors;
		float* _lightIntensities;
		float* _radii;
		int* _lightTypes;

		void clearArrays();
		void initializeArrays();
};
#endif