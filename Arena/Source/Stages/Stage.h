#ifndef STAGES_STAGE_H
#define STAGES_STAGE_H

#include "Graphics\Renderer.h"
#include "Stages\Stage_Handler.h"

class Stage : public Renderer
{
public:
	const Stages::Type type;

	virtual void Dispose() = 0;

protected:
	Stage(const Stages::Type &_type);
	virtual ~Stage();

private:
	Stage(const Stage &_other);
	Stage & operator=(const Stage &_other);
};
#endif