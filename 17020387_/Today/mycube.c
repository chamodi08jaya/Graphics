//includes
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "main.c"

//Function Prototypes
void display();
void specialKeys();


//Global Variables
double rotate_y=0;
double rotate_x=0;

//Q3.This function is used to get color codes in floating point numbers.When calling randomFloat() function in the below of the code it generates specific r value for glcolor in every vertex.
float randomFloat(){
	float r =(float)rand()/(float)RAND_MAX;
	return r;
}

//Q4.All the work of drawing will done in this function.By doing glClear() the old drawings invisible under the new drawing. It makes the location correctly in the current object.
//display() callback function
void display(){
	//Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//Reset transformation
	glLoadIdentity();

	//Rotate when user changes rotate_x and rotate_y
	glRotatef(rotate_x,3.0,1.0,0.0);
	glRotatef(rotate_y,0.0,1.0,0.0);
	glScalef(0.13f,0.13f,0.13f);

	float colour_dif=1.0f / face_index;
	
	//Q9 Take the face_index and satring from 0 it increments the value. In here we add colors to all side through multi colored side-front using glBegin(GL_POLYGON)
	for(int i=0;i<=face_index;i++){
		glBegin(GL_POLYGON);
		glColor3f(randomFloat(),randomFloat(),randomFloat());
	//Q10 This for loop help us to get vertices of the object in floating point .In here we drawing 3 dimensions vertices showing as glVertex3f(). Always we defining the vertices as clockwise. We add these vertices in between glBegin() and glEnd().
	for (int j=0;j<n_vertices_per_face[i];j++){
		int vertex_index_temp=face_vertex_list[i][j]-1;
		glVertex3f(vertex_list[vertex_index_temp][0],vertex_list[vertex_index_temp][1],vertex_list[vertex_index_temp][2]);

	}
	glEnd();
	}
	glFlush();
	glutSwapBuffers();

} 
//Q5. This function helps to rotate the object from pressing arrow keys.This function declared the global variables as rotate_x and rotate_y. When we press the up and down arrow keys rotate_x will change accordingly to the below.
//specialKeys() Callback Function
void specialKeys(int key,int x,int y){

	//Right arrow-increase rotation by 5 degree
	if(key==GLUT_KEY_RIGHT)
		rotate_y+=5;

	//Left arrow-decrease rotation by 5 degree
	else if(key==GLUT_KEY_LEFT)
		rotate_y-=5;

	else if(key==GLUT_KEY_UP)
		rotate_x+=5;

	else if(key==GLUT_KEY_DOWN)
		rotate_x-=5;

	//Request display update
	glutPostRedisplay();

}
//Q6. This below function show setting up of the main function  code. In here we get read_obj_file as "monkey.obj".From that it refer to the read_obj_function in main.c file and run the code in it.
//main() function
int main(int argc,char* argv[]){
	read_obj_file("monkey.obj");

	//Initialize GLUT and process user parameters
	glutInit(&argc,argv);

	//Request double buffered true color window with z-buffer
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);


	//Create window
	glutCreateWindow("Awesome Cube");

	//Enable z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	//Callback functions
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	//Pass control to GLUT  for events
	glutMainLoop();

	//Return to OS
	return 0;

}




