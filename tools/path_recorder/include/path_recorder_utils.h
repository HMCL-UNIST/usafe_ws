// #pragma once
#include <vector>
#include <ros/ros.h>
#include <ros/time.h>
#include <lanelet2_core/primitives/Lanelet.h>
#include <lanelet2_core/LaneletMap.h>
#include <lanelet2_io/Io.h>
#include <lanelet2_io/io_handlers/Factory.h>
#include <lanelet2_io/io_handlers/Writer.h>
#include <lanelet2_projection/UTM.h>
#include <lanelet2_routing/Route.h>
#include <lanelet2_routing/RoutingCost.h>
#include <lanelet2_routing/RoutingGraph.h>
#include <lanelet2_routing/RoutingGraphContainer.h>
#include <lanelet2_traffic_rules/TrafficRulesFactory.h>
#include <lanelet2_core/primitives/BasicRegulatoryElements.h>


int ctl_count=100000;

void insertMarkerArray(visualization_msgs::MarkerArray* a1, const visualization_msgs::MarkerArray& a2)
{
  a1->markers.insert(a1->markers.end(), a2.markers.begin(), a2.markers.end());
}


void setColor(std_msgs::ColorRGBA* cl, double r, double g, double b, double a)
{
  cl->r = r;
  cl->g = g;
  cl->b = b;
  cl->a = a;
}

lanelet::ConstLanelets laneletLayerConst(lanelet::LaneletMapPtr ll_map)
{
  lanelet::ConstLanelets lanelets;  

  for (auto li = ll_map->laneletLayer.begin(); li != ll_map->laneletLayer.end(); li++)
  {
    lanelets.push_back(*li);
  }

  return lanelets;
}


lanelet::Lanelets laneletLayer(lanelet::LaneletMapPtr ll_map)
{
  lanelet::Lanelets lanelets;  

  for (auto li = ll_map->laneletLayer.begin(); li != ll_map->laneletLayer.end(); li++)
  {
    lanelets.push_back(*li);
  }

  return lanelets;
}

lanelet::Lanelets subtypeLanelets(lanelet::Lanelets lls, const char subtype[])
{
  lanelet::Lanelets subtype_lanelets;

  for (auto li = lls.begin(); li != lls.end(); li++)
  {
    lanelet::Lanelet ll = *li;

    if (ll.hasAttribute(lanelet::AttributeName::Subtype))
    {
      lanelet::Attribute attr = ll.attribute(lanelet::AttributeName::Subtype);
      if (attr.value() == subtype)
      {
        subtype_lanelets.push_back(ll);
      }
    }
  }

  return subtype_lanelets;
}

lanelet::ConstLanelets subtypeLanelets(lanelet::ConstLanelets lls, const char subtype[])
{
  lanelet::ConstLanelets subtype_lanelets;

  for (auto li = lls.begin(); li != lls.end(); li++)
  {
    lanelet::ConstLanelet ll = *li;

    if (ll.hasAttribute(lanelet::AttributeName::Subtype))
    {
      lanelet::Attribute attr = ll.attribute(lanelet::AttributeName::Subtype);
      if (attr.value() == subtype)
      {
        subtype_lanelets.push_back(ll);
      }
    }
  }

  return subtype_lanelets;
}

// lanelet::Lanelets crosswalkLanelets(const lanelet::Lanelets lls)
// {
//   return (subtypeLanelets(lls, lanelet::AttributeValueString::Crosswalk));
// }

lanelet::Lanelets roadLanelets(lanelet::Lanelets lls)
{
  return (subtypeLanelets(lls, lanelet::AttributeValueString::Road));
}

lanelet::ConstLanelets roadLaneletsConst(lanelet::ConstLanelets lls)
{
  return (subtypeLanelets(lls, lanelet::AttributeValueString::Road));
}




