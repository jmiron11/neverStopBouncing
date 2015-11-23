#ifndef TIMER_H_
#define TIMER_H_


class Timer{
 public:
 	Timer();
 	~Timer();

 	float timeSinceCreated();
 	float timeSinceLastCall();


 private:
 	float m_prevTime;

};

#endif