#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "../include/cache.h"

int main (int argc, char * argv[]) {

	/// Reads the configuratio file
	std::ifstream file;
	file.open ("./data/Direto.txt");
	//file.open ("./data/TA_Random.txt");
	//file.open ("./data/TA_FIFO.txt");
	//file.open ("./data/TA_LFU.txt");
	//file.open ("./data/TA_LRU.txt");
	//file.open ("./data/PA_Random.txt");
	//file.open ("./data/PA_FIFO.txt");
	//file.open ("./data/PA_LFU.txt");
	//file.open ("./data/PA_LRU.txt");

	/// Sets the parameters
	Memory memory;
	Cache cache;

	file >> memory.wordsPerBlocks >> cache.lines >> 
			memory.memorySize >> memory.mapping >> 
			memory.setSize >> memory.replacementPolicy;
	cache.wordsPerBlocks = memory.wordsPerBlocks;

	/// Creates the objects
	memory.createMemory (memory);
	cache.createCache (cache);

	/// Variables
	std::string instruction, aux;
	std::size_t found;
	int word = 0, content = 0, blockCache = 0, blockMemory = 0, rest = 0, sizeWay = 0, 
	blockWay = 0, begin = 0, end = 0, blockCacheAux = 0;
	bool state = false;

	/// Counter for LFU and LRU policy
	std::vector<int> blockCacheSets (memory.setSize, 0);

	/// Using the mapping informed
	switch (memory.mapping) {
		/// Directed-Mapped
		case 1:
			/// Gets the commando from the user
			while (std::getline (std::cin, instruction)) {

				/// Search for a space in the command
				found = instruction.find (" ");
				/// If it finds it, splits the command
				if (found != std::string::npos) {
					aux = instruction.substr (found + 1);
					instruction = instruction.substr (0, found);
				}

				/// Reading the command
				if (instruction.compare ("Read") == 0) {

					word = std::stoi (aux);

					blockCache = (word / memory.wordsPerBlocks) % cache.lines;
					blockMemory = word / memory.wordsPerBlocks;
					rest = word % memory.wordsPerBlocks;

					if (cache.elements[blockCache][rest] == word) {
						std::cout << "HIT - Linha " << blockCache << std::endl;
					} else {
						std::cout << "MISS - Alocado na linha " << blockCache << " - Bloco " << blockMemory << " substituído." << std::endl;
						changeBlocks (memory, cache, blockCache, blockMemory);
					}

				} else if (instruction.compare("Write") == 0) {

					found = aux.find (" ");

					if (found != std::string::npos) {
						content = std::stoi (aux.substr (found + 1));
						word = std::stoi (aux.substr (0, found));
					}

					blockCache = (word / memory.wordsPerBlocks) % cache.lines;
					blockMemory = word / memory.wordsPerBlocks;
					rest = word % memory.wordsPerBlocks;

					if (cache.elements[blockCache][rest] == word) {
						std::cout << "HIT - Linha " << blockCache << " - Novo valor do endereço " << word << " = " << content << std::endl;
					} else {
						std::cout << "MISS - Alocado na linha " << blockCache << " - Bloco " << blockMemory << " substituído." << std::endl;
						changeBlocks (memory, cache, blockCache, blockMemory, content);
					}

				} else if (instruction.compare("Show") == 0) {
					cache.showCache (cache, memory);
					memory.showMemory (memory);
				}

			}
			break;
		/// Fully Associative
		case 2: 
			switch (memory.replacementPolicy) {
				/// Random
				case 1:
					while (std::getline (std::cin, instruction)) {

						begin = 0;
						end = cache.elements.size ();
						/// Gets the command
						found = instruction.find (" ");

						if (found != std::string::npos) {
							aux = instruction.substr (found + 1);
							instruction = instruction.substr (0, found);
						}

						blockMemory = word / memory.wordsPerBlocks;

						if (instruction.compare ("Read") == 0) {

							word = std::stoi (aux);

							/// Search inside the cache
							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << std::endl;
								state = false;
							} else { 	//!< Find the first available position in the cache
								state = findWord (cache, -1, blockCache, begin, end);
								if (state) {
									changeBlocks (memory, cache, blockCache, blockMemory);
								} else {
									srand (time(NULL));
									blockCache = rand () % cache.lines;
									changeBlocks (memory, cache, blockCache, blockMemory);
								}
								std::cout << "MISS - Alocado na linha " << blockCache << " - Bloco " << blockMemory << " substituído." << std::endl;
							}


						} else if (instruction.compare ("Write") == 0) {

							found = aux.find (" ");

							if (found != std::string::npos) {
								content = std::stoi (aux.substr (found + 1));
								word = std::stoi (aux.substr (0, found));
							}

							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << " - Novo valor do endereço " << word << " = " << content << std::endl;
								state = false;
							} else { 	//!< Find the first available position in the cache
								state = findWord (cache, -1, blockCache, begin, end);
								if (state) {
									changeBlocks (memory, cache, blockCache, blockMemory);
								} else {
									srand (time(NULL));
									blockCache = rand () % cache.lines;
									changeBlocks (memory, cache, blockCache, blockMemory);
								}
								std::cout << "MISS - Alocado na linha " << blockCache << " - Bloco " << blockMemory << " substituído." << std::endl;
							}


						} else if (instruction.compare ("Show") == 0) {
							cache.showCache (cache, memory);
							memory.showMemory (memory);
						}

					} break;
				/// FIFO
				case 2: 
					while (std::getline (std::cin, instruction)) {

						begin = 0;
						end = cache.elements.size ();
						/// Gets the command
						found = instruction.find (" ");
						if (found != std::string::npos) {
							aux = instruction.substr (found + 1);
							instruction = instruction.substr (0, found);
						}

						blockMemory = word / memory.wordsPerBlocks;

						if (instruction.compare ("Read") == 0) {

							word = std::stoi (aux);

							/// Search inside the cache
							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << std::endl;
								state = false;
							} else {
								changeBlocks (memory, cache, blockCacheAux % cache.lines, blockMemory);
								std::cout << "MISS - Alocado na linha " << (blockCacheAux % cache.lines) << " - Bloco " << blockMemory << " substituído." << std::endl;
								blockCacheAux = blockCacheAux + 1;
							}

						} else if (instruction.compare ("Write") == 0) {

							found = aux.find (" ");

							if (found != std::string::npos) {
								content = std::stoi (aux.substr (found + 1));
								word = std::stoi (aux.substr (0, found));
							}

							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << " - Novo valor do endereço " << word << " = " << content << std::endl;
								state = false;
							} else {
								changeBlocks (memory, cache, blockCacheAux % cache.lines, blockMemory);
								std::cout << "MISS - Alocado na linha " << (blockCacheAux % cache.lines) << " - Bloco " << blockMemory << " substituído." << std::endl;
								blockCacheAux = blockCacheAux + 1;
							}

						} else if (instruction.compare ("Show") == 0) {
							cache.showCache (cache, memory);
							memory.showMemory (memory);
						}

					} break;
				/// LFU
				case 3:
					for (int i = 0; i < cache.lines; i++) {
						cache.count.push_back(0);
					}
					while (std::getline (std::cin, instruction)) {

						begin = 0;
						end = cache.elements.size ();
						/// Gets the command
						found = instruction.find (" ");
						if (found != std::string::npos) {
							aux = instruction.substr (found + 1);
							instruction = instruction.substr (0, found);
						}

						blockMemory = word / memory.wordsPerBlocks;

						if (instruction.compare ("Read") == 0) {

							word = std::stoi (aux);

							/// Search inside the cache
							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << std::endl;
								cache.count[blockCache] = cache.count[blockCache] + 1;
								state = false;
							} else {
								state = findWord (cache, -1, blockCache, begin, end);
								if (state) {
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = 1;
								} else {
									blockCache = cache.findLeastFrequentlyUsed (cache);
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = 1;
								}
								std::cout << "MISS - Alocado na linha " << blockCache << " - Bloco " << blockMemory << " substituído." << std::endl;
							}

						} else if (instruction.compare ("Write") == 0) {

							found = aux.find (" ");

							if (found != std::string::npos) {
								content = std::stoi (aux.substr (found + 1));
								word = std::stoi (aux.substr (0, found));
							}

							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << " - Novo valor do endereço " << word << " = " << content << std::endl;
								cache.count[blockCache] = cache.count[blockCache] + 1;
								state = false;
							} else {
								state = findWord (cache, -1, blockCache, begin, end);
								if (state) {
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = 1;
								} else {
									blockCache = cache.findLeastFrequentlyUsed (cache);
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = 1;
								}
								std::cout << "MISS - Alocado na linha " << blockCache << " - Bloco " << blockMemory << " substituído." << std::endl;
							}

						} else if (instruction.compare ("Show") == 0) {
							cache.showCache (cache, memory);
							memory.showMemory (memory);
						}

					} break;
				/// LRU
				case 4:
					for (int i = 0; i < cache.lines; i++) {
						cache.count.push_back(0);
					}
					while (std::getline (std::cin, instruction)) {

						begin = 0;
						end = cache.elements.size ();
						/// Gets the command
						found = instruction.find (" ");
						if (found != std::string::npos) {
							aux =instruction.substr (found + 1);
							instruction = instruction.substr (0, found);
						}

						blockMemory = word / memory.wordsPerBlocks;

						if (instruction.compare ("Read") == 0) {

							word = std::stoi (aux);

							/// Search inside the cache
							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << std::endl;
								cache.count[blockCache] = -1;
								state = false;
							} else {
								state = findWord (cache, -1, blockCache, begin, end);
								if (state) {
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = -1;
								} else {
									blockCache = cache.findLeastRecentlyUsed (cache);
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = -1;
								}
								std::cout << "MISS - Alocado na linha " << blockCache << " - Bloco " << blockMemory << " substituído." << std::endl;
							}

							cache.changeLeastRecentlyUsed (cache);

						} else if (instruction.compare ("Write") == 0) {

							found = aux.find (" ");

							if (found != std::string::npos) {
								content = std::stoi (aux.substr (found + 1));
								word = std::stoi (aux.substr (0, found));
							}

							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << " - Novo valor do endereço " << word << " = " << content << std::endl;
								cache.count[blockCache] = -1;
								state = false;
							} else {
								state = findWord (cache, -1, blockCache, begin, end);
								if (state) {
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = -1;
								} else {
									blockCache = cache.findLeastRecentlyUsed (cache);
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = -1;
								}
								std::cout << "MISS - Alocado na linha " << blockCache << " - Bloco " << blockMemory << " substituído." << std::endl;
							}

							cache.changeLeastRecentlyUsed (cache);

						} else if (instruction.compare ("Show") == 0) {
							cache.showCache (cache, memory);
							memory.showMemory (memory);
						}

					} break;

			} break;
		/// Set Associative
		case 3:
			switch (memory.replacementPolicy) {
				/// Random
				case 1:
					while (std::getline (std::cin, instruction)) {

						/// Gets the command
						found = instruction.find (" ");
						if (found != std::string::npos) {
							aux = instruction.substr (found + 1);
							instruction = instruction.substr (0, found);
						}

						blockMemory = word / memory.wordsPerBlocks;
						sizeWay = cache.lines / memory.setSize;
						blockWay = blockMemory % memory.setSize;
						begin = (blockWay * sizeWay);
						end = begin + sizeWay;

						if (instruction.compare ("Read") == 0) {

							word = std::stoi (aux);

							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << std::endl;
								state = false;
							} else { 	//!< Find the first available position in the cache
								state = findWord (cache, -1, blockCache, begin, end);
								if (state) {
									changeBlocks (memory, cache, blockCache, blockMemory);
									state = false;
								} else {
									srand (time(NULL));
									blockCache = rand () % cache.lines;
									changeBlocks (memory, cache, blockCache, blockMemory);
								}
								std::cout << "MISS - Alocado na linha " << blockCache << " - Bloco " << blockMemory << " substituído." << std::endl;
							}


						} else if (instruction.compare ("Write") == 0) {

							found = aux.find (" ");

							if (found != std::string::npos) {
								content = std::stoi (aux.substr (found + 1));
								word = std::stoi (aux.substr (0, found));
							}

							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << " - Novo valor do endereço " << word << " = " << content << std::endl;
								state = false;
							} else { 	//!< Find the first available position in the cache
								state = findWord (cache, -1, blockCache, begin, end);
								if (state) {
									changeBlocks (memory, cache, blockCache, blockMemory);
									state = false;
								} else {
									srand (time(NULL));
									blockCache = rand () % cache.lines;
									changeBlocks (memory, cache, blockCache, blockMemory);
								}
								std::cout << "MISS - Alocado na linha " << blockCache << " - Bloco " << blockMemory << " substituído." << std::endl;
							}


						} else if (instruction.compare ("Show") == 0) {
							cache.showCache (cache, memory);
							memory.showMemory (memory);
						}

					} break;
				/// FIFO
				case 2:
					while (std::getline (std::cin, instruction)) {

						/// Gets the command
						found = instruction.find (" ");
						if (found != std::string::npos) {
							aux = instruction.substr (found + 1);
							instruction = instruction.substr (0, found);
						}

						blockMemory = word / memory.wordsPerBlocks;
						sizeWay = cache.lines / memory.setSize;
						blockWay = blockMemory % memory.setSize;
						begin = (blockWay * sizeWay);
						end = begin + sizeWay;

						if (instruction.compare ("Read") == 0) {

							word = std::stoi (aux);

							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << std::endl;
								state = false;
							} else {
								changeBlocks (memory, cache, (begin + blockCacheSets[blockWay] % sizeWay), blockMemory);
								std::cout << "MISS - Alocado na linha " << (begin + blockCacheSets[blockWay] % sizeWay) << " - Bloco " << blockMemory << " substituído." << std::endl;
								blockCacheSets[blockWay] = blockCacheSets[blockWay] + 1;
							}

						} else if (instruction.compare ("Write") == 0) {

							found = aux.find (" ");

							if (found != std::string::npos) {
								content = std::stoi (aux.substr (found + 1));
								word = std::stoi (aux.substr (0, found));
							}

							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << " - Novo valor do endereço " << word << " = " << content << std::endl;
								state = false;
							} else {
								changeBlocks (memory, cache, (begin + blockCacheSets[blockWay] % sizeWay), blockMemory);
								std::cout << "MISS - Alocado na linha " << (begin + blockCacheSets[blockWay] % sizeWay) << " - Bloco " << blockMemory << " substituído." << std::endl;
								blockCacheSets[blockWay] = blockCacheSets[blockWay] + 1;
							}

						} else if (instruction.compare ("Show") == 0) {
							cache.showCache (cache, memory);
							memory.showMemory (memory);
						}

					} break;
				/// LFU
				case 3: 
					for (int i = 0; i < cache.lines; i++) {
						cache.count.push_back(0);
					}
					while (std::getline (std::cin, instruction)) {
						// Gets the command
						found = instruction.find (" ");
						if (found != std::string::npos) {
							aux = instruction.substr (found + 1);
							instruction = instruction.substr (0, found);
						}

						blockMemory = word / memory.wordsPerBlocks;
						sizeWay = cache.lines / memory.setSize;
						blockWay = blockMemory % memory.setSize;
						begin = (blockWay * sizeWay);
						end = begin + sizeWay;

						if (instruction.compare ("Read") == 0) {

							word = std::stoi (aux);

							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << std::endl;
								cache.count[blockCache] = cache.count[blockCache] + 1;
								state = false;
							} else {
								state = findWord (cache, -1, blockCache, begin, end);
								if (state) {
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = 1;
								} else {
									blockCache = cache.findLeastFrequentlyUsed (cache);
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = 1;
								}
								std::cout << "MISS - Alocado na linha " << blockCache << " - Bloco " << blockMemory << " substituído." << std::endl;
							}

						} else if (instruction.compare ("Write") == 0) {

							found = aux.find (" ");

							if (found != std::string::npos) {
								content = std::stoi (aux.substr (found + 1));
								word = std::stoi (aux.substr (0, found));
							}

							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << " - Novo valor do endereço " << word << " = " << content << std::endl;
								cache.count[blockCache] = cache.count[blockCache] + 1;
								state = false;
							} else {
								state = findWord (cache, -1, blockCache, begin, end);
								if (state) {
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = 1;
								} else {
									blockCache = cache.findLeastFrequentlyUsed (cache);
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = 1;
								}
								std::cout << "MISS - Alocado na linha " << blockCache << " - Bloco " << blockMemory << " substituído." << std::endl;
							}


						} else if (instruction.compare ("Show") == 0) {
							cache.showCache (cache, memory);
							memory.showMemory (memory);
						}

					} break;
				/// LRU
				case 4: 
					for (int i = 0; i < cache.lines; i++) {
						cache.count.push_back(0);
					}
					while (std::getline (std::cin, instruction)) {
						// Gets the command
						found = instruction.find (" ");
						if (found != std::string::npos) {
							aux = instruction.substr (found + 1);
							instruction = instruction.substr (0, found);
						}

						blockMemory = word / memory.wordsPerBlocks;
						sizeWay = cache.lines / memory.setSize;
						blockWay = blockMemory % memory.setSize;
						begin = (blockWay * sizeWay);
						end = begin + sizeWay;

						if (instruction.compare ("Read") == 0) {

							word = std::stoi (aux);

							/// Search inside the cache
							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << std::endl;
								cache.count[blockCache] = -1;
								state = false;
							} else {
								state = findWord (cache, -1, blockCache, begin, end);
								if (state) {
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = -1;
								} else {
									blockCache = cache.findLeastRecentlyUsedSets (cache, begin, end);
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = -1;
								}
								std::cout << "MISS - Alocado na linha " << blockCache << " - Bloco " << blockMemory << " substituído." << std::endl;
							}

							cache.changeLeastRecentlyUsedSets (cache, begin, end);

						} else if (instruction.compare ("Write") == 0) {

							found = aux.find (" ");

							if (found != std::string::npos) {
								content = std::stoi (aux.substr (found + 1));
								word = std::stoi (aux.substr (0, found));
							}

							state = findWord (cache, word, blockCache, begin, end);
							if (state) {
								std::cout << "HIT - Linha " << blockCache << " - Novo valor do endereço " << word << " = " << content << std::endl;
								cache.count[blockCache] = -1;
								state = false;
							} else {
								state = findWord (cache, -1, blockCache, begin, end);
								if (state) {
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = -1;
								} else {
									blockCache = cache.findLeastRecentlyUsedSets (cache, begin, end);
									changeBlocks (memory, cache, blockCache, blockMemory);
									cache.count[blockCache] = -1;
								}
								std::cout << "MISS - Alocado na linha " << blockCache << " - Bloco " << blockMemory << " substituído." << std::endl;
							}

							cache.changeLeastRecentlyUsedSets (cache, begin, end);

						} else if (instruction.compare ("Show") == 0) {
							cache.showCache (cache, memory);
							memory.showMemory (memory);
						}

					} break;

			} break;

	}

	file.close ();
	return 0;

}