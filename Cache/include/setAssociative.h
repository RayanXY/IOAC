/**
 * @file setAssociative.h
 * @author Rayan Avelino
 * @copyright 2018 Rayan Avelino
 */
#ifndef INCLUDE_SETASSOCIATIVE_H_
#define INCLUDE_SETASSOCIATIVE_H_

/**
 * @class SetAssociative
 *
 * This class contains a set of funtions that will simulate
 * the set associative mapped cache.
 */
template <typename T> class SetAssociative {
 public:
        /**
         * Searches in the cache the passed word
         *
         * @param cache - The cache that it's been used
         * @param memory - The main memory that it's been used
         * @param blockCache - The auxilliar variable to find in what 
         *  block of the cache the word might be
         * @param blockMemory - The auxilliar variable to find in what 
         *  block of the memory the word might be
         * @param word - The word that must been find
         * @param begin - The position where the block begins
         * @param end - The position where the block ends
         * @param state - True if it finds the word and False when not
         */
        void readRandom(Cache <T> &cache, Memory <T> &memory,
                         T &blockCache, T &blockMemory, T &word,
                         T &begin, T &end, bool &state) {
            /// Search inside the cache
            state = findWord(cache, word, blockCache,
                             begin, end);

            if (state) {
                std::cout << "HIT - Linha "
                          << blockCache << std::endl;
                state = false;
            /// Find the first available position in the cache
            } else {
                state = findWord(cache, -1, blockCache,
                                 begin, end);

                if (state) {
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                    state = false;
                } else {
                    srand(time(NULL));
                    blockCache = rand() % cache.lines;
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                }
                std::cout << "MISS - Alocado na linha "
                          << blockCache << " - Bloco "
                          << blockMemory << " substituído."
                          << std::endl;
            }
        }

        /**
         * Writes in the passed address the passed content
         *
         * @param cache - The cache that it's been used
         * @param memory - The main memory that it's been used
         * @param blockCache - The auxilliar variable to find in what 
         *  block of the cache the word might be
         * @param blockMemory - The auxilliar variable to find in what 
         *  block of the memory the word might be
         * @param word - The word that must been find
         * @param begin - The position where the block begins
         * @param end - The position where the block ends
         * @param state - True if it finds the word and False when not
         * @param content - The new value to be stored
         */
        void writeRandom(Cache <T> &cache, Memory <T> &memory,
                          T &blockCache, T &blockMemory, T &word,
                          T &begin, T &end, bool &state, T &content) {
            /// Search inside the cache
            state = findWord(cache, word, blockCache,
                             begin, end);

            if (state) {
                std::cout << "HIT - Linha " << blockCache
                          << " - Novo valor do endereço "
                          << word << " = " << content
                          << std::endl;
                state = false;
            /// Find the first available position in the cache
            } else {
                state = findWord(cache, -1, blockCache,
                                 begin, end);

                if (state) {
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                    state = false;
                } else {
                    srand(time(NULL));
                    blockCache = rand() % cache.lines;
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                }
                std::cout << "MISS - Alocado na linha "
                          << blockCache << " - Bloco "
                          << blockMemory << " substituído."
                          << std::endl;
            }
        }

        /**
         * Searches in the cache the passed word
         *
         * @param cache - The cache that it's been used
         * @param memory - The main memory that it's been used
         * @param blockCache - The auxilliar variable to find in what 
         *  block of the cache the word might be
         * @param blockMemory - The auxilliar variable to find in what 
         *  block of the memory the word might be
         * @param word - The word that must been find
         * @param begin - The position where the block begins
         * @param end - The position where the block ends
         * @param state - True if it finds the word and False when not
         * @param sizeWay - The size of the way of where the address might be
         * @param blockWay - The block of where the address might be
         * @param blockCacheSets - The vector that stores the sets that will be replaced
         */
        void readFIFO(Cache <T> &cache, Memory <T> &memory,
                       T &blockCache, T &blockMemory, T &word,
                       T &begin, T &end, bool &state, T &sizeWay,
                       T &blockWay, std::vector<T> &blockCacheSets) {
            /// Search inside the cache
            state = findWord(cache, word, blockCache,
                             begin, end);

            if (state) {
                std::cout << "HIT - Linha " << blockCache
                          << std::endl;
                state = false;
            } else {
                changeBlocks(memory, cache,
                             (begin + blockCacheSets[blockWay] % sizeWay),
                             blockMemory);
                std::cout << "MISS - Alocado na linha "
                          << (begin + blockCacheSets[blockWay] % sizeWay)
                          << " - Bloco " << blockMemory
                          << " substituído." << std::endl;
                blockCacheSets[blockWay] = blockCacheSets[blockWay] + 1;
            }
        }

        /**
         * Writes in the passed address the passed content
         *
         * @param cache - The cache that it's been used
         * @param memory - The main memory that it's been used
         * @param blockCache - The auxilliar variable to find in what 
         *  block of the cache the word might be
         * @param blockMemory - The auxilliar variable to find in what 
         *  block of the memory the word might be
         * @param word - The word that must been find
         * @param begin - The position where the block begins
         * @param end - The position where the block ends
         * @param state - True if it finds the word and False when not
         * @param sizeWay - The size of the way of where the address might be
         * @param blockWay - The block of where the address might be
         * @param blockCacheSets - The vector that stores the sets that will be replaced
         * @param content - The new value to be stored
         */
        void writeFIFO(Cache <T> &cache, Memory <T> &memory,
                        T &blockCache, T &blockMemory, T &word,
                        T &begin, T &end, bool &state, T &sizeWay,
                        T &blockWay, std::vector<T> &blockCacheSets,
                        T &content) {
            /// Search inside the cache
            state = findWord(cache, word, blockCache,
                             begin, end);

            if (state) {
                std::cout << "HIT - Linha " << blockCache
                          << " - Novo valor do endereço "
                          << word << " = " << content
                          << std::endl;
                state = false;
            } else {
                changeBlocks(memory, cache,
                             (begin + blockCacheSets[blockWay] % sizeWay),
                             blockMemory);
                std::cout << "MISS - Alocado na linha "
                          << (begin + blockCacheSets[blockWay] % sizeWay)
                          << " - Bloco " << blockMemory
                          << " substituído." << std::endl;
                blockCacheSets[blockWay] = blockCacheSets[blockWay] + 1;
            }
        }

        /**
         * Searches in the cache the passed word
         *
         * @param cache - The cache that it's been used
         * @param memory - The main memory that it's been used
         * @param blockCache - The auxilliar variable to find in what 
         *  block of the cache the word might be
         * @param blockMemory - The auxilliar variable to find in what 
         *  block of the memory the word might be
         * @param word - The word that must been find
         * @param begin - The position where the block begins
         * @param end - The position where the block ends
         * @param state - True if it finds the word and False when not
         * @param sizeWay - The size of the way of where the address might be
         * @param blockWay - The block of where the address might be
         * @param blockCacheSets - The vector that stores the sets that will be replaced
         */
        void readLFU(Cache <T> &cache, Memory <T> &memory,
                      T &blockCache, T &blockMemory, T &word,
                      T &begin, T &end, bool &state, T &sizeWay,
                      T &blockWay, std::vector<T> &blockCacheSets) {
            /// Search inside the cache
            state = findWord(cache, word, blockCache,
                             begin, end);

            if (state) {
                std::cout << "HIT - Linha "
                          << blockCache << std::endl;
                cache.count[blockCache] = cache.count[blockCache] + 1;
                state = false;
            } else {
                state = findWord(cache, -1, blockCache,
                                 begin, end);

                if (state) {
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                    cache.count[blockCache] = 1;
                } else {
                    blockCache = cache.findLeastFrequentlyUsed(cache);
                    changeBlocks(memory, cache,
                                  blockCache, blockMemory);
                    cache.count[blockCache] = 1;
                }
                std::cout << "MISS - Alocado na linha "
                          << blockCache << " - Bloco "
                          << blockMemory << " substituído."
                          << std::endl;
            }
        }

        /**
         * Writes in the passed address the passed content
         *
         * @param cache - The cache that it's been used
         * @param memory - The main memory that it's been used
         * @param blockCache - The auxilliar variable to find in what 
         *  block of the cache the word might be
         * @param blockMemory - The auxilliar variable to find in what 
         *  block of the memory the word might be
         * @param word - The word that must been find
         * @param begin - The position where the block begins
         * @param end - The position where the block ends
         * @param state - True if it finds the word and False when not
         * @param sizeWay - The size of the way of where the address might be
         * @param blockWay - The block of where the address might be
         * @param blockCacheSets - The vector that stores the sets that will be replaced
         * @param content - The new value to be stored
         */
        void writeLFU(Cache <T> &cache, Memory <T> &memory,
                       T &blockCache, T &blockMemory, T &word,
                       T &begin, T &end, bool &state, T &sizeWay,
                       T &blockWay, std::vector<T> &blockCacheSets,
                       T &content) {
            /// Search inside the cache
            state = findWord(cache, word, blockCache,
                             begin, end);

            if (state) {
                std::cout << "HIT - Linha " << blockCache
                          << " - Novo valor do endereço "
                          << word << " = " << content
                          << std::endl;
                cache.count[blockCache] = cache.count[blockCache] + 1;
                state = false;
            } else {
                state = findWord(cache, -1, blockCache,
                                 begin, end);

                if (state) {
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                    cache.count[blockCache] = 1;
                } else {
                    blockCache = cache.findLeastFrequentlyUsed(cache);
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                    cache.count[blockCache] = 1;
                }
                std::cout << "MISS - Alocado na linha "
                          << blockCache << " - Bloco "
                          << blockMemory << " substituído."
                          << std::endl;
            }
        }

        /**
         * Searches in the cache the passed word
         *
         * @param cache - The cache that it's been used
         * @param memory - The main memory that it's been used
         * @param blockCache - The auxilliar variable to find in what 
         *  block of the cache the word might be
         * @param blockMemory - The auxilliar variable to find in what 
         *  block of the memory the word might be
         * @param word - The word that must been find
         * @param begin - The position where the block begins
         * @param end - The position where the block ends
         * @param state - True if it finds the word and False when not
         * @param sizeWay - The size of the way of where the address might be
         * @param blockWay - The block of where the address might be
         * @param blockCacheSets - The vector that stores the sets that will be replaced
         */
        void readLRU(Cache <T> &cache, Memory <T> &memory,
                      T &blockCache, T &blockMemory, T &word,
                      T &begin, T &end, bool &state, T &sizeWay,
                      T &blockWay, std::vector<T> &blockCacheSets) {
            /// Search inside the cache
            state = findWord(cache, word, blockCache,
                             begin, end);

            if (state) {
                std::cout << "HIT - Linha " << blockCache
                          << std::endl;
                cache.count[blockCache] = -1;
                state = false;
            } else {
                state = findWord(cache, -1, blockCache,
                                 begin, end);

                if (state) {
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                    cache.count[blockCache] = -1;
                } else {
                    blockCache = cache.findLeastRecentlyUsedSets(cache, begin, end);
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                    cache.count[blockCache] = -1;
                }
                std::cout << "MISS - Alocado na linha "
                          << blockCache << " - Bloco "
                          << blockMemory << " substituído."
                          << std::endl;
            }

            cache.changeLeastRecentlyUsedSets(cache, begin, end);
        }

        /**
         * Writes in the passed address the passed content
         *
         * @param cache - The cache that it's been used
         * @param memory - The main memory that it's been used
         * @param blockCache - The auxilliar variable to find in what 
         *  block of the cache the word might be
         * @param blockMemory - The auxilliar variable to find in what 
         *  block of the memory the word might be
         * @param word - The word that must been find
         * @param begin - The position where the block begins
         * @param end - The position where the block ends
         * @param state - True if it finds the word and False when not
         * @param sizeWay - The size of the way of where the address might be
         * @param blockWay - The block of where the address might be
         * @param blockCacheSets - The vector that stores the sets that will be replaced
         * @param content - The new value to be stored
         */
        void writeLRU(Cache <T> &cache, Memory <T> &memory,
                       T &blockCache, T &blockMemory, T &word,
                       T &begin, T &end, bool &state, T &sizeWay,
                       T &blockWay, std::vector<T> &blockCacheSets,
                       T &content) {
            state = findWord(cache, word, blockCache,
                             begin, end);

            if (state) {
                std::cout << "HIT - Linha " << blockCache
                          << " - Novo valor do endereço "
                          << word << " = " << content
                          << std::endl;
                cache.count[blockCache] = -1;
                state = false;
            } else {
                state = findWord(cache, -1, blockCache,
                                 begin, end);

                if (state) {
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                    cache.count[blockCache] = -1;
                } else {
                    blockCache = cache.findLeastRecentlyUsedSets(cache, begin, end);
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                    cache.count[blockCache] = -1;
                }
                std::cout << "MISS - Alocado na linha "
                          << blockCache  << " - Bloco "
                          << blockMemory << " substituído."
                          << std::endl;
            }

            cache.changeLeastRecentlyUsedSets(cache, begin, end);
        }

        /**
         * Reads the instruction
         *
         * @param cache - The cache that it's been used
         * @param memory - The main memory that it's been used
         * @param blockMemory - The auxilliar variable to find in what 
         *  block of the memory the word might be
         * @param word - The word that must been find
         * @param found - Gets the size of the string to determine
         *  if there is an instruction or not
         * @param instruction - The instruction passed by the user
         * @param commandAux - An auxilliar vector to help separate the instruction
         */
        void readInstruction(Cache <T> &cache, Memory <T> &memory,
                              T &begin, T &end, T &blockMemory, T &word,
                              std::size_t found, std::string &instruction,
                              std::vector<std::string> &commandAux,
                              T &sizeWay, T &blockWay) {
            found = instruction.find(" ");

            if (found != std::string::npos) {
                std::istringstream buf(instruction);
                std::istream_iterator <std::string> beg(buf), end;
                std::vector<std::string> commandAuxTemp(beg, end);
                commandAux = commandAuxTemp;
                instruction = commandAux[0];
                word = std::stoi(commandAux[1]);
            }

            blockMemory = word / memory.wordsPerBlocks;
            sizeWay = cache.lines / memory.setSize;
            blockWay = blockMemory % memory.setSize;
            begin = (blockWay * sizeWay);
            end = begin + sizeWay;
        }
};

#endif  // INCLUDE_SETASSOCIATIVE_H_
