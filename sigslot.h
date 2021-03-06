#ifndef SIGSLOT_H
#define SIGSLOT_H

#include <stdbool.h>
#include <stdint.h>

/*
 * TV_SIGNAL_MAX_SLOTS maximum number of slots that may be connected to a
 * signal. You can easily work around this limitation by using multiple slots
 * if need be.
 */
#define TV_SIGNAL_MAX_SLOTS 31

/*
 * SIGNAL is a macro that defines a new type of signal and slot as well as the
 * necessary functions to connect and emit to/from it.
 *
 * Every signal has an emit method that signals the triggering of the signal
 * to all connected slots.
 * Here is a simple signal implementation:
 *   struct
 *   {
 *     int (*emit)(int, int)  //the emit function
 *     struct mySlot slots[]  //slots that expect an emit of this signal's form.
 *   }mySignal;
 * Slots are named by the following convention:
 * tv_SlotABC... where A, B,C, etc. are the types of the parameters to the slot.
 * the types are represented by the following lowercase characters:
 *  c- character
 *  f- float
 *  i- integer
 *  v- void
 *  p- pointer
 * It is recommended that you typedef slots and signals to more useful names
 * in each case they are used.  For example:
 * typedef tv_Slotv openDoorSlot;
 * typedef tv_Signalv openDoorSignal;
 */
#define SIGNAL(name, ...)                                                      \
	typedef void (*tv_Slot##name)(__VA_ARGS__);                            \
	struct sig_##name {                                                    \
		unsigned _numSlots;                                            \
		struct {                                                       \
			tv_Slot##name fn;                                      \
			uint32_t active;                                       \
		} slots[TV_SIGNAL_MAX_SLOTS];                                  \
		uint32_t active;                                               \
	};                                                                     \
	extern struct sig_##name name;                                         \
	void tv_Signal##name##Init(struct sig_##name *sig);                    \
	void tv_Signal##name##Emit(struct sig_##name *sig, ##__VA_ARGS__);     \
	void tv_Signal##name##Connect(struct sig_##name *sig,                  \
	                              tv_Slot##name slot);

/*
 * SIGDEF is a macro that defines a signal with the given name.
 * Every SIGNAL declaration must have a matching SIGDEF.
 */
#define SIGDEF(name, ...) struct sig_##name name;

/* CONNECT is a macro that connects sig to the given slot. */
#define CONNECT(sig, slot)                                                     \
	{                                                                      \
		if (sig._numSlots < TV_SIGNAL_MAX_SLOTS) {                     \
			sig.slots[sig._numSlots].fn = slot;                    \
			sig.slots[sig._numSlots].active |= 0x80000000;         \
			sig.active |= 0x80000000;                              \
			sig._numSlots++;                                       \
		}                                                              \
	}

/* GCONNECT connects sig to slot and sets its group to group. */
#define GCONNECT(group, sig, slot)                                             \
	{                                                                      \
		if (sig._numSlots < TV_SIGNAL_MAX_SLOTS) {                     \
			sig.slots[sig._numSlots].fn = slot;                    \
			sig.slots[sig._numSlots].active = group;               \
			sig._numSlots++;                                       \
			sig.active |= group;                                   \
		}                                                              \
	}

/* GACTIVATE activates group on signal sig. */
#define GACTIVATE(group, sig)                                                  \
	{ sig.active |= group; }

/* GDEACTIVATE deactivates group on signal sig. */
#define GDEACTIVATE(group, sig)                                                \
	{ sig.active &= ~group; }

/* EMIT is a macro that calls all slots connected to the signal name. */
#define EMIT(name, ...)                                                        \
	{                                                                      \
		unsigned i;                                                    \
		for (i = 0; i < name._numSlots; ++i) {                         \
			if ((name.slots[i].active & name.active) != 0)         \
				name.slots[i].fn(__VA_ARGS__);                 \
		}                                                              \
	}

/* tv_Signal is a struct embedded by other signals. */
struct tv_Signal {};

#endif
