#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>

int main (int argc, char * argv[]) {

	std::string instruction, command;
	int a, b;

	std::getline(std::cin, instruction);

	//std::cout << "Entrada: " << instruction << std::endl;

	std::istringstream buf(instruction);
	std::istream_iterator <std::string> beg(buf), end;

	std::vector<std::string> v (beg, end);

	//std::cout << "v.size = " << v.size () << std::endl;	

	command = v[0];
	a = std::stoi (v[1]);
/*
	std::cout << "v[0] = " << v[0] << std::endl;
	std::cout << "v[1] = " << v[1] << std::endl;
	std::cout << "v[2] = " << v[2] << std::endl;

*/
	std::cout << command << std::endl;
	std::cout << a << std::endl;
	//std::cout << b << std::endl;

/*
	std::string instruction, aux;
	int word = 0, content = 0;
	std::size_t found;

	while (std::getline (std::cin, instruction)) {

		/// Search for a space in the command
		found = instruction.find (" ");

		//std::cout << found << std::endl;
		/// If it finds it, splits the command
		if (found != std::string::npos) {
			aux = instruction.substr (found + 1);
			instruction = instruction.substr (0, found);
		}

		if (instruction.compare("Read") == 0){
			word = std::stoi (aux);
			std::cout << "Instrução: " << instruction << std::endl;
			std::cout << "Endereço: " << word << std::endl;
		}

		if (instruction.compare("Write") == 0){
			
			found = aux.find (" ");

			if (found != std::string::npos) {
				content = std::stoi (aux.substr (found + 1));
				word = std::stoi (aux.substr (0, found));
			}

			std::cout << "Instrução: " << instruction << std::endl;
			std::cout << "Endereço: " << word << std::endl;
			std::cout << "Conteúdo: " << content << std::endl;

		}

	}

}


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
*/
}