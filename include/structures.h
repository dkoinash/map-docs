#pragma once

#include <array>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <string>

/**
 * @brief https://github.com/sk-zk/map-docs/wiki/Item-type-IDs
 *
 */
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
/**
 * @brief https://github.com/sk-zk/map-docs/wiki/kDOP-bounding-box
 *
 */
struct KDOP
{
  std::array<float, 5> minimums;
  std::array<float, 5> maximums;
};
/**
 * @brief https://github.com/sk-zk/map-docs/wiki/kDOP-item
 *
 */
struct KDOP_ITEM
{
  ItemTypeID item_type;
  /// The UID of the item.
  uint64_t uid;
  /// kDOP bounding box
  KDOP kdop;
  /// Despite the semantics, this is the main flag field for every item type, with each using
  /// different, item-specific flags.
  uint32_t flags;
  /// View distance of the item in meters, divided by 10. Default is 400m. The maximum the game will
  /// let you use is 1500m.
  uint8_t view_list;
};


class Token
{
public:
  static const int MaxLength     = 12;
  static const int CharsetLength = 38;

  bool IsValidToken(std::string str){
    if(str.length() > MaxLength) return false;
    for (auto c : str) {
      bool check = false;
      for (int i = 0; i < CharsetLength; ++i) {
        if (c == CharacterSet[i]) {
          check = true;
          break;
        }
      }
      if (check == false) return false;
    }
    return true;
  }
  
  int GetCharIndex(char letter){
    int index = -1;
    for(int i = 0; i < CharsetLength; ++i){
      if(letter == CharacterSet[i]){
        index = i;
        break;
      }
    }
    return index;
  }

  uint64_t StringToToken(std::string input){
    if(input.empty()) return 0;
    if (!IsValidToken(input))
                throw ("Input is not a valid token.");
    for(auto c:input){
      std::tolower(c);
    }
    uint64_t token;
    for(int i = 0; i < input.length(); ++i){
      token += (uint64_t)std::pow(CharsetLength, i) * (uint64_t)GetCharIndex(input[i]);
    }
    return token;
  }

  Token(uint64_t token) { Value = token; }
  
  Token(std::string str) { Value = StringToToken(str); }

private:
  uint64_t Value;
  char     CharacterSet[38] = { '\0', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b',
                            'c',  'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                            'p',  'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_' };
};
