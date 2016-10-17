/*
 * calc.h
 *
 *  Created on: 30.09.2016
 *      Author: hsr
 */

#ifndef CALC_H_
#define CALC_H_

#include <iosfwd>

int calc(int lhs, int rhs , char op);

int calc(std::istream& in);

#endif /* CALC_H_ */
