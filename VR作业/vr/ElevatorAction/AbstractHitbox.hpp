#pragma once
class AbstractHitbox
{
public:
	AbstractHitbox(bool solid);
	~AbstractHitbox();
	bool solid;

	virtual float x1() const = 0;
	virtual float y1() const = 0;
	virtual float x2() const = 0;
	virtual float y2() const = 0;
	float left() const;
	float right() const;
	float top() const;
	float bottom() const;
	bool collides(AbstractHitbox *h);
	bool intersects(AbstractHitbox *h);
	virtual void render(float delta, float r, float g, float b);
};

