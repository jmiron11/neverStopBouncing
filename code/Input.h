#ifndef INPUT_H_
#define INPUT_H_

const int NUM_KEYS = 323;

class Input{
public:
	Input();
	~Input();

	void getInput();
	bool * getKeysPressed();
	bool quitPressed();


private:
	bool m_keysPressed[NUM_KEYS];
	bool m_quitPressed;
};

#endif