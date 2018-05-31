/***********************************************************
Starter code for Assignment 3

This code was originally written by Jack Wang for
CSC418, SPRING 2005

***********************************************************/


#include "raytracer.h"
#include <cstdlib>

int main(int argc, char* argv[])
{
	// Build your scene and setup your camera here, by calling 
	// functions from Raytracer.  The code here sets up an example
	// scene and renders it from two different view points, DO NOT
	// change this if you're just implementing part one of the 
	// assignment.  
	Raytracer raytracer;
	int width = 320;
	int height = 240;

	if (argc == 3) {
		width = atoi(argv[1]);
		height = atoi(argv[2]);
	}

	// Camera parameters.
	Point3D eye(0, 0, 1);
	Vector3D view(0, 0, -1);
	Vector3D up(0, 1, 0);
	double fov = 60;

	// Defines a material for shading.
	Material gold(Colour(0.3, 0.3, 0.3), Colour(0.75164, 0.60648, 0.22648),
		Colour(0.628281, 0.555802, 0.366065),
		51.2);
	Material jade(Colour(0, 0, 0), Colour(0.54, 0.89, 0.63),
		Colour(0.316228, 0.316228, 0.316228),
		12.8);

	// for hyperboloid
	Material jade2(Colour(0, 0, 0), Colour(0.54, 0.89, 0.63),
		Colour(0.316228, 0.316228, 0.316228),
		12.8);

	gold.reflection_coeff = 0.3;
	jade.reflection_coeff = 0.6;

	// for texture mapping
 	unsigned char *rarray = NULL; unsigned char *garray = NULL; unsigned char *barray = NULL;

	// for refraction
	gold.transparency = 0.5;
	gold.refraction_mu = 0.3;

/*
	// Defines a point light source.
	raytracer.addLightSource(new PointLight(Point3D(0, 0, 5),
		Colour(0.9, 0.9, 0.9)));
*/

	// for area light source
	raytracer.addLightSource(new AreaLight(Point3D(0, 0, 5), Colour(0.9, 0.9, 0.9), 1, 1));
	

	// Add a unit square into the scene with material mat.
	SceneDagNode* sphere = raytracer.addObject(new UnitSphere(), &gold);
	SceneDagNode* plane = raytracer.addObject(new UnitSquare(), &jade);
	//SceneDagNode* hyperboloid = raytracer.addObject(new UnitHyperboloid(), &jade2);

	// for texture mapping
	unsigned long int texture_width;
	long int texture_height;
	jade.texture = 1;
	bmp_read("earthmap.bmp", &texture_width, &texture_height, &rarray, &garray, &barray);
	jade.width = texture_width;
	jade.height = texture_height;
	jade.rarray = &rarray;
	jade.garray = &garray;
	jade.barray = &barray;

	//bmp_write( "view3.bmp", texture_width, texture_height, rarray, garray, barray );

	// Apply some transformations to the unit square.
	double factor1[3] = { 1.0, 2.0, 1.0 };
	double factor2[3] = { 6.0, 6.0, 6.0 };
	raytracer.translate(sphere, Vector3D(0, 0, -5));
	raytracer.rotate(sphere, 'x', -45);
	raytracer.rotate(sphere, 'z', 45);
	raytracer.scale(sphere, Point3D(0, 0, 0), factor1);

	raytracer.translate(plane, Vector3D(0, 0, -7));
	raytracer.rotate(plane, 'z', 45);
	raytracer.scale(plane, Point3D(0, 0, 0), factor2);

	// for hyperboloid
	//raytracer.translate(hyperboloid, Vector3D(0, 0, 0));
	//raytracer.rotate(hyperboloid, 'x', 45);

	// Render the scene, feel free to make the image smaller for
	// testing purposes.	
	raytracer.render(width, height, eye, view, up, fov, "view1.bmp");
	

	// Render it from a different point of view.
	Point3D eye2(4, 2, 1);
	Vector3D view2(-4, -2, -6);
	raytracer.render(width, height, eye2, view2, up, fov, "view2.bmp");

	return 0;
}