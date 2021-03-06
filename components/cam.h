#ifndef CAM_H
#define CAM_H

#include "entity.h"
#include "matrix.h"
#include "types.h"

/* Cam is a struct that represents a viewport to be rendered to. */
struct Cam {
	TV_COMPONENT
	tv_Vector3 pos;
	tv_Vector3 rot;
	struct Mat4x4 proj;
	struct tv_IRect viewport;
};

struct Cam NewCam();
tv_Vector2 tv_CamSceneToScreen(struct Cam *, tv_Vector3);
bool tv_CamRaypick(struct Cam *, tv_Vector2, struct tv_Entity **);
void tv_CamSetViewport(struct Cam *, uint32_t, uint32_t, uint32_t, uint32_t);

#endif
