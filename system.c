#include "system.h"
#include <string.h>

static struct tv_System systems[TV_NUM_SYSTEMS];
static unsigned short numSystems;

/* tv_RegisterSystem registers sys to be updated each frame. */
void tv_RegisterSystem(struct tv_System *sys, unsigned id) {
	sys->enabled = true;
	sys->id = id;
	memcpy(&systems[numSystems], sys, sizeof(struct tv_System));
	memset(systems[numSystems].cache, 0, sizeof(sys->cache));
	numSystems++;
}

/* tv_SystemStartAll runs all registered TV_SYSTEM_START type systems. */
void tv_SystemStart() {
	unsigned i;
	for (i = 0; i < numSystems; ++i) {
		if (systems[i].enabled)
			tv_EntityStartAll(systems[i].Implements,
			                  systems[i].Start, systems[i].cache);
	}
}

/* tv_UpdateSystems updates all registered systems. */
void tv_SystemUpdate() {
	unsigned i;
	for (i = 0; i < numSystems; ++i) {
		if (systems[i].enabled && systems[i].GlobalUpdate != NULL)
			systems[i].GlobalUpdate();
	}
	for (i = 0; i < numSystems; ++i) {
		if (systems[i].enabled && systems[i].Update != NULL)
			tv_EntityUpdateAll(systems[i].Implements,
			                   systems[i].Update, systems[i].cache);
	}
}

/* tv_SystemEnable enables the system of the given ID. */
void tv_SystemEnable(unsigned id) {
	unsigned i;
	for (i = 0; i < numSystems; ++i) {
		if (id == systems[i].id) {
			systems[i].enabled = true;
		}
	}
}

/* tv_SystemEnable disables the system of the given ID. */
void tv_SystemDisable(unsigned id) {
	unsigned i;
	for (i = 0; i < numSystems; ++i) {
		if (id == systems[i].id) {
			systems[i].enabled = false;
		}
	}
}

/* tv_SystemEnabled returns true if the system known by id is enabled. */
bool tv_SystemEnabled(unsigned id) {
	unsigned i;
	for (i = 0; i < numSystems; ++i) {
		if (id == systems[i].id) {
			return systems[i].enabled;
		}
	}

	return false;
}
