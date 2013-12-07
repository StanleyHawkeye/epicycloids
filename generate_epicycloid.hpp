/**
 * $Id$
 * Function generating points of an epicycloid according to the formula
 *  a = n/m
 *  r = a√((m+1)(m+1-2 sin(½π + mφ))+1)
 *
 *
 * Licensed under The MIT License (MIT)
 *
 * Copyright (C) 2013 Stanley Hawkeye
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef GENERATE_EPICYCLOID_HPP_
#define GENERATE_EPICYCLOID_HPP_

#include <vector>
#include <opencv2/core/core.hpp>

/**
 * @brief Generates points of an epicycloid according to the formula
 *  a = n/m
 *  r = a√((m+1)(m+1-2 sin(½π + mφ))+1)
 *
 * @param points The vector of points where the points of the epicycloid are to be stored
 * @param n The n from the formula
 * @param m The m from the formula
 * @param step The step for φ
 *
 */
void generate_epicycloid(std::vector<cv::Point2f>& points, int numerator, int denominator, float step);

#endif /* GENERATE_EPICYCLOID_HPP_ */
