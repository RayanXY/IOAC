#include <iostream>
#include "./cache.cpp"

int main (int argc, char * argv[]) {

	std::string config = "./data/config.txt";

	Cache cache (config);

	cache.showConfig ();
	
}