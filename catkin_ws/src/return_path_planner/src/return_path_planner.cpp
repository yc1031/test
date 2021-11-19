#include "return_path_planner.h"
// #include <fork_msg/LppCmd.h>
using namespace LPP;
using namespace std;

//文字列のsplit機能
std::vector<std::string> split(std::string str, char del) {
    int first = 0;
    int last = str.find_first_of(del);
    std::vector<std::string> result;
    while (first < str.size()) {
        std::string subStr(str, first, last - first);
        result.push_back(subStr);
        first = last + 1;
        last = str.find_first_of(del, first);
        if (last == std::string::npos) {
            last = str.size();
        }
    }
    return result;
}

std::vector<std::vector<std::string> >
csv2vector(std::string filename, int ignore_line_num){
    //csvファイルの読み込み
    std::ifstream reading_file;
    reading_file.open(filename, std::ios::in);
    if(!reading_file){
        std::vector<std::vector<std::string> > data;
        return data;
    }
    std::string reading_line_buffer;
    //最初のignore_line_num行を空読みする
    for(int line = 0; line < ignore_line_num; line++){
        getline(reading_file, reading_line_buffer);
        if(reading_file.eof()) break;
    }

    //二次元のvectorを作成
    std::vector<std::vector<std::string> > data;
    while(std::getline(reading_file, reading_line_buffer)){
        if(reading_line_buffer.size() == 0) break;
        std::vector<std::string> temp_data;
        temp_data = split(reading_line_buffer, ',');
        data.push_back(temp_data);
    }
    return data;
}

bool make_return_path(std::vector<stGlobalPath> globalPathList,
                      std::vector<stWaypointList> waypointList,
                      std::vector<stWwaypointObstractRelation> waypointObst,
                      std::vector<stStationMaster> stationMap,
                      std::vector<stStaticObst> staticObst,
                      stGlobalPath agf_pos)
{
    stGlobalPath st_pos;
    std::vector<stGlobalPath> confluence_points;
    float r0;
    stGlobalPath center_pos;
    float theta;

    std::vector<float> vec_r0;
    std::vector<stGlobalPath> vec_center_pos;
    std::vector<stGlobalPath> return_path;
    std::vector<stGlobalPath> return_path_relax;
    std::vector<std::vector<stGlobalPath>> vec_return_path_relax;

    coordinate_transformation(globalPathList, waypointList, waypointObst, stationMap, staticObst, agf_pos, st_pos);
    calc_confluen_point(globalPathList, waypointList, waypointObst, stationMap, staticObst, agf_pos, st_pos, confluence_points);
    
    theta = atan2((confluence_points[1].y-confluence_points[0].y), (confluence_points[1].x-confluence_points[0].x));
    for(int i=0, size=confluence_points.size(); i<size; i++)
    {
        calc_turning_radius(agf_pos, st_pos, confluence_points[i], theta, r0, center_pos);
        calc_return_path(globalPathList, agf_pos, r0, center_pos, return_path);
                
    }    

}


void coordinate_transformation(std::vector<stGlobalPath>& globalPathList,
                                std::vector<stWaypointList>& waypointList,
                                std::vector<stWwaypointObstractRelation>& waypointObst,
                                std::vector<stStationMaster>& stationMap,
                                std::vector<stStaticObst>& staticObst,
                                stGlobalPath& agf_pos,
                                stGlobalPath& st_pos)
{
    float dist;
    std::vector<float> vec_dist;

    for(int i=0, size=stationMap.size(); i< size; i++)
    {
        st_pos.x = stationMap[i].PalletFrontX;
        st_pos.y = stationMap[i].PalletFrontY;

        dist = sqrt(pow(st_pos.x-agf_pos.x, 2) + pow(st_pos.y - agf_pos.x, 2));
        vec_dist.push_back(dist);
    }

    std::vector<float>::iterator iter = std::min_element(vec_dist.begin(), vec_dist.end());
    size_t index = std::distance(vec_dist.begin(), iter);

    st_pos.x = stationMap[index].PalletFrontX;
    st_pos.y = stationMap[index].PalletFrontY;    
    st_pos.yaw = stationMap[index].PalletFrontTheta;

    for(int i=0, size=globalPathList.size(); i<size; i++)
    {
        globalPathList[i].x = cos(st_pos.yaw) * globalPathList[i].x - sin(st_pos.yaw) * globalPathList[i].y;
        globalPathList[i].x = sin(st_pos.yaw) * globalPathList[i].x + cos(st_pos.yaw) * globalPathList[i].y;        
    }

    for(int i=0, size=waypointObst.size(); i<size; i++)
    {
        waypointObst[i].x = cos(st_pos.yaw) * waypointObst[i].x - sin(st_pos.yaw) * waypointObst[i].y;
        waypointObst[i].x = sin(st_pos.yaw) * waypointObst[i].x + cos(st_pos.yaw) * waypointObst[i].y;        
    }

    // for(int i=0, size=waypointObst.size(); i<size; i++)
    // {
    //     waypointObst[i].x = cos(st_pos.yaw) * waypointObst[i].x - sin(st_pos.yaw) * waypointObst[i].y;
    //     waypointObst[i].x = sin(st_pos.yaw) * waypointObst[i].x + cos(st_pos.yaw) * waypointObst[i].y;        
    // }


}


