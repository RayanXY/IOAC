#ifndef _CACHE_H_
#define _CACHE_H_

#include <iostream>
#include <vector>

class Memory {

	public:
		int wordsPerBlocks, memorySize, mapping, 
			setSize, replacementPolicy;
		std::vector< std::vector<int> > elements;

		void createMemory (Memory &memory) {

			std::vector<int> aux;

			for (int i = 0; i < (memory.wordsPerBlocks * memory.memorySize); i++){
				for (int j = 0; j < memory.wordsPerBlocks; j++, i++) aux.push_back (i);
				memory.elements.push_back (aux);
				aux.clear ();
				i--;
			}

		}

		void showMemory (Memory &memory) {

			std::cout << ">>> MEMÓRIA PRINCIPAL" << std::endl;
			std::cout << "Bloco" << "\t" << "Endereço" << std::endl;

			for (size_t i = 0; i < memory.elements.size (); i++){
				for (int j = 0; j < memory.wordsPerBlocks; j++){
					std::cout << i << "\t" << memory.elements[i][j] << std::endl;
				}
			}
			std::cout << std::endl;

		}
	
};


class Cache : public Memory {

	public:

		int lines;
		std::vector< std::vector<int> > elements;
		std::vector<int> count;

		void createCache (Cache &cache) {

			std::vector<int> aux;

			for (int i = 0; i < (cache.wordsPerBlocks * cache.lines); i++){
				for (int j = 0; j < cache.wordsPerBlocks; j++, i++)	aux.push_back (-1);
				cache.elements.push_back (aux);
				aux.clear ();
				i--;
			}

		}

		void showCache (Cache &cache, Memory &memory) {

			std::cout << "CACHE L1" << std::endl;
			std::cout << "Linha\tBloco\tEndereço\tConteúdo\n";

			for (size_t i = 0; i < cache.elements.size (); i++){
				for (int j = 0; j < cache.wordsPerBlocks; j++){

					int block, address;
					block = cache.elements[i][j]/memory.wordsPerBlocks;
					address = cache.elements[i][j];

					std::cout << i << "\t" << block << "\t" << address << "\t\t" << memory.elements[block][address] << std::endl;

				}
			}
			std::cout << std::endl;

		}

		int findLeastFrequentlyUsed (Cache &cache){

			int less = cache.count[0];
			int lessIndex = 0;

			for (int i = 1; i < cache.lines; i++){
				if (cache.count[i] < less){
					less = cache.count[i];
					lessIndex = i;
				}
			}

			return lessIndex;

		}

		int findLeastFrequentlyUsedSets (Cache &cache, int begin, int end) {

			int less = cache.count[begin];
			int lessIndex = begin;

			for (int i = begin + 1; i < end; i++) {
				if (cache.count[i] < less) {
					less = cache.count[i];
					lessIndex = i;
				}
			}

			return lessIndex;

		}

		int findLeastRecentlyUsed (Cache &cache) {

			int greater = cache.count[0];
			int greaterIndex = 0;

			for (int i = 1; i < cache.lines; i++) {
				if (cache.count[i] > greater) {
					greater = cache.count[i];
					greaterIndex = i;
				}
			}

			return greaterIndex;

		}

		int findLeastRecentlyUsedSets (Cache &cache, int begin, int end) {

			int greater = cache.count[begin];
			int greaterIndex = begin;

			for (int i = begin + 1; i < end; i++) {
				if (cache.count[i] > greater) {
					greater = cache.count[i];
					greaterIndex = i;
				}
			}

			return greaterIndex;

		}

		void changeLeastRecentlyUsed (Cache &cache) {
			for (int i = 0; i < cache.lines; i++) {
				cache.count[i] = cache.count[i] + 1;
			}
		}

		void changeLeastRecentlyUsedSets (Cache &cache, int begin, int end) {
			for (int i = begin + 1; i < end; i++) {
				cache.count[i] = cache.count[i] + 1;
			}
		}

};

	void changeBlocks (Memory &memory, Cache &cache, int blockCache, int blockMemory) {
		for (int i = 0; i < memory.wordsPerBlocks; i++) {
			cache.elements[blockCache][i] = memory.elements[blockMemory][i];
		}
	}

	bool findWord (Cache &cache, int word, int &block, int begin, int end) {

		for (int i = begin; i < end; i++) {
			for (size_t j = 0; j < cache.elements[i].size (); j++) {
				if (cache.elements[i][j] == word) {
					block = i;
					return true;
				}
			}
		}

		return false;

	}

#endif