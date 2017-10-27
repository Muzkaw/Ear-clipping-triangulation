//This file is part of Ear clipping triangulation(GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <cmath>

using namespace std ;
using namespace sf ;

float determinant(Vector2f u, Vector2f v) ;
float Distance(Vector2f const& v1, Vector2f const& v2) ;
bool collisionTrianglePoint(Vector2f a, Vector2f b, Vector2f c, Vector2f point) ;
vector<Vector2f> triangulate(vector<Vector2f> points) ;