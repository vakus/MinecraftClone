CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr

release: src/main.cpp shaders
	g++ $(CFLAGS) -o build/VulkanTest src/main.cpp $(LDFLAGS) -Wall -W -O3

debug: src/main.cpp shaders
	g++ $(CFLAGS) -o build/VulkanTest src/main.cpp $(LDFLAGS) -Wall -W -g -Og -D VALIDATIONLAYERS -D LOGMIN=2

shaders:
	glslc src/shaders/shader.vert -o build/shaders/vert.spv
	glslc src/shaders/shader.frag -o build/shaders/frag.spv

.PHONY: clean
clean:
	rm -f build/*