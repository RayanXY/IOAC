/**
 * @file memory.h
 * @author Rayan Avelino
 * @copyright 2018 Rayan Avelino
 */
#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

#include <iostream>
#include <vector>

/**
 * @class Memory
 *
 * This class represents a simple Main Memory of a computer
 * where the data will be stored.
 */
template <typename T> class Memory {
 public:
        T wordsPerBlocks, memorySize, mapping, setSize, replacementPolicy;

        std::vector< std::vector<T> > elements;
        /* 
         * Creates the Memory
         * @param memory - The Main Memory
         */
        void createMemory(Memory <T> &memory) {
            std::vector<T> aux;

            for (int i = 0; i < (memory.wordsPerBlocks * memory.memorySize); i++) {
                for (int j = 0; j < memory.wordsPerBlocks; j++, i++) {
                    aux.push_back(i);
                }
                memory.elements.push_back(aux);
                aux.clear();
                i--;
            }
        }

        /* 
         * Show the current state of the Memory
         * @param memory - The Main Memory
         */
        void showMemory(Memory <T> &memory) {
            std::cout << ">>> MEMÓRIA PRINCIPAL" << std::endl;
            std::cout << "Bloco\tEndereço" << std::endl;

            for (size_t i = 0; i < memory.elements.size(); i++) {
                for (int j = 0; j < memory.wordsPerBlocks; j++) {
                    std::cout << i << "\t"
                              << memory.elements[i][j] << std::endl;
                }
            }
            std::cout << std::endl;
        }
};

#endif  // INCLUDE_MEMORY_H_
