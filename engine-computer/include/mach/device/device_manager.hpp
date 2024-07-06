#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "mach/labjack.hpp"
#include "mach/device/valve.hpp"
#include "mach/device/sensor.hpp"

namespace mach {

/**
 * @brief A singleton class that stores all devices in the system.
 */
class DeviceManager {
    public:
        static DeviceManager& getInstance() {
            static DeviceManager instance;
            return instance;
        }

        DeviceManager(DeviceManager const&) = delete;
        void operator=(DeviceManager const&) = delete;

        void addLabJack(std::shared_ptr<LabJack> labJack);
        void addDevice(std::shared_ptr<Valve> valve);
        void addDevice(std::shared_ptr<Sensor> sensor);
        std::shared_ptr<Valve> getValve(std::string valveName);
        std::shared_ptr<Sensor> getSensor(std::string sensorName);
        void startAllLabjackStreams();
        void printDevices();
    
    private:
        DeviceManager() {}

        std::list<std::shared_ptr<LabJack>> labJacks;
        std::unordered_map<std::string, std::shared_ptr<Valve>> valves;
        std::unordered_map<std::string, std::shared_ptr<Sensor>> sensors;
};

} // namespace mach