#include "revo2.h"
#include "config.h"

#include <mc_rtc/constants.h>
#include <mc_rtc/logging.h>
#include <RBDyn/parsers/urdf.h>

namespace mc_robots
{

inline static std::string revo2Variant(const std::string & variant)
{
  std::string fullName = "revo2_" + variant;
  mc_rtc::log::info("Revo2RobotModule uses the Revo2 variant: '{}'", fullName);
  return fullName;
}

Revo2RobotModule::Revo2RobotModule(const std::string & variant)
: RobotModule(mc_rtc::REVO2_DESCRIPTION_PATH,
              revo2Variant(variant),
              std::string(mc_rtc::REVO2_DESCRIPTION_PATH) + "/urdf/" + revo2Variant(variant) + ".urdf")
{
  mc_rtc::log::success("Revo2RobotModule loaded with name: {}", name);
  //rsdf_dir = std::string(mc_rtc::REVO2_DESCRIPTION_PATH) + "/rsdf";

  mc_rtc::log::success("Revo2RobotModule using URDF \"{}\"", urdf_path);
  //mc_rtc::log::success("Revo2RobotModule using path \"{}\" for rsdf", rsdf_dir);

  // Revo2 is typically mounted to an arm/socket; expose fixed-base kinematics by default.
  bool fixed = true;
  init(rbd::parsers::from_urdf_file(urdf_path, fixed));

  const bool left = variant == "left_hand";
  const std::string side = left ? "left" : "right";

    
  _ref_joint_order = {
      side + "_thumb_metacarpal_joint", side + "_thumb_proximal_joint", side + "_thumb_distal_joint",
      side + "_index_proximal_joint",   side + "_index_distal_joint",   
      side + "_middle_proximal_joint",  side + "_middle_distal_joint",    
      side + "_ring_proximal_joint",  side + "_ring_distal_joint",
      side + "_pinky_proximal_joint",   side + "_pinky_distal_joint"};
    
  // Only 6 active joints
  /*_ref_joint_order = {
      side + "_thumb_metacarpal_joint", side + "_thumb_proximal_joint",
      side + "_index_proximal_joint",   
      side + "_middle_proximal_joint",
      side + "_ring_proximal_joint", 
      side + "_pinky_proximal_joint"};
  */
  for(const auto & joint : _ref_joint_order)
  {
    _stance[joint] = {0.0};
  }

  for(const auto & joint : _ref_joint_order)
  {
    if(mb.jointIndexByName().count(joint) != 0)
    {
      _jointSensors.emplace_back(joint);
    }
  }

  _bodySensors.emplace_back("FloatingBase", side + "_base_link", sva::PTransformd::Identity());
  _minimalSelfCollisions = {};
  _commonSelfCollisions = _minimalSelfCollisions;
}

} // namespace mc_robots

extern "C"
{
  ROBOT_MODULE_API void MC_RTC_ROBOT_MODULE(std::vector<std::string> & names)
  {
    names = {"Revo2", "Revo2_LeftHand", "Revo2_RightHand"};
  }

  ROBOT_MODULE_API void destroy(mc_rbdyn::RobotModule * ptr)
  {
    delete ptr;
  }

  ROBOT_MODULE_API mc_rbdyn::RobotModule * create(const std::string & n)
  {
    ROBOT_MODULE_CHECK_VERSION("Revo2")
    if(n == "Revo2" || n == "Revo2_LeftHand")
    {
      return new mc_robots::Revo2RobotModule("left_hand");
    }
    else if(n == "Revo2_RightHand")
    {
      return new mc_robots::Revo2RobotModule("right_hand");
    }
    else
    {
      mc_rtc::log::error("Revo2 module cannot create an object of type {}", n);
      return nullptr;
    }
  }
}
