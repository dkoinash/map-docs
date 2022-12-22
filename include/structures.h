#pragma once

#include <cstdint>

enum class ItemTypeID : uint8_t
{
  TERRAIN         = 0x01,
  BUILDING        = 0x02,
  ROAD            = 0x03,
  PREFAB          = 0x04,
  MODEL           = 0x05,
  COMPANY         = 0x06,
  SERVICE         = 0x07,
  CUT_PLANE       = 0x08,
  MOVER           = 0x09,
  NO_WEATHER_AREA = 0x0B,
  CITY            = 0x0C,
  HINGE           = 0x0D,
  ANIMATED_MODEL  = 0x0F,
  MAP_OVERLAY     = 0x12,
  FERRY           = 0x13,
  SOUND           = 0x15,
  GARAGE          = 0x16,
  CAMERA_POINT    = 0x17,
  WALKER          = 0x1C,
  TRIGGER         = 0x22,
  FUEL_PUMP       = 0x23,
  SIGN            = 0x24,
  BUS_STOP        = 0x25,
  TRAFFIC_AREA    = 0x26,
  BEZIER_PATCH    = 0x27,
  COMPOUND        = 0x28,
  TRAJECTORY      = 0x29,
  MAP_AREA        = 0x2A,
  FAR_MODEL       = 0x2B,
  CURVE           = 0x2C,
  CAMERA_PATH     = 0x2D,
  CUTSCENE        = 0x2E,
  HOOKUP          = 0x2F,
  VISIBILITY_AREA = 0x30
};