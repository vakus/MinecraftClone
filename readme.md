## Application Arguments

| Argument                                                           | Description                         |
|--------------------------------------------------------------------|-------------------------------------|
| --logmin [finer\|fine\|info\|warn\|warning\|error\|critical\|none] | Sets minimum allowed log level      |
| --logmax [finer\|fine\|info\|warn\|warning\|error\|critical\|none] | Sets maximum allowed log level      |
| --validation-layers                                                | Enables Vulkan Validation Layers    |
| --validation-layer-khronos                                         | Enables VK_LAYER_KHRONOS_validation |
| --validation-layer-api-dump                                        | Enables VK_LAYER_LUNARG_api_dump    |
| --flatland                                                         | Makes the world flat                |


**NOTE:** to enable Vulkan Validation Layers you are required to have VulkanSDK, otherwise the application may result with a crash.
For linux see: https://vulkan.lunarg.com/doc/view/1.2.135.0/linux/getting_started.html

**NOTE:** To self: `source ~/vulkan/1.2.154.0/setup-env.sh`


## Compilation Arguments

| Argument                     | Description                                 |
|------------------------------|---------------------------------------------|
| -D LOGMIN=[1\|2\|3\|4\|5\|6] | Sets default minimum allowed log level      |
| -D LOGMAX=[1\|2\|3\|4\|5\|6] | Sets default maximum allowed log level      |
| -D VALIDATIONLAYERS          | Enables by default Vulkan Validation Layers |

**NOTE:** Levels for the Compilation Arguments are listed below:

| Level Number | Level Verbal |
|--------------|--------------|
| 1            | FINER        |
| 2            | FINE         |
| 3            | INFO         |
| 4            | WARNING      |
| 5            | ERROR        |
| 6            | CRITICAL     |