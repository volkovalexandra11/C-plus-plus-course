//
// Created by alexa on 24.11.2021.
//

#ifndef WEEK3_RECTANGLE_H
#define WEEK3_RECTANGLE_H


class Rectangle {
public:
	Rectangle(int width, int height);

	int GetArea() const;
	int GetPerimeter() const;
	int GetWidth() const;
	int GetHeight() const;

private:
	int width_, height_;
};


#endif //WEEK3_RECTANGLE_H
