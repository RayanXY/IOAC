/**
 * @file tests.cpp
 * @author Rayan Avelino
 * @copyright 2018 Rayan Avelino
 */
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../include/cache.h"
#include "../include/memory.h"
/**
 * This test checks if the configuration file for the Directed Mapped it's read corretly
 * @SetTestName Cache_Config_Test - The name of the set of test which the code need to pass
 * @TestName Directed_Mapped_Config_Test - The name of this specific test
 */
TEST(Cache_Config_Test, Directed_Mapped_Config_Test) {
    /// Reads the file
    std::ifstream file;
    file.open("../data/Girao_DIRETO.txt");

    Memory <int> memory;
    Cache <int> cache;

    file >> memory.wordsPerBlocks >> cache.lines >>
            memory.memorySize >> memory.mapping >>
            memory.setSize >> memory.replacementPolicy;
    cache.wordsPerBlocks = memory.wordsPerBlocks;

    memory.createMemory(memory);
    cache.createCache(cache);

    ASSERT_EQ(4, memory.wordsPerBlocks);
    ASSERT_EQ(4, cache.wordsPerBlocks);
    ASSERT_EQ(4, cache.lines);
    ASSERT_EQ(14, memory.memorySize);
    ASSERT_EQ(1, memory.mapping);
    ASSERT_EQ(2, memory.setSize);
    ASSERT_EQ(4, memory.replacementPolicy);
}

/**
 * This test checks if the configuration file for the Fully Associative it's read corretly
 * @SetTestName Cache_Config_Test - The name of the set of test which the code need to pass
 * @TestName Fully_Associative_Config_Test - The name of this specific test
 */
TEST(Cache_Config_Test, Fully_Associative_Config_Test) {
    /// Reads the file
    std::ifstream file;
    file.open("../data/Girao_TOTAL.txt");

    Memory <int> memory;
    Cache <int> cache;

    file >> memory.wordsPerBlocks >> cache.lines >>
            memory.memorySize >> memory.mapping >>
            memory.setSize >> memory.replacementPolicy;
    cache.wordsPerBlocks = memory.wordsPerBlocks;

    memory.createMemory(memory);
    cache.createCache(cache);

    /// Test if the results are the same
    ASSERT_EQ(4, memory.wordsPerBlocks);
    ASSERT_EQ(4, cache.wordsPerBlocks);
    ASSERT_EQ(4, cache.lines);
    ASSERT_EQ(14, memory.memorySize);
    ASSERT_EQ(2, memory.mapping);
    ASSERT_EQ(2, memory.setSize);
    ASSERT_EQ(4, memory.replacementPolicy);
}

/**
 * This test checks if the configuration file for the Set Associative it's read corretly
 * @SetTestName Cache_Config_Test - The name of the set of test which the code need to pass
 * @TestName Set_Associative_Config_Test - The name of this specific test
 */
TEST(Cache_Config_Test, Set_Associative_Config_Test) {
    /// Reads the file
    std::ifstream file;
    file.open("../data/Girao_PARCIAL.txt");

    Memory <int> memory;
    Cache <int> cache;

    file >> memory.wordsPerBlocks >> cache.lines >>
            memory.memorySize >> memory.mapping >>
            memory.setSize >> memory.replacementPolicy;
    cache.wordsPerBlocks = memory.wordsPerBlocks;

    memory.createMemory(memory);
    cache.createCache(cache);

    /// Test if the results are the same
    ASSERT_EQ(4, memory.wordsPerBlocks);
    ASSERT_EQ(4, cache.wordsPerBlocks);
    ASSERT_EQ(4, cache.lines);
    ASSERT_EQ(14, memory.memorySize);
    ASSERT_EQ(3, memory.mapping);
    ASSERT_EQ(2, memory.setSize);
    ASSERT_EQ(3, memory.replacementPolicy);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
