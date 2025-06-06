#include <vector>
#include <iostream>

const std::string red = "\033[31m";
const std::string green = "\033[32m";
const std::string yellow = "\033[33m";
const std::string blue = "\033[34m";
const std::string magenta = "\033[35m";
const std::string cyan = "\033[36m";
const std::string white = "\033[37m";
const std::string reset = "\033[0m";

std::vector<std::string> logo{
"                                    ",
	"     /\\                             ",
	"    /  \\   _ __ __ ___  ___   _ ___ ",
	"   / /\\ \\ | '__/ _` \\ \\/ / | | / __|",
	"  / ____ \\| | | (_| |>  <| |_| \\__ \\",
	" /_/    \\_\\_|  \\__,_/_/\\_\\\\__, |___/",
	"                           __/ |    ",
	"                          |___/     "
};


void print_header(void)
{
	for (const auto& line : logo)
		std::cout << magenta << line << std::endl;
	std::cout << yellow << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
}