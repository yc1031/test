// #include <ros/ros.h>
#include <map>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;



namespace LPP{
typedef struct {
    float x;
    float y;
    float yaw;
    int waypointID;
} stGlobalPath;

typedef struct {
    int id;
    int turn_back;
} stWaypointList;

typedef struct {
    float x;
    float y;
    int id;
} stWwaypointObstractRelation;

typedef struct {
    int WaypointID;
    float PalletFrontX;
    float PalletFrontY;
    float PalletFrontTheta;
} stStationMaster;


typedef struct {
    int id;
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    float x4;
    float y4;            
} stStaticObst;


class AnyBase
{
    public:
        virtual ~AnyBase() = 0;
};

inline AnyBase::~AnyBase(){}
template<class T>
class Any : public AnyBase
{
    public:
        typedef T Type;
        explicit Any(const Type& data) : data(data){}
        Any() {}
        Type data;
};
};
