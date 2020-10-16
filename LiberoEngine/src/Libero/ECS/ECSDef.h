#pragma once
#include "../Misc/Handle.h"
#include <limits>

#ifdef max
#undef max
#endif

// TypeID:
typedef unsigned int TypeID;
static const TypeID gTypeID_Invalid = std::numeric_limits<TypeID>::max();

// EntityID:
typedef TypeID ETypeID;
typedef Handle64 EntityID;
static const EntityID gEntityID_Invalid = Handle64::INVALID;

// ComponentID:
typedef TypeID CTypeID;
typedef Handle64 CompID;
static const CTypeID gComponentID_Invalid = gTypeID_Invalid;

// SystemID:
typedef TypeID SysTypeID;
static const SysTypeID gSystemID_Invalid = gTypeID_Invalid;

// Memory:
#define LBR_ENTITY_T_CHUNK_SIZE 1024
#define LBR_COMPONENT_T_CHUNK_SIZE 1024

#define LBR_COMPONENT_LUTGROW 1024
#define LBR_ENTITY_LUTGROW 1024

#define LBR_SYSTEM_MEMORY_SIZE 8388608 / 2