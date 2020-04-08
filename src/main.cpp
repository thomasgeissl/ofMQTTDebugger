#include "ofAppNoWindow.h"
#include "ofApp.h"
#include <iostream>
#include "ofxCommandLineUtils.h"

std::string getAbsolutePath(std::string path)
{
	filesystem::path exePath = filesystem::current_path();

	if (!ofFilePath::isAbsolute(path))
	{
		path = ofFilePath::join(exePath, path);
	}
	return path;
}

cxxopts::ParseResult parse(int argc, char *argv[])
{
	try
	{
		cxxopts::Options options(argv[0], " - MQTT publisher and subscriber");
		options.add_options()("h,host", "host", cxxopts::value<std::string>()->default_value("localhost"))("p,port", "port", cxxopts::value<int>()->default_value("1883"))("o,output", "output", cxxopts::value<std::string>())("i,interactive", "interactive")("j,input", "input", cxxopts::value<std::string>())("m,message", "message", cxxopts::value<std::string>())("t,topic", "topic", cxxopts::value<std::string>());
		auto result = options.parse(argc, argv);
		return result;
	}
	catch (const cxxopts::OptionException &e)
	{
		std::cout << "error parsing options: " << e.what() << std::endl;
		exit(1);
	}
}

int main(int argc, char *argv[])
{
	auto result = parse(argc, argv);
	auto arguments = result.arguments();

	ofAppNoWindow window;
	ofSetupOpenGL(&window, 0, 0, OF_WINDOW);

	if (result.count("message") > 0)
	{
		auto message = result["message"].as<std::string>();
		std::string singleQuote = "'";
		std::string doubleQuote = "\"";

		size_t pos;
		while ((pos = message.find(singleQuote)) != std::string::npos)
		{
			message.replace(pos, 1, doubleQuote);
		}
		auto app = new ofApp(result["host"].as<std::string>(), result["port"].as<int>(), result["topic"].as<std::string>(), message);
		ofRunApp(app);
	}
	else
	{
		auto app = new ofApp(result["host"].as<std::string>(), result["port"].as<int>(), result["topic"].as<std::string>());
		ofRunApp(app);
	}
	return 0;
}
