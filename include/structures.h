#pragma once

#include <array>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>

using token = uint64_t;

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
  /// kDop item
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

// class Token
// {
// public:
//   static const int MaxLength     = 12;
//   static const int CharsetLength = 38;
//   bool IsValidToken(std::string str){
//     if(str.length() > MaxLength) return false;
//     for (auto c : str) {
//       bool check = false;
//       for (int i = 0; i < CharsetLength; ++i) {
//         if (c == CharacterSet[i]) {
//           check = true;
//           break;
//         }
//       }
//       if (check == false) return false;
//     }
//     return true;
//   }
//   int GetCharIndex(char letter){
//     int index = -1;
//     for(int i = 0; i < CharsetLength; ++i){
//       if(letter == CharacterSet[i]){
//         index = i;
//         break;
//       }
//     }
//     return index;
//   }
//   uint64_t StringToToken(std::string input){
//     if(input.empty()) return 0;
//     if (!IsValidToken(input))
//                 throw ("Input is not a valid token.");
//     for(auto c:input){
//       std::tolower(c);
//     }
//     uint64_t token;
//     for(int i = 0; i < input.length(); ++i){
//       token += (uint64_t)std::pow(CharsetLength, i) * (uint64_t)GetCharIndex(input[i]);
//     }
//     return token;
//   }
//   Token(uint64_t token) { Value = token; }
//   Token(std::string str) { Value = StringToToken(str); }
// private:
//   uint64_t Value;
//   char     CharacterSet[38] = { '\0', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b',
//                             'c',  'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
//                             'p',  'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_' };
// };

/**
 * @brief https://github.com/sk-zk/map-docs/wiki/Bus-Stop
 * 
 */
struct BusStop{
  /// kDop item
  ItemTypeID item_type;
  /// The city this is a bus stop for, as defined in /def/city.sii. The map must contain a City item with the same token,
  /// or the game will log the error "Failed to find city for bus stop".
  token city_name;
  /// The UID of the prefab this item is linked to.
  uint64_t prefab_uid;
  /// The UID of the node of this item.
  uint64_t node_uid;
};
/**
 * @brief https://github.com/sk-zk/map-docs/wiki/City
 * 
 */
struct City{
  /// kDop item
  ItemTypeID item_type;
  /// Unit name of the city, as defined in /def/city.sii.
  token city;
  /// Width and height of the area.
  float width;
  float height;
  /// The UID of the node of this item.
  uint64_t node_uid;
};
/**
 * @brief https://github.com/sk-zk/map-docs/wiki/Company
 * 
 */
struct Company{
  /// kDop item
  ItemTypeID item_type;
  /// Name of the company.
  token company_name;
  /// The city this company is in, as defined in /def/city.sii.
  /// If the company is not inside a City item, the game will complain about it: "Company at position x;y;z is not inside city area".
  token city_name;
  /// The UID of the prefab this item is linked to.
  uint64_t prefab_uid;
  /// The UID of the main node of this item.
  /// This node is linked to the CompanyPoint spawn point type of the prefab model.
  uint64_t node_uid;
  /// Repeated six times, with UIDs of nodes which represent the following spawn point types:
  /// UnloadEasy
  /// UnloadMedium
  /// UnloadHard
  /// Trailer
  /// (unknown)
  /// LongTrailer
  uint32_t node_count;
  std::vector<uint64_t> node_uids;
};
/**
 * @brief https://github.com/sk-zk/map-docs/wiki/Cut-Plane
 * 
 */
struct CutPlane{
  /// kDop item
  ItemTypeID item_type;
  /// UIDs of nodes of this item.
  /// The path of the item is determined only by the order of nodes in this list.
  uint32_t node_count;
  std::vector<uint64_t> node_uids;
};

/**
 * @brief https://github.com/sk-zk/map-docs/wiki/Ferry
 * 
 */
struct Ferry{
  /// kDop item
  ItemTypeID item_type;
  /// Unit name of the ferry port, as defined in /def/ferry.
  token ferry_name;
  /// UID of the prefab this ferry is linked to.
  /// As far as I understand it, the editor links a prefab when the ferry item is inside the prefab and the prefab has the ferry entrance flag enabled.
  uint64_t prefab_link_uid;
  /// UID of the node of this item.
  uint64_t node_uid;
  /// Modifies where the player spawns when arriving here, I guess?
  float unload_offset;
};
/**
 * @brief https://github.com/sk-zk/map-docs/wiki/Garage
 * 
 */
struct Garage{
  /// kDop item
  ItemTypeID item_type;
  /// The city this is a garage for, as defined in /def/city.sii.
  /// The map must contain a City item with the same token, or the game will log the error "Failed to find city for garage".
  token city_name;
  /// Determines if the point is the buy point of the garage (1) or not (0).
  uint32_t buy_mode;
  /// UID of the node of this item.
  uint64_t node_uid;
  /// The UID of the prefab this item is linked to.
  uint64_t prefab_uid;
  /// Probably UIDs of nodes of trailer spawn points.
  uint32_t node_count;
  std::vector<uint64_t> node_uids;
};
/**
 * @brief https://github.com/sk-zk/map-docs/wiki/Map-Area
 * 
 */
