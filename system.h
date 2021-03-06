#ifndef SYSTEM_H
#define SYSTEM_H

#include "entity.h"
#include <stdbool.h>
#include <stdint.h>

#define TV_SYSTEM_CACHE_SIZE 32

/**
 * tv_System is a struct containing the information of a "system".
 * Systems either initialize components, update components (each frame) by
 * iterating through the global entity list, or both.
 */
struct tv_System {
	bool enabled; /* if false, system will not run. */
	unsigned id;  /* a unique identifier for this system. */
	void (*Start)(struct tv_Entity *);  /* starts components (run-once). */
	void (*Update)(struct tv_Entity *); /* updates an entity per-frame. */
	bool (*Implements)(
	    struct tv_Entity *); /* true- entity implements system. */
	void (*GlobalUpdate)();  /* run once per system per frame. */
	struct tv_Entity
	    *cache[TV_SYSTEM_CACHE_SIZE]; /* cache of recent entities. */
};

enum { TV_NUM_SYSTEMS = 1024, TV_SYSTEM_INVALID };

void tv_RegisterSystem(struct tv_System *, unsigned id);
void tv_SystemStart();
void tv_SystemUpdate();
void tv_SystemEnable(unsigned);
void tv_SystemDisable(unsigned);
bool tv_SystemEnabled(unsigned);

#endif