void calc_confluen_point(std::vector<stGlobalPath> globalPathList,
                            std::vector<stWaypointList> waypointList,
                            std::vector<stWwaypointObstractRelation> waypointObst,
                            std::vector<stStationMaster> stationMap,
                            std::vector<stStaticObst> staticObst,
                            stGlobalPath agf_pos,
                            stGlobalPath st_pos,
                            std::vector<stGlobalPath>& confluence_points)
{
    uint16_t wp_id;
    float wp_x;
    float wp_y;
    float theta;
    float dist;
    std::vector<float> vec_dist;
    float dist_curve;
    std::vector<float> vec_dist_curve;    
    stGlobalPath conf_point;

    for(int i=0,size=waypointList.size(); i< size; i++)
    {
        wp_id = waypointList[i].id;
        auto iter = std::find_if(waypointObst.begin(), waypointObst.end(), [&](auto &c) {return (c.id==wp_id);});
        size_t index = std::distance(waypointObst.begin(),iter);
        wp_x = waypointObst[index].x;
        wp_y = waypointObst[index].y;

        theta = atan2((wp_y-st_pos.y), (wp_x-st_pos.x));

        if(theta >= (30.0/180.0) * M_PI)
        {
            conf_point.x = wp_x;
            conf_point.y = wp_y;
            break;
        }
    }

    auto iter_curve = std::find_if(waypointList.begin(), waypointList.end(), [&](auto &c) {return (c.turn_back==1);});
    size_t index_curve = std::distance(waypointList.begin(),iter_curve);

    for(int i=0, size=globalPathList.size(); i<size; i++)
    {
        dist = sqrt(pow(wp_x-globalPathList[i].x, 2) + pow(wp_y - globalPathList[i].y, 2));
        vec_dist.push_back(dist);
        dist_curve = sqrt(pow(waypointObst[index_curve].x-globalPathList[i].x, 2) + pow(waypointObst[index_curve].y - globalPathList[i].y, 2));
        vec_dist_curve.push_back(dist_curve);        
    }

    std::vector<float>::iterator iter = std::min_element(vec_dist.begin(), vec_dist.end());
    size_t index_start = std::distance(vec_dist.begin(), iter);

    std::vector<float>::iterator iter_end = std::min_element(vec_dist_curve.begin(), vec_dist_curve.end());
    size_t index_end = std::distance(vec_dist_curve.begin(), iter_end);

    int d_index = (index_end - index_start) / 3;
    
    for(int i=index_start; i<=index_end; i+=d_index)
    {
        conf_point.x = globalPathList[i].x;
        conf_point.y = globalPathList[i].y;
        confluence_points.push_back(conf_point);
    }
}


void calc_turning_radius(stGlobalPath agf_pos,
                         stGlobalPath st_pos,
                         stGlobalPath confluence_point,
                         float theta,
                         float& r0,
                         stGlobalPath& center_point)
{
    r0 = (agf_pos.y - agf_pos.x * tan(theta) - confluence_point.y + confluence_point.x * tan(theta))
         / (tan(theta)*cos(agf_pos.yaw) - tan(theta)*sin(theta) - sin(agf_pos.yaw) - cos(theta));

    center_point.x = agf_pos.x + r0 * cos(agf_pos.yaw);
    center_point.y = agf_pos.y + r0 + sin(agf_pos.yaw);

}



