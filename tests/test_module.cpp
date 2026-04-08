#include <mc_rbdyn/RobotLoader.h>

int main(int argc, char * argv[])
{
  if(argc < 2)
  {
    mc_rtc::log::critical("Usage: {} [MODULE_DIR]", argv[0]);
    return 1;
  }
  mc_rbdyn::RobotLoader::clear();
  mc_rbdyn::RobotLoader::update_robot_module_path({argv[1]});

  auto left = mc_rbdyn::RobotLoader::get_robot_module("Revo2_LeftHand");
  auto right = mc_rbdyn::RobotLoader::get_robot_module("Revo2_RightHand");

  if(!left || !right)
  {
    mc_rtc::log::error("Failed to load Revo2 robot modules");
    return 1;
  }

  mc_rtc::log::info("Revo2_LeftHand has {} dof", left->mb.nrDof());
  mc_rtc::log::info("Revo2_RightHand has {} dof", right->mb.nrDof());
  return 0;
}
