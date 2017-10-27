/*********************************************************************

This file is part of Ear clipping triangulation (GNU GPL) - https://www.youtube.com/user/Muzkaw).

Ear clipping triangulation is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Ear clipping triangulation is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Ear clipping triangulation. If not, see <http://www.gnu.org/licenses/>.

Ear clipping triangulation codded by Muzkaw : https://www.youtube.com/user/Muzkaw
You need to link SFML 2.0 or above to run the program

********************************************************************/

#include <SFML/Graphics.hpp> // to open a renderwindow and draw stuff
#include "Triangulation.h" // where is defined triangulation() function

using namespace std ;
using namespace sf ;

int main() // I hope you know what that means
{
	RenderWindow window(VideoMode(800,600),"Triangulation") ; // declaration of the window where we work
	vector<Vector2f> points ; // a dynamic array that will store the points of the polygon you want to triangulate
	vector<Vector2f> triangles ; /* a dynamic array that will store the points of the triangles : if the triangle n is (An Bn Cn), then the points will be stored as [A1,B1,C1,
																																									  A2,B2,C2,
																																									  A3,B3,C3...] */
	VertexArray trianglesVA(Triangles) ; // a vertex array that will draw the triangles for us (SFML feature)
	VertexArray trianglesWireframeVA(LinesStrip) ; // another vertex array to draw the wireframe
		
	while(window.isOpen()) // update loop
	{
		Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		Vector2f mousePos = Vector2f(Mouse::getPosition(window).x , Mouse::getPosition(window).y) ; // save mouse position in a Vec2f each frame
		if(Mouse::isButtonPressed(Mouse::Left)) // if we click LMB, then we add a point to the dynamic array points
		{
			if(points.size()==0) // if it is the first point, no problem, we add it
				points.push_back(mousePos) ;
			else if(Distance(mousePos,points.back())>10) // we want a small gap between points to avoid getting 2 points at the exact same spot : that will eventually block the triangulation algorithm ; Distance() is defined in Triangulation.h
				points.push_back(mousePos) ;
		}
		if(Keyboard::isKeyPressed(Keyboard::R)) // hit r to reset
		{
			points.clear() ;
			triangles.clear() ;
			trianglesVA.clear() ;
			trianglesWireframeVA.clear() ;
		}

		if(Keyboard::isKeyPressed(Keyboard::Space)) // hit space to triangulate the polygon -> hold space while drawing a polygon, it updates it in real time
		{
			trianglesVA.clear() ;
			trianglesWireframeVA.clear() ;
			triangles = triangulate(points) ; // triangulate() is defined in Triangulation.h
			for(int i(0) ; i < triangles.size() ; i++) // we copy the points triangulated into the vertex arrays in order to draw the polygon and its wireframe
			{
				Vertex vertex1(triangles[i]), vertex2(triangles[i]) ;
				vertex1.color = Color::Color(255,255,170) ; vertex2.color = Color::Black ;
				trianglesVA.append(vertex1) ; trianglesWireframeVA.append(vertex2)  ;
			}
		}

		window.clear(Color::White) ; // we clear the window before drawing a new frame
		window.draw(trianglesVA) ;
		window.draw(trianglesWireframeVA) ;
		
		for(int i(0) ; i < points.size() ; i++) // draw the red dots when clicking
		{
			CircleShape circle(3) ;
			circle.setFillColor(Color::Red) ;
			circle.setOrigin(circle.getRadius()/2,circle.getRadius()/2) ;
			circle.setPosition(points[i]) ;
			window.draw(circle) ;
		}
		window.display() ; // shows the window with its content
	}
}
