#include "foodnbomb.h"
#include <iostream>


std::string FoodnBomb::Checkflag(){
	if(_flag_type == Flag_type::green){
		_msg = "Snake eat food, increase the snake size and score!";
	}
	else{
		_msg = "Snake hit the bomb, this reduce the snake size and score to by 4!";
	}
	return _msg;
}

void FoodnBomb:: Display_on_screen(std::string info) const{
	std::cout<< info<< "\n";
}

void FoodnBomb:: Setflag(Flag_type flagd){
	_flag_type = flagd;
}

void FoodnBomb:: Count(){
	++_count;
	++_count_food;
	++_count_bomb;
}

int FoodnBomb:: GetCount(){
	return _count;
}

void FoodnBomb:: Distroy(){
	--_count;
}
