#ifndef INPUTHANDLE_H
#define INPUTHANDLE_H

class InputHandle
{
	public:
		InputHandle();

		void resetKeys();
		void toggleKey(const unsigned int key);

		bool isKeyDown(const unsigned int key);
		int getState();
		void setState(int state);
		

		static const unsigned int KEY_ESC = 0, KEY_A = 1, KEY_B = 2 , KEY_C = 3, KEY_D = 4, KEY_E = 5,KEY_F = 6,KEY_G = 7,KEY_H = 8,
											 KEY_I = 9, KEY_J = 10 , KEY_K = 11, KEY_L = 12, KEY_M = 13,KEY_N = 14,KEY_O = 15,KEY_P = 16,
											 KEY_Q = 17, KEY_R = 18 , KEY_S = 19, KEY_T = 20, KEY_U = 21,KEY_V = 22,KEY_W = 23, KEY_X = 24,KEY_Y = 25,
											 KEY_Z = 26, KEY_SPACE = 27;

		void setMousePosition(int mousePositionX, int mousePositionY);
		
		void getMousePosition(int& mousePositionX, int& mousePositionY);
		private:
			static const unsigned int NUMBER_OF_KEYS = 28;
			bool keys[NUMBER_OF_KEYS];
			int _mousePositionX;
			int _mousePositionY;
			int _state;
};

#endif
