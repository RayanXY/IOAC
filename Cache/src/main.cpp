/**
 * @file main.cpp
 * @author Rayan Avelino
 * @copyright 2018 Rayan Avelino
 */
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include "../include/cache.h"
#include "../include/directed.h"
#include "../include/fully.h"
#include "../include/setAssociative.h"

int main(int argc, char * argv[]) {
    /// Reads the configuratio file
    std::ifstream file;
    file.open("./data/Girao_DIRETO.txt");
    // file.open("./data/Girao_PARCIAL.txt");
    // file.open("./data/Girao_TOTAL.txt");

    /// Sets the parameters
    Memory <int> memory;
    Cache <int> cache;
    Directed <int> directed;
    Fully <int> fully;
    SetAssociative <int> set;

    file >> memory.wordsPerBlocks >> cache.lines >>
            memory.memorySize >> memory.mapping >>
            memory.setSize >> memory.replacementPolicy;

    cache.wordsPerBlocks = memory.wordsPerBlocks;

    /// Creates the objects
    memory.createMemory(memory);
    cache.createCache(cache);

    /// Variables
    std::string instruction, command;
    std::size_t found;
    int word = 0, content = 0, blockCache = 0,
        blockMemory = 0, rest = 0, sizeWay = 0,
        blockWay = 0, begin = 0, end = 0, blockCacheAux = 0;
    bool state = false;

    std::vector<std::string> commandAux;

    /// Counter for LFU and LRU policy
    std::vector<int> blockCacheSets(memory.setSize, 0);

    /// Using the mapping informed
    switch (memory.mapping) {
        /// Directed-Mapped
        case 1:
            /// Gets the commando from the user
            while (std::getline(std::cin, instruction)) {
                /// Gets the command
                directed.readInstruction(found, instruction,
                                         end, word, commandAux);
                /// Reading the command
                if (instruction.compare("Read") == 0) {
                    directed.read(cache, memory, blockCache,
                                  blockMemory, word, rest);
                } else if (instruction.compare("Write") == 0) {
                    directed.write(cache, memory, blockCache,
                                   blockMemory, word, rest);
                } else if (instruction.compare("Show") == 0) {
                    cache.showCache(cache, memory);
                    memory.showMemory(memory);
                }
            }
            break;
        /// Fully Associative
        case 2:
            switch (memory.replacementPolicy) {
                /// Random
                case 1:
                    while (std::getline(std::cin, instruction)) {
                        /// Gets the command
                        fully.readInstruction(cache, memory, begin, end,
                                              blockMemory, word, found,
                                              instruction, commandAux);
                        /// Reading the command
                        if (instruction.compare("Read") == 0) {
                            fully.readRandom(cache, memory, blockCache,
                                             blockMemory, word, begin,
                                             end, state);
                        } else if (instruction.compare("Write") == 0) {
                            content = std::stoi(commandAux[2]);
                            fully.writeRandom(cache, memory, blockCache,
                                              blockMemory, word, begin,
                                              end, state, content);
                        } else if (instruction.compare("Show") == 0) {
                            cache.showCache(cache, memory);
                            memory.showMemory(memory);
                        }
                    } break;
                /// FIFO
                case 2:
                    while (std::getline(std::cin, instruction)) {
                        /// Gets the command
                        fully.readInstruction(cache, memory, begin, end,
                                               blockMemory, word, found,
                                               instruction, commandAux);
                        /// Reading the command
                        if (instruction.compare("Read") == 0) {
                            fully.readFIFO(cache, memory, blockCache,
                                           blockMemory, word, begin,
                                           end, state, blockCacheAux);
                        } else if (instruction.compare("Write") == 0) {
                            content = std::stoi(commandAux[2]);
                            fully.writeFIFO(cache, memory, blockCache,
                                            blockMemory, word, begin,
                                            end, state, content, blockCacheAux);
                        } else if (instruction.compare("Show") == 0) {
                            cache.showCache(cache, memory);
                            memory.showMemory(memory);
                        }
                    } break;
                /// LFU
                case 3:
                    /// Initiate the counter for LFU Policy
                    for (int i = 0; i < cache.lines; i++) {
                        cache.count.push_back(0);
                    }
                    /// Gets the Instructions
                    while (std::getline(std::cin, instruction)) {
                        /// Gets the command
                        fully.readInstruction(cache, memory, begin, end,
                                              blockMemory, word, found,
                                              instruction, commandAux);
                        /// Reading the command
                        if (instruction.compare("Read") == 0) {
                            fully.readLFU(cache, memory, blockCache,
                                          blockMemory, word, begin,
                                          end, state);
                        } else if (instruction.compare("Write") == 0) {
                            content = std::stoi(commandAux[2]);
                            fully.writeLFU(cache, memory, blockCache,
                                           blockMemory, word, begin,
                                           end, state, content);
                        } else if (instruction.compare("Show") == 0) {
                            cache.showCache(cache, memory);
                            memory.showMemory(memory);
                        }
                    } break;
                /// LRU
                case 4:
                    /// Initiate the counter for LRU Policy
                    for (int i = 0; i < cache.lines; i++) {
                        cache.count.push_back(0);
                    }

                    while (std::getline(std::cin, instruction)) {
                        /// Gets the command
                        fully.readInstruction(cache, memory, begin, end,
                                              blockMemory, word, found,
                                              instruction, commandAux);
                        /// Reading the command
                        if (instruction.compare("Read") == 0) {
                            fully.readLRU(cache, memory, blockCache,
                                          blockMemory, word, begin, end, state);
                        } else if (instruction.compare("Write") == 0) {
                            content = std::stoi(commandAux[2]);
                            fully.writeLRU(cache, memory, blockCache,
                                           blockMemory, word, begin,
                                           end, state, content);
                        } else if (instruction.compare("Show") == 0) {
                            cache.showCache(cache, memory);
                            memory.showMemory(memory);
                        }
                    } break;
            } break;
        /// Set Associative
        case 3:
            switch (memory.replacementPolicy) {
                /// Random
                case 1:
                    while (std::getline(std::cin, instruction)) {
                        /// Gets the command
                        set.readInstruction(cache, memory, begin, end,
                                            blockMemory, word, found,
                                            instruction, commandAux,
                                            sizeWay, blockWay);
                        /// Reading the command
                        if (instruction.compare("Read") == 0) {
                            set.readRandom(cache, memory, blockCache,
                                           blockMemory, word, begin,
                                           end, state);
                        } else if (instruction.compare("Write") == 0) {
                            content = std::stoi(commandAux[2]);
                            set.writeRandom(cache, memory, blockCache,
                                            blockMemory, word, begin,
                                            end, state, content);
                        } else if (instruction.compare("Show") == 0) {
                            cache.showCache(cache, memory);
                            memory.showMemory(memory);
                        }
                    } break;
                /// FIFO
                case 2:
                    while (std::getline(std::cin, instruction)) {
                        /// Gets the command
                        set.readInstruction(cache, memory, begin,
                                            end, blockMemory, word,
                                            found, instruction, commandAux,
                                            sizeWay, blockWay);
                        /// Reading the command
                        if (instruction.compare("Read") == 0) {
                            set.readFIFO(cache, memory, blockCache,
                                         blockMemory, word, begin,
                                         end, state, sizeWay,
                                         blockWay, blockCacheSets);
                        } else if (instruction.compare("Write") == 0) {
                            content = std::stoi(commandAux[2]);
                            set.writeFIFO(cache, memory, blockCache,
                                          blockMemory, word, begin,
                                          end, state, sizeWay,
                                          blockWay, blockCacheSets, content);
                        } else if (instruction.compare("Show") == 0) {
                            cache.showCache(cache, memory);
                            memory.showMemory(memory);
                        }
                    } break;
                /// LFU
                case 3:
                    for (int i = 0; i < cache.lines; i++) {
                        cache.count.push_back(0);
                    }
                    while (std::getline(std::cin, instruction)) {
                        // Gets the command
                        set.readInstruction(cache, memory, begin, end,
                                            blockMemory, word, found,
                                            instruction, commandAux,
                                            sizeWay, blockWay);
                        /// Reading the command
                        if (instruction.compare("Read") == 0) {
                            set.readLFU(cache, memory, blockCache,
                                        blockMemory, word, begin,
                                        end, state, sizeWay,
                                        blockWay, blockCacheSets);
                        } else if (instruction.compare("Write") == 0) {
                            content = std::stoi(commandAux[2]);
                            set.writeLFU(cache, memory, blockCache,
                                         blockMemory, word, begin,
                                         end, state, sizeWay,
                                         blockWay, blockCacheSets, content);
                        } else if (instruction.compare("Show") == 0) {
                            cache.showCache(cache, memory);
                            memory.showMemory(memory);
                        }
                    } break;
                /// LRU
                case 4:
                    for (int i = 0; i < cache.lines; i++) {
                        cache.count.push_back(0);
                    }
                    while (std::getline(std::cin, instruction)) {
                        // Gets the command
                        set.readInstruction(cache, memory, begin, end,
                                            blockMemory, word, found,
                                            instruction, commandAux,
                                            sizeWay, blockWay);
                        /// Reading the command
                        if (instruction.compare("Read") == 0) {
                            set.readLRU(cache, memory, blockCache,
                                        blockMemory, word, begin,
                                        end, state, sizeWay,
                                        blockWay, blockCacheSets);
                        } else if (instruction.compare("Write") == 0) {
                            content = std::stoi(commandAux[2]);
                            set.writeLRU(cache, memory, blockCache,
                                         blockMemory, word, begin,
                                         end, state, sizeWay,
                                         blockWay, blockCacheSets, content);
                        } else if (instruction.compare("Show") == 0) {
                            cache.showCache(cache, memory);
                            memory.showMemory(memory);
                        }
                    } break;
            } break;
    }

    file.close();
    return 0;
}
