#pragma once

class Ball;

class ControlStrategy {
public:
	// Returns the Y direction: -1 (up), 0 (stand), 1 (down)
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
