#pragma once

#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

class IRenderable{

protected:
	IRenderable();
	virtual ~IRenderable();

	virtual void Render() = 0;

	void OnEnable();
	void OnDisable();

	void UpdateLayer();

protected:
	int layer = 0;
private:
	bool enabled = false;
	friend class RenderSystem;
};

#endif	// _RENDERABLE_H_
