#pragma once

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
    explicit AIControlStrategy(const Ball& ball);
	void updateDirection(Paddle& paddle) override;

private:
    const Ball& m_ball;
};
