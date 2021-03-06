#include "sys_gui.h"
#include "components/enum.h"
#include "components/gui.h"
#include "draw.h"
#include "gui.h"
#include "systems.h"
#include <system.h>

bool implements(struct tv_Entity *e) {
	if (tv_EntityGetComponent(e, COMPONENT_TRANSFORM) == NULL)
		return false;

	/* TODO: implement simple inheritance or || all GUI types? */
	return tv_EntityGetComponent(e, COMPONENT_GUITEXT) != NULL;
}

void update(struct tv_Entity *e) {
	struct GUIText *g;
	struct Transform *t;
	t = (struct Transform *)tv_EntityGetComponent(e, COMPONENT_TRANSFORM);
	g = (struct GUIText *)tv_EntityGetComponent(e, COMPONENT_GUITEXT);
	tv_GuiText(t->pos.x, t->pos.y, g->text, g->size);
}

/* sys_GUIInit initializes the GUI system for use by the engine. */
void InitGUISystem() {
	struct tv_System sys = {
	    .enabled = true,
	    .Start = NULL,
	    .Update = update,
	    .Implements = implements,
	    .GlobalUpdate = NULL,
	};
	tv_RegisterSystem(&sys, SYSTEM_GUI);
}
