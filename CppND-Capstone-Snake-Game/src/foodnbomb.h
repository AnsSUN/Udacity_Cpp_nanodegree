#ifndef FOODNBOMB_H
#define FOODNBOMB_H

#include <vector>
#include <memory>
#include <SDL.h>
#include <string>

class Display_entity{
	virtual void Display_on_screen(std::string info) const = 0;
};
//flaging type of object in the space (food and bomb) 
enum class Flag_type {red, green};
class FoodnBomb : Display_entity{
public:
	std::string Checkflag();
	void Setflag(Flag_type flagd);
	void Count();
	int GetCount();
	void Distroy();
	void Display_on_screen(std::string info) const;

	SDL_Point food_body;
	SDL_Point bomb_body;

private:
	Flag_type _flag_type;
	int _count = 0;
	int _count_food = 0;
	int _count_bomb = 0;
	std::string _msg;

};

#endif
