//This file is part of Ear clipping triangulation(GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "Triangulation.h"

float determinant(Vector2f u, Vector2f v) // basic determinant formula : det(u(x,y) , v(x',y') ) = xy'-x'y 
{
	float result = u.x*v.y - u.y*v.x ;
	return result ;
}

float Distance(Vector2f const& v1, Vector2f const& v2) // basic distance formula : dist(u(x,y) , v(x',y') ) = sqrt( (x'-x)^2 + (y'-y)^2 )
{
	float distance = sqrt(pow((v2.x-v1.x),2) + pow((v2.y-v1.y),2)) ;
	return distance ;
}

bool collisionTrianglePoint(Vector2f a, Vector2f b, Vector2f c, Vector2f point) // checks if a point is within the triangle ABC : the point must be at the left of each edge -> be careful to the winding direction
{
	Vector2f ab = b-a ;
	Vector2f bc = c-b ;
	Vector2f ca = a-c ;
	
	if(determinant(ab,point-a) > 0 && determinant(bc,point-b) > 0 && determinant(ca,point-c) > 0)
	{
		return true ;
	}
	else return false ;
}

vector<Vector2f> triangulate(vector<Vector2f> points) // the ear clipping algorithm
{
	vector<Vector2f> triangles ; /* a dynamic array that will store the points of the triangles : if the triangle n is (An Bn Cn), then the points will be stored as [A1,B1,C1,
																																									  A2,B2,C2,
																																									  A3,B3,C3...] */
	vector<Vector2f> initialPoints = points ;
	if(points.size() < 3) // let's make sure that the user don't feed the function with less than 3 points !
		return triangles ;
	else
	{
		bool impossibleToTriangulate = false ;
		bool triangleFound = true ;

		while(points.size() != 0) // run the algorithm until our polygon is empty
		{
			if(!triangleFound) // if we've looped once without finding any ear, the program is stuck, the polygon is not triangulable for our algorithm (likely to be a 8 shape or such self intersecting polygon)
				return triangles ;

			triangleFound = false ; // we want to find a new ear at each loop

			for(int i(0) ; i < points.size()-2 ; i++) // for each 3 consecutive points we check if it's an ear : an ear is a triangle that wind in the right direction and that do not contain any other point of the polygon
			{
				if(!triangleFound) // if we still didn't find an ear
				{
					bool result = false ;
					if(determinant(points[i+1]-points[i],points[i+2]-points[i+1]) < 0) // if the triangle winds in the right direction
					{
						result = true ;
						for(int j(0) ; j < initialPoints.size() ; j++) // we check if there's no point inside it
						{
							if(collisionTrianglePoint(points[i+2],points[i+1],points[i],initialPoints[j]))
							{
								result = false ; // if I got a point in my triangle, then it's not an ear !
							}
						}
					}

					if(result) // now, we have found an ear :
					{
						triangleFound = true ;
				
						triangles.push_back(points[i]) ; // so we add our 3 vec2f to the triangle array : it's one of our triangles !
						triangles.push_back(points[i+1]) ;
						triangles.push_back(points[i+2]) ;

						vector<Vector2f> bufferArray;
						for(int j(0) ; j < points.size() ; j++) // then we delete the triangle in the points array : we already know that it's an ear, we don't need it anymore
						{
							if(j!=i+1) // we copiy all the points in a buffer array except the point we don't want
							{
								bufferArray.push_back( points[j] );
							}
						}
						points = bufferArray ;
					}
				}
			}
		}
	}			
		return triangles ; // we return the triangle array
}
