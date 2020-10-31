## Application Arguments

| Argument                                                           | Description                      |
|--------------------------------------------------------------------|----------------------------------|
| --logmin [finer\|fine\|info\|warn\|warning\|error\|critical\|none] | Sets minimum allowed log level   |
| --logmax [finer\|fine\|info\|warn\|warning\|error\|critical\|none] | Sets maximum allowed log level   |
| --validation-layers                                                | Enables Vulkan Validation Layers |


**NOTE:** to enable Vulkan Validation Layers you are required to have VulkanSDK, otherwise the application may result with a crash.
For linux see: https://vulkan.lunarg.com/doc/view/1.2.135.0/linux/getting_started.html

**NOTE:** To self: `source ~/vulkan/1.2.154.0/setup-env.sh`