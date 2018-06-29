/**
 * @file cache.h
 * @author Rayan Avelino
 * @copyright 2018 Rayan Avelino
 */
#ifndef INCLUDE_CACHE_H_
#define INCLUDE_CACHE_H_

#include "memory.h"

/**
 * @class Cache
 *
 * This class contains a set of functions for controlling
 * the cache and its contents. It allows to mantain controll
 * and edit whenever it's necessary.
 */
template <typename T> class Cache : public Memory <T> {
 public:
        T lines;
        std::vector< std::vector<T> > elements;
        std::vector<T> count;

        /* 
         * Creates the Cache
         * @param cache - The L1 Cache
         */
        void createCache(Cache <T> &cache) {
            std::vector<T> aux;

            for (int i = 0; i < (cache.wordsPerBlocks * cache.lines); i++) {
                for (int j = 0; j < cache.wordsPerBlocks; j++, i++) {
                    aux.push_back(-1);
                }
                cache.elements.push_back(aux);
                aux.clear();
                i--;
            }
        }
        /* 
         * Show the current state of the Cache
         * @param memory - The Main Memory
         * @param cache - The L1 Cache
         */
        void showCache(Cache <T> &cache, Memory <T> &memory) {
            std::cout << "CACHE L1" << std::endl;
            std::cout << "Linha\tBloco\tEndereço"<< std::endl;

            for (size_t i = 0; i < cache.elements.size(); i++) {
                for (int j = 0; j < cache.wordsPerBlocks; j++) {
                    int block, address;
                    block = cache.elements[i][j]/memory.wordsPerBlocks;
                    address = cache.elements[i][j];

                    std::cout << i << "\t" << block << "\t"
                              << address << std::endl;
                }
            }
            std::cout << std::endl;
        }
        /* 
         * Finds the least frequently used address in the cache
         * @param cache - The Cache in use
         * @return the least frequently used index
         */
        T findLeastFrequentlyUsed(Cache <T> &cache) {
            T less = cache.count[0];
            T lessIndex = 0;

            for (int i = 1; i < cache.lines; i++) {
                if (cache.count[i] < less) {
                    less = cache.count[i];
                    lessIndex = i;
                }
            }

            return lessIndex;
        }
        /* 
         * Finds the least frequently used set of address in the cache
         * @param cache - The Cache in use
         * @param begin - Where the cache begins
         * @param end - Where the cache ends
         * @return the least frequently used set of index
         */
        T findLeastFrequentlyUsedSets(Cache <T> &cache, T begin, T end) {
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
        /* 
         * Finds the least recently used address in the cache
         * @param cache - The Cache in use
         * @return the least recently used of index
         */
        T findLeastRecentlyUsed(Cache <T> &cache) {
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
        /* 
         * Finds the least recently used sets of address in the cache
         * @param cache - The Cache in use
         * @param begin - Where the cache begins
         * @param end - Where the cache end
         */
        T findLeastRecentlyUsedSets(Cache <T> &cache, T begin, T end) {
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
        /* 
         * It changes the least recently used address
         * @param cache - The Cache in use
         * @return the least recently used set of index
         */
        void changeLeastRecentlyUsed(Cache <T> &cache) {
            for (int i = 0; i < cache.lines; i++) {
                cache.count[i] = cache.count[i] + 1;
            }
        }
        /* 
         * It changes the least recently used sets of address
         * @param cache - The Cache in use
         * @param begin - Where the cache begins
         * @param end - Where the cache end
         */
        void changeLeastRecentlyUsedSets(Cache <T> &cache, T begin, T end) {
            for (int i = begin + 1; i < end; i++) {
                cache.count[i] = cache.count[i] + 1;
            }
        }
};
/*
 * It changes the blocks of elements
 * @param memory - The Main Memory
 * @param cache - The L1 Cache
 * @param blockCache - The current block in use of the cache
 * @param blockMemory - The current block in use of the memory
 */
template <typename T> void changeBlocks(Memory <T> &memory, Cache <T> &cache,
                                        T blockCache, T blockMemory) {
    for (T i = 0; i < memory.wordsPerBlocks; i++) {
        cache.elements[blockCache][i] = memory.elements[blockMemory][i];
    }
}

/*
 * Finds the address
 * @param cache - The L1 Cache
 * @param word - The address to be found
 * @param block - Where the address is if it's found
 * @param begin - Where the cache begins
 * @param end - Where the cache end
 */
template <typename T> bool findWord(Cache <T> &cache, T word,
                                    T &block, T begin, T end) {
    for (int i = begin; i < end; i++) {
        for (size_t j = 0; j < cache.elements[i].size(); j++) {
            if (cache.elements[i][j] == word) {
                block = i;
                return true;
            }
        }
    }

    return false;
}

#endif  // INCLUDE_CACHE_H_
