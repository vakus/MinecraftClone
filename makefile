CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr


debug: src/main.cpp
	g++ $(CFLAGS) -o VulkanTest src/main.cpp $(LDFLAGS) -Wall -D VALIDATIONLAYERS -D LOGMIN=2

release: src/main.cpp
	g++ $(CFLAGS) -o VulkanTest src/main.cpp $(LDFLAGS) -Wall

clean:
	rm -f VulkanTest