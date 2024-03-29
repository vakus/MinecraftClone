# Minecraft Clone in C++/Vulkan

## About

This project was created as part of my University final year project. The focus of this project was to explore C++ programming language and Vulkan Graphics API.

The game was created under Linux (Debian) and was not tested on Windows operating systems.

![Game Screenshot](/assets/example_image.jpg?raw=true "Game Screenshot")

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