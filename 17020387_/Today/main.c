#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#define MAX_VERTICES 6000
// Q11. Macro definition which declared the MAX_VERTICES as 6000 constant value through out the code.So the constant name MAX_VERTICES would contain value 6000
#define MAX_POINTS_PER_FACE 10
//Q12. Macro definition which declared the MAX_POINTS_PER_FACE as 10 constant value through out the code.So the constant name MAX_POINTS_PER_FACE would contain value 10
#define MAX_FACES 1000
//Q13. Macro definition which declared the MAX_FACES as 1000 constant value through out the code.So the constant name MAX_FACES would contain value 1000


float vertex_list[MAX_VERTICES][3];
//Q14. Show float type array list of vertex which have maximum three vertices
int face_vertex_list[MAX_FACES][MAX_POINTS_PER_FACE];
//Q15. Int type array list of face_vertex_list which have maximum faces depending on the max_point_per_face

int n_vertices_per_face[MAX_FACES];
int vertex_index=-1;
int face_index=-1;

//Q1.In here split_string function read lines one by one to tokenize. In here token get one word in monkey.obj file. v,f or values which seperate from  space character are read through this function one by one. Firstly the line reads the token which is in zero index. It is shown by tok_index=0. This fill out an array of values which receive a line from monkey.obj file. tok_index is used to refer the token index of the line.vertex_dim is used to represent state variables such as X as 0,Y as 1,Z as 2.
int split_string(const char* str){
	//Returns first token
	char *token=strtok((char *)str, " ");
	int tok_index=0;
	char* str_v("v");

	int vertex_dim=-1;
	int vertex_indx_per_face=-1;

//Q7. In here findout whether we are reading a line through token . It is find out by when NULL is not equal.It states that we should beginning a new vertex. When it read a line firstly it print a token and next the token index .After that it finds the token index 0 is v or f. When it is v, we  add plus 1 to increase the vertex_index as vertex_index is starting from -1.So now vertex_index array is 0.When it is f,face_index is increment by one value, vertex_index_per_face become zero and other two lines also occured. The other lines are print statement of adding face through face_index and vertex_indx_per_face is assign in to the n_vertices_per_face array. At the else part we are in the place where token is not zero.    In here firstly we should find out whether token index is in between 0 and 3. It means previously we are in a read line which begin from v. Then we add vertex_dim 2D array into the vertex_index through token value. If it is not we read a line which starting from f. So we add vertex_index_per_face to face_index 2D array through token.After the if statement ,we increase the tok_index through one value and make the first index is equal to NULL to jump into the other value in the same string .

	while(token!=NULL){
		printf("\n\n++++++++++++++++\n[%s]\n",token);
		printf("tok_index=%d\n",tok_index);

		if(tok_index==0){
			printf("is comparison? <%i><%i>\n",token[0],token[1]);
		if(strcmp(token,"v")==0)
		{
			printf("#################VERTEX##################### %i\n",vertex_index);
			vertex_index++;
			vertex_dim=0;
			//begin adding the vertex with the vertex' x value.



		}
		else if(strcmp(token,"f")==0){
			face_index++;
			vertex_indx_per_face=0;
			n_vertices_per_face[face_index]=vertex_indx_per_face;
			printf("ADDING FACE %i\n", face_index);

		}


		}
		else{
			if(vertex_dim>=0 && vertex_dim <3){
				vertex_list[vertex_index][vertex_dim]=atof(token);
				if(vertex_dim ==2)
					vertex_dim=-1;
				else
					vertex_dim++;
			}
			else if(vertex_indx_per_face>=0){
				face_vertex_list[face_index][vertex_indx_per_face]=atoi(token);
			//atoi will automatically get rid of the "//" characters.
			vertex_indx_per_face++;
			n_vertices_per_face[face_index]=vertex_indx_per_face;


			}	
		}
		tok_index++;
		token=strtok(NULL," ");

	}
	


}

//Q2. We get the monkey.obj file string(char array) and open that file for reading. We use std::ifstream infile(filename) to start reading the file. To read each line we used the variable std:: string line. After that we can read each line into a string variable and display in the terminal output.After that we print relevant X,Y,Z vertices.

int read_obj_file(char * filename){
	std::ifstream infile(filename);
	std::string line;

	while(std::getline(infile,line)){
		std::cout<< "{{" << line << "}}" << std::endl;
		split_string(line.c_str());


	}
	printf("\n=========================\n");

	for(int i=0;i<=vertex_index;i++){
		printf("%i: X=%f, Y=%f, Z=%f\n", vertex_list[i][0], i, vertex_list[i][1],vertex_list[i][2]);


	}
	printf("\n\n*******************************\n");
	
	//Q8. This for loop helps to print the face and vertices per face in the relevant line.After that it get vretices_per_value and print the face_vertex_list beginning from 0. Here is a sample code of Face-496 : 4 vertices and V314-->V506-->V504-->V322

	for(int i=0;i<=face_index;i++){
		printf("Face-%i : %i vertices\n",i,n_vertices_per_face[i]);
		for(int j=0;j<n_vertices_per_face[i];j++){
			printf("V%i", face_vertex_list[i][j]);
			if(j<n_vertices_per_face[i]-1)
				printf("-->");



		}
		printf("\n");

	}
	return 0;
}


