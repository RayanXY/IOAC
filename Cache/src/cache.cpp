#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Cache {

	private: 
		int block_size, lines, main_memory, mapping, set, replacement_policy;

	public:
		Cache (std::string file_name) {

			int i = 0;
			std::string line;
			std::ifstream file;

			file.open (file_name);

			if (file.fail ()) {
				std::cout << "Unable to open the file.\n";
			}

			while (getline (file, line)) {

				/// Block Size
				if (i == 0) {
					block_size = std::stoi (line);
				}
				/// Number of lines
				if (i == 1) {
					lines = std::stoi (line);
				}
				/// Number of block in the Main Memory
				if (i == 2) {
					main_memory = std::stoi (line);
				}
				/// Mapping
				if (i == 3) {
					mapping = std::stoi (line);
				}
				/// Number of Set (Set-Associative Mapping only)
				if (i == 4) {
					set = std::stoi (line);
				}
				/// Replacement Policy
				if (i == 5) {
					replacement_policy = std::stoi (line);
				}

				i++;

			}

			file.close ();

		}



		/// Show the configuration
		void showConfig () {

			std::cout << ">>> CONFIGURATION FILE <<<" << std::endl;
			std::cout << "Block Size: " << block_size << std::endl;
			std::cout << "Number of lines: " << lines << std::endl;
			std::cout << "Blocks in the Main Memory: " << main_memory << std::endl;
			std::cout << "Mapping: " << mapping << std::endl;
			std::cout << "Set: " << set << std::endl;
			std::cout << "Replacement Policy: " << replacement_policy << std::endl;

		}
		
};



/*






void readConfiguration () {

	std::string line;
	std::ifstream file;

	file.open ("./data/config.txt");

	if (file.fail ()){
		std::cout << "Unable to open the file.\n";
	}

	while (getline (file, line)) {

		std::cout << line << std::endl;

	}

	file.close ();

}
*/