#pragma once
#include "./LevelBuilder.h"
#include <Engine\FileParser\FileLoader.h>
#include <nlohmann\json.hpp>

class LevelOneBuilder : public LevelBuilder {
public:
	LevelOneBuilder(Engine& _engine) : LevelBuilder(_engine) { }

	virtual void create() override {
		FileLoader p;

		auto filestream = p.readFile("C:\\Users\\thijs\\Downloads\\Level 1 - Simple.json");
		nlohmann::json j;
		filestream >> j;
		filestream.close();

		// even easier with structured bindings (C++17)
		for (auto& [key, value] : j.items()) {
			std::cout << key << " : " << value << "\n";
		}

	}
};


