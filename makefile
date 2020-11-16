CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr

VulkanTest: main.cpp
	g++ $(CFLAGS) -o VulkanTest main.cpp $(LDFLAGS) -Wall

.PHONY: test clean

debug: main.cpp
	g++ $(CFLAGS) -o VulkanTest main.cpp $(LDFLAGS) -Wall -D VALIDATIONLAYERS -D LOGMIN=2

test: VulkanTest
	./VulkanTest

clean:
	rm -f VulkanTest
