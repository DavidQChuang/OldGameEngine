#include "stdafx.h"
#include "Options.h"

int Options::Scene = 0;
int Options::WIDTH = 800;
int Options::HEIGHT = 600;
Options::Options() {
}

void Options::SetDefaults() {
	config.open("settings.cfg");

}

int Options::GetOptionI(std::string key) {
	struct stat buf;
	//The requested key
	const char *ckey = key.c_str();
	//The file key
	const char *cfkey;

	config.open("settings.cfg");

	if (stat("settings.cfg", &buf) != -1) {
		std::string line;
		while (std::getline(config, line)) {
			std::istringstream is_line(line);
			//Name of variable in the line
			std::string fkey;
			if (std::getline(is_line, fkey, '=')) {
				//Value of variable in the line
				std::string fvalue;
				if (std::getline(is_line, fvalue)) {
					//Name of variable in the line converted to char
					cfkey = fkey.c_str();
					//If the line's key equals the requested key
					if (cfkey == ckey) {
						config.close();
						return atoi(fvalue.c_str());
					}
				}
			}
		}
		config.close();
		return false;
	}
	else {
		SetDefaults();
		return false;
	}
	config.close();
}
float Options::GetOptionF(std::string key) {
	struct stat buf;
	//The requested key
	const char *ckey = key.c_str();
	//The file key
	const char *cfkey;

	config.open("settings.cfg");

	if (stat("settings.cfg", &buf) != -1) {
		std::string line;
		while (std::getline(config, line)) {
			std::istringstream is_line(line);
			//Name of variable in the line
			std::string fkey;
			if (std::getline(is_line, fkey, '=')) {
				//Value of variable in the line
				std::string fvalue;
				if (std::getline(is_line, fvalue)) {
					//Name of variable in the line converted to char
					cfkey = fkey.c_str();
					//If the line's key equals the requested key
					if (cfkey == ckey) {
						config.close();
						return atof(fvalue.c_str());
					}
				}
			}
		}
		config.close();
		return -1;
	}
	else {
		SetDefaults();
		return false;
	}
	config.close();
}
bool Options::GetOptionB(std::string key) {
	struct stat buf;
	//The requested key
	const char *ckey = key.c_str();
	//The file key
	const char *cfkey;

	config.open("settings.cfg");

	if (stat("settings.cfg", &buf) != -1) {
		std::string line;
		while (std::getline(config, line)) {
			std::istringstream is_line(line);
			//Name of variable in the line
			std::string fkey;
			if (std::getline(is_line, fkey, '=')) {
				//Value of variable in the line
				std::string fvalue;
				if (std::getline(is_line, fvalue)) {
					//Name of variable in the line converted to char
					cfkey = fkey.c_str();
					//If the line's key equals the requested key
					if (cfkey == ckey) {
						config.close();
						return (std::string("true") == fvalue);
					}
				}
			}
		}
		config.close();
		return false;
	}
	else {
		SetDefaults();		
		return false;
	}
	config.close();
}

void Options::SetOption(std::string key, std::string value) {
	struct stat buf;
	//The requested key.
	const char *ckey = key.c_str();
	//The key in the file.
	const char *cfkey;

	config.open("settings.cfg");

	if (stat("settings.cfg", &buf) != -1) {
		//If settings.cfg exists
		std::string line;
		while (std::getline(config, line)) {
			std::istringstream is_line(line);
			//Name of variable in the line
			std::string fkey;
			if (std::getline(is_line, fkey, '=')) {
				//Value of variable in the line
				std::string fvalue;
				if (std::getline(is_line, fvalue)) {
					//Name of variable in the line converted to char
					cfkey = fkey.c_str();
					//If the line's key equals the requested key
					if (cfkey == ckey) {
						fvalue = value;
					}
				}
			}
		}
	}
	else {

	}
	config.close();
}