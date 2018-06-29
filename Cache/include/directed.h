/**
 * @file directed.h
 * @author Rayan Avelino
 * @copyright 2018 Rayan Avelino
 */
#ifndef INCLUDE_DIRECTED_H_
#define INCLUDE_DIRECTED_H_

/**
 * @class Directed
 *
 * This class contains a set of funtions that will simulate
 * the directed mapped cache.
 */
template <typename T> class Directed {
 public:
        /**
         * Searches in the cache the passed word
         *
         * @param cache - The cache that it's been used
         * @param memory - The main memory that it's been used
         * @param blockCache - The auxilliar variable to find in what 
         * block of the cache the word might be
         * @param blockMemory - The auxilliar variable to find in what 
         * block of the memory the word might be
         * @param word - The word that must been find
         * @param rest - An auxilliar variable
         */
        void read(Cache <T> &cache, Memory <T> &memory, T blockCache,
                  T blockMemory, T word, T rest) {
            /// Defines where to store the command
            blockCache = (word / memory.wordsPerBlocks) % cache.lines;
            blockMemory = word / memory.wordsPerBlocks;
            rest = word % memory.wordsPerBlocks;

            if (cache.elements[blockCache][rest] == word) {
                std::cout << "HIT - Linha " << blockCache << std::endl;
            } else {
                std::cout << "MISS - Alocado na linha " << blockCache <<
                             " - Bloco " << blockMemory <<
                             " substituído." << std::endl;
                changeBlocks(memory, cache, blockCache, blockMemory);
            }
        }

        /**
         * Writes in the passed address the passed content
         *
         * @param cache - The cache that it's been used
         * @param memory - The main memory that it's been used
         * @param blockCache - The auxilliar variable to find in what 
         * block of the cache the word might be
         * @param blockMemory - The auxilliar variable to find in what 
         * block of the memory the word might be
         * @param word - The word that must been find
         * @param rest - An auxilliar variable
         */
        void write(Cache <T> &cache, Memory <T> &memory,
                   T blockCache, T blockMemory, T word, T rest) {
            /// Defines where to store the command
            blockCache = (word / memory.wordsPerBlocks) % cache.lines;
            blockMemory = word / memory.wordsPerBlocks;
            rest = word % memory.wordsPerBlocks;

            if (cache.elements[blockCache][rest] == word) {
                std::cout << "HIT - Linha " << blockCache << std::endl;
            } else {
                std::cout << "MISS - Alocado na linha " << blockCache <<
                             " - Bloco " << blockMemory <<
                             " substituído." << std::endl;
                changeBlocks(memory, cache, blockCache, blockMemory);
            }
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
                             T begin, T end, T blockMemory, T word,
                             std::size_t found, std::string instruction,
                             std::vector<std::string> commandAux) {
            found = instruction.find(" ");

            if (found != std::string::npos) {
                std::istringstream buf(instruction);
                std::istream_iterator <std::string> beg(buf), end;
                std::vector<std::string> commandAuxTemp(beg, end);
                commandAux = commandAuxTemp;
                instruction = commandAux[0];
                word = std::stoi(commandAux[1]);
            }
        }
};

#endif  // INCLUDE_DIRECTED_H_
