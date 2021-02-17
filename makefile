CFLAGS = -std=c++17
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -Iinclude

release: src/main.cpp shaders textures
	g++ $(CFLAGS) -o build/VulkanTest src/main.cpp $(LDFLAGS) -Wall -W -O3

debug: src/main.cpp shaders textures
	g++ $(CFLAGS) -o build/VulkanTest src/main.cpp $(LDFLAGS) -Wall -W -g -O3 -D VALIDATIONLAYERS -D LOGMIN=2

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