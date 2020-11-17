#pragma once


class Savegame
{
public:
	static Savegame& get_instance() { return instance; }
	// prohibit copy & move
	Savegame(const Savegame&) = delete;
	Savegame(Savegame&&) = delete;
	Savegame& operator=(const Savegame&) = delete;
	Savegame& operator=(Savegame&&) = delete;

private:
	static Savegame instance;
	Savegame() {};
};



