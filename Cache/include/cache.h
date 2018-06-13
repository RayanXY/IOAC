#ifndef _CACHE_H_
#define _CACHE_H_

#include <iostream>
#include <vector>

template <typename T> class Memory {

	public:
		T wordsPerBlocks, memorySize, mapping, setSize, replacementPolicy;

		std::vector< std::vector<T> > elements;

		void createMemory (Memory <T> &memory) {

			std::vector<T> aux;

			for (int i = 0; i < (memory.wordsPerBlocks * memory.memorySize); i++){
				for (int j = 0; j < memory.wordsPerBlocks; j++, i++){
					aux.push_back (i);
				}
				memory.elements.push_back (aux);
				aux.clear ();
				i--;
			}

		}

		void showMemory (Memory <T> &memory) {

			std::cout << ">>> MEMÓRIA PRINCIPAL" << std::endl;
			std::cout << "Bloco\tEndereço" << std::endl;

			for (size_t i = 0; i < memory.elements.size (); i++){
				for (int j = 0; j < memory.wordsPerBlocks; j++){
					std::cout << i << "\t" << memory.elements[i][j] << std::endl;
				}
			}
			std::cout << std::endl;

		}
	
};


template <typename T> class Cache : public Memory <T> {

	public:

		T lines;
		std::vector< std::vector<T> > elements;
		std::vector<T> count;

		void createCache (Cache <T> &cache) {

			std::vector<T> aux;

			for (int i = 0; i < (cache.wordsPerBlocks * cache.lines); i++){
				for (int j = 0; j < cache.wordsPerBlocks; j++, i++){
					aux.push_back (-1);
				}
				cache.elements.push_back (aux);
				aux.clear ();
				i--;
			}

		}

		void showCache (Cache <T> &cache, Memory <T> &memory) {

			std::cout << "CACHE L1" << std::endl;
			std::cout << "Linha\tBloco\tEndereço"<< std::endl;

			for (size_t i = 0; i < cache.elements.size (); i++){
				for (int j = 0; j < cache.wordsPerBlocks; j++){

					int block, address;
					block = cache.elements[i][j]/memory.wordsPerBlocks;
					address = cache.elements[i][j];

					std::cout << i << "\t" << block << "\t" << address << std::endl;

				}
			}
			std::cout << std::endl;

		}

		T findLeastFrequentlyUsed (Cache <T> &cache){

			T less = cache.count[0];
			T lessIndex = 0;

			for (int i = 1; i < cache.lines; i++){
				if (cache.count[i] < less){
					less = cache.count[i];
					lessIndex = i;
				}
			}

			return lessIndex;

		}

		T findLeastFrequentlyUsedSets (Cache <T> &cache, T begin, T end) {

			T less = cache.count[begin];
			T lessIndex = begin;

			for (int i = begin + 1; i < end; i++) {
				if (cache.count[i] < less) {
					less = cache.count[i];
					lessIndex = i;
				}
			}

			return lessIndex;

		}

		T findLeastRecentlyUsed (Cache <T> &cache) {

			T greater = cache.count[0];
			T greaterIndex = 0;

			for (int i = 1; i < cache.lines; i++) {
				if (cache.count[i] > greater) {
					greater = cache.count[i];
					greaterIndex = i;
				}
			}

			return greaterIndex;

		}

		T findLeastRecentlyUsedSets (Cache <T> &cache, T begin, T end) {

			T greater = cache.count[begin];
			T greaterIndex = begin;

			for (int i = begin + 1; i < end; i++) {
				if (cache.count[i] > greater) {
					greater = cache.count[i];
					greaterIndex = i;
				}
			}

			return greaterIndex;

		}

		void changeLeastRecentlyUsed (Cache <T> &cache) {
			for (int i = 0; i < cache.lines; i++) {
				cache.count[i] = cache.count[i] + 1;
			}
		}

		void changeLeastRecentlyUsedSets (Cache <T> &cache, T begin, T end) {
			for (int i = begin + 1; i < end; i++) {
				cache.count[i] = cache.count[i] + 1;
			}
		}

};

template <typename T> void changeBlocks (Memory <T> &memory, Cache <T> &cache, T blockCache, T blockMemory) {
	for (T i = 0; i < memory.wordsPerBlocks; i++) {
		cache.elements[blockCache][i] = memory.elements[blockMemory][i];
	}
}

template <typename T> bool findWord (Cache <T> &cache, T word, T &block, T begin, T end) {

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