CFLAGS = -std=c++17 -fmax-errors=1
#`isystem include` to prevent warnings for libraries to be displayed.
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -isystem include
MAIN_DEFAULT = src/main.cpp
MAIN_TEST = src/test/main.cpp
COMPILEFILES = src/logger.cpp src/application.cpp src/world/block.cpp src/world/chunk.cpp src/world/world.cpp

release: src/main.cpp shaders textures
	g++ $(CFLAGS) -o build/Vulkan $(MAIN_DEFAULT) $(COMPILEFILES) $(LDFLAGS) -Wall -W -O3

debug: src/main.cpp shaders textures
	g++ $(CFLAGS) -o build/Vulkan $(MAIN_DEFAULT) $(COMPILEFILES) $(LDFLAGS) -Wall -W -g -O0 -D VALIDATIONLAYERS -D LOGMIN=2 -D LAYERS_KHRONOS_VALIDATION

profile: src/main.cpp shaders textures
	g++ $(CFLAGS) -o build/Vulkan $(MAIN_DEFAULT) $(COMPILEFILES) $(LDFLAGS) -Wall -W -g -pg -O0 -D PROFILE
	cd build; ./Vulkan;	gprof ./Vulkan > profile.log; (gprof2dot profile.log | dot -Tpng -o profile.png)
	rm build/gmon.out

test: src/test/main.cpp
	g++ $(CFLAGS) -o build/VulkanTest $(MAIN_TEST) $(COMPILEFILES) $(LDFLAGS) -Wall -W -g -O0


textures:
	mkdir -p build/textures
	cp -rv assets/textures/* build/textures

shaders:
	mkdir -p build/shaders
	glslc src/shaders/shader.vert -o build/shaders/vert.spv
	glslc src/shaders/shader.frag -o build/shaders/frag.spv

.PHONY: clean
clean:
	rm -rf build/*