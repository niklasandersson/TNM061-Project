#ifndef INFOHANDLE_H
#define INFOHANDLE_H

class InfoHandle
{
	public:
		InfoHandle();

		int getWindowWidth();
		int getWindowHeight();
		bool getIsJumping();

		void setWindowWidth(int windowWidth);
		void setWindowHeight(int windowHeight);
		void setIsJumping(bool isJumping);

	private:
		int _windowWidth;
		int _windowHeight;
		bool _isJumping;
};

#endif