std::vector<std::shared_ptr<const lanelet::TrafficLight>> get_trafficLights(lanelet::Lanelets lanelets)
{ 
  std::vector<std::shared_ptr<const lanelet::TrafficLight>> tl_reg_elems;

  for (auto i = lanelets.begin(); i != lanelets.end(); i++)
  {
    lanelet::ConstLanelet ll = *i;
    std::vector<std::shared_ptr<const lanelet::TrafficLight>> ll_tl_re = ll.regulatoryElementsAs<lanelet::TrafficLight>();

    // insert unique tl into array
    for (auto tli = ll_tl_re.begin(); tli != ll_tl_re.end(); tli++)
    {
      std::shared_ptr<const lanelet::TrafficLight> tl_ptr = *tli;
      lanelet::Id id = tl_ptr->id();
      bool unique_id = true;
      for (auto ii = tl_reg_elems.begin(); ii != tl_reg_elems.end(); ii++)
      {
        if (id == (*ii)->id())
        {
          unique_id = false;
          break;
        }
      }
      if (unique_id)
      {
        tl_reg_elems.push_back(tl_ptr);
      }
    }
  }
  return tl_reg_elems;
}

void toGeomMsgPt(const geometry_msgs::Point32& src, geometry_msgs::Point* dst)
{
  if (dst == nullptr)
  {
    ROS_ERROR_STREAM(__FUNCTION__ << "pointer is null!");
    return;
  }
  dst->x = src.x;
  dst->y = src.y;
  dst->z = src.z;
}
void toGeomMsgPt(const Eigen::Vector3d& src, geometry_msgs::Point* dst)
{
  if (dst == nullptr)
  {
    ROS_ERROR_STREAM(__FUNCTION__ << "pointer is null!");
    return;
  }
  dst->x = src.x();
  dst->y = src.y();
  dst->z = src.z();
}
void toGeomMsgPt(const lanelet::ConstPoint3d& src, geometry_msgs::Point* dst)
{
  if (dst == nullptr)
  {
    ROS_ERROR_STREAM(__FUNCTION__ << "pointer is null!");
    return;
  }
  dst->x = src.x();
  dst->y = src.y();
  dst->z = src.z();
}
void toGeomMsgPt(const lanelet::ConstPoint2d& src, geometry_msgs::Point* dst)
{
  if (dst == nullptr)
  {
    ROS_ERROR_STREAM(__FUNCTION__ << "pointer is null!");
    return;
  }
  dst->x = src.x();
  dst->y = src.y();
  dst->z = 0;
}

geometry_msgs::Point toGeomMsgPt(const geometry_msgs::Point32& src)
{
  geometry_msgs::Point dst;
  toGeomMsgPt(src, &dst);
  return dst;
}
geometry_msgs::Point toGeomMsgPt(const Eigen::Vector3d& src)
{
  geometry_msgs::Point dst;
  toGeomMsgPt(src, &dst);
  return dst;
}
geometry_msgs::Point toGeomMsgPt(const lanelet::ConstPoint3d& src)
{
  geometry_msgs::Point dst;
  toGeomMsgPt(src, &dst);
  return dst;
}
geometry_msgs::Point toGeomMsgPt(const lanelet::ConstPoint2d& src)
{
  geometry_msgs::Point dst;
  toGeomMsgPt(src, &dst);
  return dst;
}



void lineString2Marker(lanelet::LineString3d ls, visualization_msgs::Marker* line_strip,
                                      const std::string frame_id, const std::string ns, const std_msgs::ColorRGBA c,
                                      const float lss, bool is_center_line)
{
  if (line_strip == nullptr)
  {
    ROS_ERROR_STREAM(__FUNCTION__ << ": line_strip is null pointer!");
    return;
  }
  line_strip->header.frame_id = frame_id;
  line_strip->color = c;
  line_strip->header.stamp = ros::Time();
  line_strip->ns = ns;
  line_strip->action = visualization_msgs::Marker::ADD;
  ctl_count++;
  line_strip->pose.orientation.w = 1.0;
  line_strip->id = ctl_count+300000;
  line_strip->type = visualization_msgs::Marker::LINE_STRIP;
  line_strip->scale.x = lss;
  // fill out lane line
  for (auto i = ls.begin(); i != ls.end(); i++)
  {
    geometry_msgs::Point p;
    p.x = (*i).x();
    p.y = (*i).y();
    p.z = (*i).z();
    line_strip->points.push_back(p);
  }
}