struct MapArea{
  /// kDop item
  ItemTypeID item_type;
  /// UIDs of the nodes of the polygon.
  uint32_t node_count;
  std::vector<uint64_t> node_uids;
  /// Color of highlighted area in GPS navigation and map.
  /// 0 - Road; 1 - Light; 2 - Dark; 3 - Green.
  uint32_t color;
};
/**
 * @brief https://github.com/sk-zk/map-docs/wiki/Map-Overlay
 * 
 */
struct MapOverlay{
  /// kDop item
  ItemTypeID item_type;
  /// The road name image / city name to use.
  token look_name;
  /// UID of the node of this item.
  uint64_t node_uid;
};
/**
 * @brief https://github.com/sk-zk/map-docs/wiki/Vegetation-Struct
 * 
 */
struct Vegetation{
  /// Unit name of the vegetation type.
  token vegetation;
  /// Density of the vegetation, multiplied by 10.
  uint16_t density;
  /// Cutoff point for high poly models, multiplied by 10.
  uint8_t hi_poly_distance;
  /// Scale of vegetation models.
  /// 0 = 80% to 120%; 1 = 60% to 100%; 2 = 50% to 80%; 3 = 100% to 140%.
  uint8_t scale_type;
  /// Where vegetation starts and stops being placed, multiplied by 10.
  uint16_t start;
  uint16_t end;
};
/**
 * @brief https://github.com/sk-zk/map-docs/wiki/Vegetation-Sphere-Struct
 * 
 */
struct VegetationSphere{
  /// The position of the sphere.
  /// X is the position along the road in percent (so 0.75 means 3/4 of the way towards the forward node).
  /// Y describes the Y position of the sphere in meters relative to the terrain height at the sphere's X/Z coordinates (so 1 means 1 meter above ground).
  /// Z describes the position on the axis perpendicular to the road in meters (so 20 means 20 meters into the terrain at X).
  float center;
  /// The radius of the sphere.
  float radius;
  /// The vegetation modifier to apply inside the sphere.
  /// 1 = No vegetation; 2 = Low poly vegetation; 3 = High poly vegetation.
  uint32_t type;
};

/**
 * @brief https://github.com/sk-zk/map-docs/wiki/Prefab-Node-Struct
 * 
 */
struct PrefabNode{
  /// Terrain size, multiplied by 10.
  uint16_t terrain_sizes;
  ///  Detail Vegetation From and To values, multiplied by 10.
  uint16_t detail_veg_distance_min;
  uint16_t detail_veg_distance;
  /// Two Vegetation structs ?
  Vegetation str1; // ?
  Vegetation str2; // ?
};




struct Prefab{
  struct Base{
  /// kDop item
  ItemTypeID item_type;
  /// The unit name of the prefab.
  token prefab_model;
  /// The model variant.
  token prefab_variant;
  /// A list of enabled additional parts.
  uint32_t add_parts_count;
  std::vector<token> add_parts;
  /// The UIDs of the nodes of this prefab.
  /// It's important that the amount, position and rotation of nodes in the map matches the nodes of the prefab model.
  /// The origin node is always node 0 in this list, no matter which one it is, and you go around clockwise after that (I think).
  uint32_t node_count;
  std::vector<uint64_t> node_uids;
  /// Item UIDs of slave items of this prefab. These items are tied to certain spawnpoint types of the prefab model, such as trailer unload points and garage buy points.
  /// Slave item types in the game are: Bus Stop, Company, Fuel Pump, Garage, and Service. Again, it is important that the position of these items in the map matches the prefab model.
  uint32_t slave_count;
  std::vector<uint64_t> slave_uids;
  /// Links to a Ferry item if the prefab is a ferry.  
  uint64_t ferry_link_uid;
  /// Defines which node is the origin (=red) node.
  /// This number is an index for the ppd file, not the node list above.
  int16_t origin_idx;
  /// Repeated for each node:
  /// token ter_profile
  /// float ter_profile_coef
  /// Terrain profile and coefficient for the terrain assigned to this node.
  // >>>  array_struct node_infos // ??

  /// Semaphore profile for this prefab.
  token semaphore_profile;
  };
  struct Data{
    /// The model look.
    token prefab_look;
    /// Repeated 6 times, regardless of how many nodes or corners the prefab has.
    std::vector<PrefabNode> node_infos;
    /// List of vegetation parts. 
    uint32_t vegetation_part_count;
    std::vector<Vegetation> vegetation_parts;
    /// The seed used for placing vegetation.
    uint32_t rnd_seed;
    /// See Vegetation sphere struct.
    uint32_t veg_sphere_count;
    std::vector<VegetationSphere> veg_spheres;
    /// The seed used for placing vegetation.
    uint32_t rnd_seed;
    ///Corner models:
    /// token corner_model
    /// token corner_variant
    /// token corner_look
    /// Repeated 6 times, regardless of how many nodes or corners the prefab has.
    // array_struct corners ???

    /// Terrain data. See Quad info struct.
    /// Repeated 6 times, regardless of how many nodes or corners the prefab has.
    // array_struct quads 
    // ToDo add from  https://github.com/sk-zk/map-docs/wiki/Quad-Info-Struct
  };
};