#ifndef statsgenerator_config_h
#define statsgenerator_config_h
namespace statsgenerator
{
#ifdef BUILDING_STATS_GENERATOR
#define LIB_STATS_GENERATOR _declspec(dllexport)
#else
#define LIB_STATS_GENERATOR _declspec(dllimport)
#endif // BUILDING_STATS_GENERATOR
}
#endif // !statsgenerator_config_h