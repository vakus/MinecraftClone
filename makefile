CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr

VulkanTest: main.cpp
	g++ $(CFLAGS) -o VulkanTest main.cpp $(LDFLAGS)

.PHONY: test clean

debug: main.cpp
	g++ $(CFLAGS) -o VulkanTest main.cpp $(LDFLAGS) -D debug

test: VulkanTest
	./VulkanTest

clean:
	rm -f VulkanTest
