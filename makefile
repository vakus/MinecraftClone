CFLAGS = -std=c++17 -fmax-errors=1
#`isystem include` to prevent warnings for libraries to be displayed.
# im not very interested in those
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -isystem include
COMPILEFILES = src/main.cpp src/logger.cpp src/application.cpp src/world/block.cpp src/world/chunk.cpp src/world/world.cpp

release: src/main.cpp shaders textures
	g++ $(CFLAGS) -o build/VulkanTest $(COMPILEFILES) $(LDFLAGS) -Wall -W -O3

debug: src/main.cpp shaders textures
	g++ $(CFLAGS) -o build/VulkanTest $(COMPILEFILES) $(LDFLAGS) -Wall -W -g -O0 -D VALIDATIONLAYERS -D LOGMIN=2 -D LAYERS_KHRONOS_VALIDATION

textures:
	mkdir -p build/textures
	cp -rv src/textures/* build/textures

shaders:
	mkdir -p build/shaders
	glslc src/shaders/shader.vert -o build/shaders/vert.spv
	glslc src/shaders/shader.frag -o build/shaders/frag.spv

.PHONY: clean
clean:
	rm -rf build/*