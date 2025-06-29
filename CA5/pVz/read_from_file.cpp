#include "functions.h"


void Read_From_File(std::vector<float> &options,std::string file_path)
{
	std::fstream fin;
	fin.open(file_path,std::ios::in);

	std::string option_str;
	std::string temp_str;
	getline(fin,temp_str);
	getline(fin,temp_str);
	std::stringstream S(temp_str);
	while(getline(S,option_str,ACTION_OPTION_SEPRATOR))
	{
		options.push_back(std::stof(option_str));
	}
 
	fin.close();
}