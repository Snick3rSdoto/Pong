#pragma once
#include <memory>

class Ball;
class Paddle;

class ControlStrategy {
public:
	virtual void updateDirection(Paddle& paddle) = 0;

	virtual ~ControlStrategy() = default;

};



class PlayerControlStrategy : public ControlStrategy {
public:
	void updateDirection(Paddle& paddle) override;
};


class AIControlStrategy : public ControlStrategy {
public:
    explicit AIControlStrategy(std::shared_ptr<Ball> ball);
	void updateDirection(Paddle& paddle) override;

private:
	std::shared_ptr<Ball> mBall;
};
