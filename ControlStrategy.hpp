#pragma once

class Ball;

class ControlStrategy {
public:
	virtual float getDirection(float paddleCenterY) = 0;

	virtual ~ControlStrategy() = default;

};



class PlayerControlStrategy : public ControlStrategy {
public:
    float getDirection(float paddleCenterY) override;
};


class AIControlStrategy : public ControlStrategy {
public:
    explicit AIControlStrategy(const Ball& ball);
    float getDirection(float paddleCenterY) override;

private:
    const Ball& m_ball;
};
