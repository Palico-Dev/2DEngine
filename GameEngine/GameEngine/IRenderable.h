#pragma once

#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

class IRenderable{
protected:
	int layer = -1;
	IRenderable();
	virtual ~IRenderable();

	virtual void Render() = 0;

private:
	friend class RenderSystem;
};

#endif	// _RENDERABLE_H_
