/*
 * Utility.cpp
 *
 *  Created on: Oct 22, 2019
 *      Author: cristi
 */

#include "Utility.h"

Utility::getRandomInt(int min, int max) {
	int value = rand() % (max-min +1) + min;
	return value;
}

