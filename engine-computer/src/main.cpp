#include <iostream>
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>
#include "mach/labjack.hpp"
#include "mach/config_parser.hpp"
#include "mach/device_manager.hpp"
#include "mach/sequences/action_factory.hpp"
#include "mach/sequences/open_action.hpp"
#include "mach/device/device.hpp"
#include "mach/sequences/sleep_action.hpp"
#include "mach/sequences/close_action.hpp"

#define LABJACK_CONFIG std::string("../../config/labjack.yml")
#define REMOTE_CONFIG std::string("../../config/remote.yml")

int main() {
    spdlog::info("MACH: Hello World!");

    // One LabJack for now.
    mach::LabJack labJack("LabJack");

    // Read configuration 🤓
    mach::parseLabjackConfig(labJack, LABJACK_CONFIG);
    mach::parseRemoteConfig(REMOTE_CONFIG);

    // Print all devices for debug.
    mach::DeviceManager& deviceManager = mach::DeviceManager::getInstance();
    deviceManager.printDevices();

    // Register sequence actions.
    mach::ActionFactory& actionFactory = mach::ActionFactory::getInstance();
    actionFactory.registerAction("OPEN", []() { return std::make_unique<mach::OpenAction>(); });
    actionFactory.registerAction("CLOSE", []() { return std::make_unique<mach::CloseAction>(); });
    actionFactory.registerAction("SLEEP", []() { return std::make_unique<mach::SleepAction>(); });
}