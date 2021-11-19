
#include "return_path_planner_type.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
using namespace LPP;

std::vector<std::string> split(std::string str, char del);
std::vector<std::vector<std::string> > csv2vector(std::string filename, int ignore_line_num);

bool make_return_path(std::vector<stGlobalPath> globalPathList,
                      std::vector<stWaypointList> waypointList,
                      std::vector<stWwaypointObstractRelation> waypointObst,
                      std::vector<stStationMaster> stationMap,
                      std::vector<stStaticObst> staticObst,
                      stGlobalPath agf_pos);

void coordinate_transformation(std::vector<stGlobalPath>& globalPathList,
                                std::vector<stWaypointList>& waypointList,
                                std::vector<stWwaypointObstractRelation>& waypointObst,
                                std::vector<stStationMaster>& stationMap,
                                std::vector<stStaticObst>& staticObst,
                                stGlobalPath& agf_pos,
                                stGlobalPath& st_pos);

                                                        

void calc_confluen_point(std::vector<stGlobalPath> globalPathList,
                            std::vector<stWaypointList> waypointList,
                            std::vector<stWwaypointObstractRelation> waypointObst,
                            std::vector<stStationMaster> stationMap,
                            std::vector<stStaticObst> staticObst,
                            stGlobalPath agf_pos,
                            stGlobalPath st_pos,
                            std::vector<stGlobalPath>& confluence_points);

void calc_turning_radius(stGlobalPath agf_pos,
                         stGlobalPath st_pos,
                         stGlobalPath confluence_point,
                         float theta,
                         float& r0,
                         stGlobalPath& center_point);

void calc_return_path(std::vector<stGlobalPath> globalPathList,
                      stGlobalPath agf_pos,
                      float r0,
                      stGlobalPath center_point,
                      std::vector<stGlobalPath>& return_path);                         


void calc_return_path_relux(std::vector<stGlobalPath>& return_path,
                      std::vector<stGlobalPath>& return_path_relax);

void bezier_curve(int n, float t, std::vector<stGlobalPath> control_point, stGlobalPath& path);

float bernstein(int n, int i, float t);

int comb(int n, int r);