void calc_return_path(std::vector<stGlobalPath> globalPathList,
                      stGlobalPath agf_pos,
                      float r0,
                      stGlobalPath center_point,
                      std::vector<stGlobalPath>& return_path)
{
    float theta;
    float d_theta;
    stGlobalPath path;

    theta = agf_pos.yaw;
    d_theta = (M_PI/2 - agf_pos.yaw) / 20;
    for(int i=0; i<100; i++)
    {
        path.x = center_point.x - r0 * cos(theta);
        path.y = center_point.y - r0 * sin(theta);
        theta = theta + d_theta;
        return_path.push_back(path);
    }

    for(int i=0, size=return_path.size(); i<size; i++)
    {
        return_path[i].yaw = atan2((return_path[i+1].y - return_path[i].y),(return_path[i+1].x - return_path[i].x));
    }
}


// 二項係数nCrの計算
int comb(int n, int r)
{
    int num = n - r + 1, x = 1;

    if (n == r) 
        return 1;
    else if (n < r) 
        // std::cout << "Error : please set n >= r" << std::endl;

    for (int i = 1; i <= r; i++)
        x = x*num++ / i;

    return x;
}

// Bernstein係数
float bernstein(int n, int i, float t)
{
    int k = 0;
    float a = 1.0f, b = 1.0f;

    for (k = 0; k < i; k++)
        a *= t;

    for (k = 0; k < n-i; k++) 
        b *= 1 - t;

    return float(comb(n, i)) * a * b;
}

// Bezier curve の算出
void bezier_curve(int n, float t, std::vector<stGlobalPath> control_point, stGlobalPath& path)
{
    float x = 0.0f, y = 0.0f, B = 0.0f;

    for (int i = 0; i <= n; i++) {
        B  = bernstein(n, i, t);
        x += B * control_point[i].x;
        y += B * control_point[i].y;
    }
    path.x = x;
    path.y = y;
}



void calc_return_path_relux(std::vector<stGlobalPath>& return_path,
                      std::vector<stGlobalPath>& return_path_relax)
{
    stGlobalPath control_point;
    std::vector<stGlobalPath> control_points;
    stGlobalPath path;

    int n = control_points.size();
    int t = 100;
    for(int i=0; i<t; i++)
    {
        bezier_curve(n, i, control_points, path);
        return_path_relax.push_back(path);
    }
}

int main(int argc, char** argv)
{
    stGlobalPath path;
    stWaypointList waypoint;
    stWwaypointObstractRelation way_obst;
    std::vector<stGlobalPath> globalPathList;
    std::vector<stWaypointList> waypointList;
    std::vector<stWwaypointObstractRelation> waypointObst;
    std::vector<stStationMaster> stationMap;
    std::vector<stStaticObst> staticObst;
    stGlobalPath agf_pos;

    std::vector<std::vector<std::string> > data_gpp;
    data_gpp = csv2vector("test.csv", 0);

    for(int i=0, size=data_gpp.size(); i<size; i++)
    {
        path.waypointID = stoi(data_gpp[i][0]);
        path.x = stod(data_gpp[i][1]);
        path.y = stod(data_gpp[i][2]);
        path.yaw = stod(data_gpp[i][3]);
        globalPathList.push_back(path);
    }




    // bool flag = make_return_path(globalPathList, waypointList, waypointObst, stationMap, staticObst, agf_pos);

//   ros::init(argc, argv, "lpp_return");
//   ros::NodeHandle nh;
//   ros::NodeHandle pn("~");
//   ros::Publisher local_path = nh.advertise<fork_msg::LppCmd>("test", 10);
//   ros::Rate loop_rate(10);

//   while (ros::ok())
//   {
//     fork_msg::LppCmd msg;
//     msg.x = 10.0;
//     ROS_INFO("publish: %s", msg.x);
//     local_path.publish(msg);

//     ros::spinOnce();
//     loop_rate.sleep();
//   }
  return 0;
}