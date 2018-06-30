/**
 * @file fully.h
 * @author Rayan Avelino
 * @copyright 2018 Rayan Avelino
 */
#ifndef INCLUDE_FULLY_H_
#define INCLUDE_FULLY_H_

/**
 * @class Fully
 *
 * This class contains a set of funtions that will simulate
 * the fully associative mapped cache.
 */
template <typename T> class Fully {
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

            if (state == true) {
                std::cout << "HIT - Linha " <<
                              blockCache << std::endl;
                state = false;
            /// Find the first available position in the cache
            } else {
                state = findWord(cache, -1, blockCache,
                                 begin, end);

                if (state == true) {
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                } else {
                    srand(time(NULL));
                    blockCache = rand() % cache.lines;
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                }

                std::cout << "MISS - Alocado na linha " <<
                             blockCache << " - Bloco " <<
                             blockMemory <<" substituído."
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
                std::cout << "HIT - Linha " << blockCache <<
                             " - Novo valor do endereço " <<
                             word << " = " << content
                             << std::endl;
                state = false;
            /// Find the first available position in the cache
            } else {
                state = findWord(cache, -1, blockCache,
                                 begin, end);

                if (state) {
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                } else {
                    srand(time(NULL));
                    blockCache = rand() % cache.lines;
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                }
                std::cout << "MISS - Alocado na linha " <<
                             blockCache << " - Bloco " <<
                             blockMemory << " substituído."
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
         * @param blockCacheAux - An auxilliar variable that helps with new address in the cache
         */
        void readFIFO(Cache <T> &cache, Memory <T> &memory,
                       T &blockCache, T &blockMemory, T &word,
                       T &begin, T &end, bool &state, T &blockCacheAux) {
            /// Search inside the cache
            state = findWord(cache, word, blockCache,
                             begin, end);

            if (state == true) {
                std::cout << "HIT - Linha " << blockCache
                          << std::endl;
                state = false;
            } else {
                changeBlocks(memory, cache,
                             blockCacheAux % cache.lines,
                             blockMemory);
                std::cout << "MISS - Alocado na linha "
                          << (blockCacheAux % cache.lines)
                          << " - Bloco " << blockMemory
                          << " substituído." << std::endl;
                blockCacheAux = blockCacheAux + 1;
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
         * @param blockCacheAux - An auxilliar variable that helps with new address in the cache
         */
        void writeFIFO(Cache <T> &cache, Memory <T> &memory,
                        T &blockCache, T &blockMemory, T &word,
                        T &begin, T &end, bool &state,
                        T &content, T &blockCacheAux) {
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
                             blockCacheAux % cache.lines,
                             blockMemory);
                std::cout << "MISS - Alocado na linha "
                          << (blockCacheAux % cache.lines)
                          << " - Bloco " << blockMemory
                          << " substituído." << std::endl;
                blockCacheAux = blockCacheAux + 1;
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
         */
        void readLFU(Cache <T> &cache, Memory <T> &memory,
                      T &blockCache, T &blockMemory, T &word,
                      T &begin, T &end, bool &state) {
            /// Search inside the cache
            state = findWord(cache, word, blockCache,
                             begin, end);

            if (state == true) {
                std::cout << "HIT - Linha "
                          << blockCache << std::endl;
                cache.count[blockCache] = cache.count[blockCache] + 1;
                state = false;
            } else {
                state = findWord(cache, -1, blockCache,
                                 begin, end);

                if (state == true) {
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
         * @param content - The new value to be stored
         */
        void writeLFU(Cache <T> &cache, Memory <T> &memory,
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
         */
        void readLRU(Cache <T> &cache, Memory <T> &memory,
                      T &blockCache, T &blockMemory, T &word,
                      T &begin, T &end, bool &state) {
            /// Search inside the cache
            state = findWord(cache, word, blockCache,
                              begin, end);

            if (state == true) {
                std::cout << "HIT - Linha "
                          << blockCache << std::endl;
                cache.count[blockCache] = -1;
                state = false;
            } else {
                state = findWord(cache, -1, blockCache,
                                 begin, end);

                if (state == true) {
                    changeBlocks(memory, cache,
                                 blockCache, blockMemory);
                    cache.count[blockCache] = -1;
                } else {
                    blockCache = cache.findLeastRecentlyUsed(cache);
                    changeBlocks(memory, cache,
                                  blockCache, blockMemory);
                    cache.count[blockCache] = -1;
                }
                std::cout << "MISS - Alocado na linha "
                          << blockCache << " - Bloco "
                          << blockMemory << " substituído."
                          << std::endl;
            }

            cache.changeLeastRecentlyUsed(cache);
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
        void writeLRU(Cache <T> &cache, Memory <T> &memory,
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
                    blockCache = cache.findLeastRecentlyUsed(cache);
                    changeBlocks(memory, cache,
                                  blockCache, blockMemory);
                    cache.count[blockCache] = -1;
                }
                std::cout << "MISS - Alocado na linha "
                          << blockCache << " - Bloco "
                          << blockMemory << " substituído."
                          << std::endl;
            }

            cache.changeLeastRecentlyUsed(cache);
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
                              std::size_t &found, std::string &instruction,
                              std::vector<std::string> &commandAux) {
            begin = 0;
            end = cache.elements.size();
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
        }
};

#endif  // INCLUDE_FULLY_H_
