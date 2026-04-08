#pragma once

#include <mc_rbdyn/RobotModule.h>
#include <mc_rbdyn/RobotModuleMacros.h>
#include <mc_robots/api.h>

namespace mc_robots
{

struct MC_ROBOTS_DLLAPI Revo2RobotModule : public mc_rbdyn::RobotModule
{
  Revo2RobotModule(const std::string & variant = "left_hand");
};

} // namespace mc_robots
