#include <iostream>
#include <vector>

#include "avk/avk.hpp"

class my_root : public avk::root {
 public:
  vk::Instance vulkan_instance() {
    if (!mInstance) {
      mInstance = vk::createInstanceUnique(vk::InstanceCreateInfo{});
    }
    return mInstance.get();
  }

  vk::PhysicalDevice &physical_device() override {
    if (!mPhysicalDevice) {
      mPhysicalDevice = vulkan_instance().enumeratePhysicalDevices().front();
    }
    return mPhysicalDevice;
  }

  vk::Device &device() override {
    if (!mDevice) {
      // Select one queue that can handle everything:
      auto queueFamilyIndex = avk::queue::find_best_queue_family_for(physical_device(), {}, avk::queue_selection_preference::versatile_queue, {});
      auto queues = avk::make_vector(avk::queue::prepare(physical_device(), 0, 0));
      auto config = avk::queue::get_queue_config_for_DeviceCreateInfo(std::begin(queues), std::end(queues));
      for (auto i = 0; i < std::get<0>(config).size(); ++i) {
        std::get<0>(config)[i].setPQueuePriorities(std::get<1>(config)[i].data());
      }

      // Create the device using the queue information from above:
      mDevice = physical_device().createDeviceUnique(vk::DeviceCreateInfo{}
        .setQueueCreateInfoCount(1u)
        .setPQueueCreateInfos(std::get<0>(config).data()));

      // AFTER device creation, the queue handle(s) can be assigned to the queues:
      queues[0].assign_handle(mDevice.get());

      // Store the queue:
      mQueue = std::move(queues[0]);

      // With the device in place, create a dynamic dispatch loader:
      mDynamicDispatch = vk::DispatchLoaderDynamic(
        vulkan_instance(),
        vkGetInstanceProcAddr,
        device());

#if defined(AVK_USE_VMA)
      // With everything in place, create the memory allocator:
      VmaAllocatorCreateInfo allocatorInfo = {};
      allocatorInfo.physicalDevice = physical_device();
      allocatorInfo.device = device();
      allocatorInfo.instance = vulkan_instance();
      // you might want to set some flags via allocatorInfo.flags
      vmaCreateAllocator(&allocatorInfo, &mMemoryAllocator);
#else
      mMemoryAllocator = {physical_device(), device()};
#endif
    }
    return mDevice.get();
  }

  vk::DispatchLoaderDynamic &dynamic_dispatch() override {
    if (!mDevice) {
      device();
    }
    return mDynamicDispatch;
  }

  AVK_MEM_ALLOCATOR_TYPE& memory_allocator() override {
    return mMemoryAllocator;
  }

  vk::Queue queue() {
    if (!mDevice) {
      device();
    }
    return mQueue.handle();
  }

 private:
  vk::UniqueInstance mInstance;
  vk::PhysicalDevice mPhysicalDevice;
  vk::UniqueDevice mDevice;
  vk::DispatchLoaderDynamic mDynamicDispatch;
  AVK_MEM_ALLOCATOR_TYPE mMemoryAllocator;
  avk::queue mQueue;
};

int main() {
  try {
    auto myRoot = my_root{};

    std::array<int8_t, 12> data = {72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100, 33};

    auto myBuffer = myRoot.create_buffer(
      avk::memory_usage::host_coherent, {},
      avk::generic_buffer_meta::create_from_data(data));
    myBuffer->fill(data.data(), 0, avk::sync::not_required());

    std::string readFromBuffer(data.size(), ' ');
    myBuffer->read(readFromBuffer.data(), 0, avk::sync::not_required());
    std::cout << readFromBuffer << '\n';
  } catch (std::runtime_error &e) {
    std::cout << e.what() << '\n';
  }
  return 0;
}
