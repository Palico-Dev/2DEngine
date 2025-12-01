#pragma once

#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include "Component.h"

class Renderable: public Component
{
protected:
	int layer = -1;
	Renderable();
	virtual ~Renderable();

	virtual void Render() = 0;

private:
	friend class RenderSystem;
};

#endif	// _RENDERABLE_H_
