# Edit-3D-DOS-1995
An early 3D viewing program I wrote for DOS with Turbo C++.


	Kevin's 3D C++ Class Library
	Copyright (1995) Kevin Richey
	All RIghts reserved.

	Permission is granted to use this software for experimental
	purposes only.  Please do not distribute this code in any
	form without written permission from the author.

	---------------------------------------------------------------

	Programs:

	EDIT3D.EXE	3D object editor
	CYLGEN.EXE	Cylinder shape file generator
	CONEGEN.EXE	Cone shape file generator
	SPHERGEN.EXE	Sphere shape file generator

	These seem to run okay under DOSBox.

	---------------------------------------------------------------

	EDIT3D

	3D object editor.
	Copyright (1995) Kevin Richey

	This utility allows you to manipulate several 3D objects
	on the screen in wireframe perspectice projection in order
	to design more complex shapes.

	Make sure that the "EGAVGA.BGI" file is in the same directory
	that you are running VIEW3D2 from.

	The program has several commands when you first start:

	l	Load shape into database
	w	Write scene to disk as 3D object file
	a	Add object to scene
	e	Edit object
	c	Set camera options
	b	Toggle backface culling hidden surface removal on/off
	q	Quit EDIT3D

	After the first object has been added to the scene, three
	new operations will become active:

	t	Translate object
	s	Scale object
	r	Rotate object

	Here is a short tutorial:

	1) Run the program.
	2) Press "c" followed by "t" to move the camera.  This is
		important because the camera begins at the center of
		the scene, and to avoid floating point errors, it
		should be moved back.
	3) When asked for translation values, enter "0 0 10".
	4) Press "l" to load a shape.  An object can not be added
		to the scene until its shape is in memory.  If the shape
		you wish to load is a compound object, be sure that the
		simpler shapes it uses are already loaded into the database.
	5) Enter the file name of the 3D shape file you wish to use,
		but fo NOT include the ".3D" extension.  You may load
		as many shapes as you would like to use.
	6) Press "a" to add an object.
	7) You will then be asked for both a name and a shape
		(separated by a space).  The 	name may be anything you
		like, as long as it is unique.  The shape is the file
		name (minus the .3D extension) of a previously loaded shape.
	8) The object will appear on the screen.  You may now
		edit it using scale, rotate, and translate.
	9) After you have added several shapes to the scene, you can
		edit any of them by pressing "e" and entering the name
		of the object (NOT the name of the shape).
	10) When you are finished with the object, you can save it to
		disk by pressing "w" and entereing a name for it.

	---------------------------------------------------------------

	CYLGEN
	CONEGEN
	SPHERGEN

	3D shape generation utilities.
	Copyright (1995) Kevin Richey

	These three programs are used to generate cylinders, cones,
	and spheres, respectively.

	They ask you for the number of sides on the shape, which must
	be greater than two, and the name of the data file to store
	the shape data in.

