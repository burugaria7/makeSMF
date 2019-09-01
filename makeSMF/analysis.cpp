#include "Analysis.hpp"

void Analysis::Set_Coodinates()
{

	//720p 88key
	if (movie.Get_Set().Get_Mode() == 2) {

		//white

		this->key_white_y = 680;

		for (int i = 0; i < 52; i++) {
			this->key_white_x[i] = (24.5 / 2.0) * (i + 1);
		}

		//black



	}

}
