﻿// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
//Huba Ferenc Benzar


//Importing libraries
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
int main()
{
	//Data String
	char intro[] = "Welcome to Huba Benzar's Module Calculator.\nName: Huba Benzar\nStudent ID: 201262833\nemail: H.Benzar@student.liverpool.ac.uk\n";
	char getModuleMark[] = "Please enter your mark from 0-100 for module %d: ";
	char higher[] = "\nThe number entered is over 100\n";
	char smaller[] = "\nThe number is negative\n";

	//Pass Fails
	char passed[] = "Number of passes: %d\n";
	char failed[] = "Number of fails: %d\n";

	//Formatting
	char moduleNumber[] = "%d";										// format string for the scanf function*/
	char Colon[] = ": "; 											// format string for the scanf function*/

																	//Data Integer
	int modMark = 0; 												//Module mark 0 by default as thats the lowest possible outcome
	int number = 1; 												//Tracks the number of loops and also prints out the number of the module entered

	int count = 1; 													//Array counter
	int pass = 0; 													//Number of passes
	int fail = 0; 													//Number of fails

																	//Array definer
	int marks[6]; 													// Array with a limited number of rows

	_asm {
		jmp startTheMarker 											//This jumps to the start section

		startTheMarker : 										//This is the start label
			mov ecx, 1 												//set ecx to 1 
			lea eax, marks 											//sets eax as the marks array
			mov ebx, eax 											//moves address of array into eax
			lea eax, intro 											//move intro into eax
			push ecx												//stacks ecx
			push eax												//stack eax
			call printf												//prints intro (welcome message)
			add esp, 4												//remove 4 bytes from the stack pointer
			pop ecx													//clears ecx to default
			jmp forloop												//This starts the forloop section

		forloop :												//start of for loop
			//Prints and stacks
			push ecx												//stacks ecx
			lea eax, getModuleMark									//puts the getModuleMark string into eax
			push number												//pushes the number int into eax
			push eax												//stack eax
			call printf												//prints the number module number string and the number integer
			add esp, 8												//remove 8 bytes from the stack pointer
			pop ecx													//clears ecx to default
			
			lea eax, modMark 										//loads modMark in eax
			push ecx												//stacks ecx
			push eax												//stacks eax
			lea eax, moduleNumber									//loads moduleNumber into eax
			push eax												//stacks eax
			call scanf												//scans for the input from the user
			add esp, 8												//remove 8 bytes from the stack pointer
			pop ecx													//clears ecx to default

			//Conditional Jumpers
			cmp modMark, 100										//compare modMark with 100
			jg positiveInput										//Jumps to positiveInput if it's greater
			cmp modMark, 0											//compared modMark with 0
			jl negativeInput										//Jumps when ModMark is lower to negativeInput
			jmp successfulInput										//Jumps to successfulInput

		positiveInput : 									//It goes here when the number is higher
			push ecx
			lea eax, higher											//loads higher string into eax
			push eax												//stacks eax
			call printf												//prints the higher string
			add esp, 4												//remove 8 bytes from the stack pointer
			pop ecx													//stacks ecx
			jmp forloop												//jumps to forloop

		negativeInput :											//It goes here when the number is negative
			push ecx
			lea eax, smaller										//loads smaller string into eax
			push eax												//stacks eax
			call printf												//prints the smaller string
			add esp, 4												//remove 8 bytes from the stack pointer
			pop ecx													//stacks ecx
			jmp forloop												//jumps to forloop

		successfulInput : 										//It goes here when both parameters pass (between 0-100)
			//During for Loop
			mov eax, modMark;										//moves modMark into eax
			mov[ebx], eax;											//moves eax into the array
			add ebx, 4;												//next index of the array
			inc ecx													//increments ecx (ecx+1)
			inc number												//increments number (number+1)
			cmp ecx, 6												//compares ecx to 6 (ecx - 6)
			jle forloop												//Jump when forloop is than ecx

			//After for Loop
			lea ebx, marks
			mov count, 1

			passFailLoop :

	passfailChecker:
			cmp[ebx], 39 //checks if pass or fail
			jle passFailFAIL //jumps if fail, otherwise...
			add pass, 1
			jmp passFailChecked //skip over adding to fails
		
		passFailFAIL :
			add fail, 1

		passFailChecked :
			add ebx, 4 //next index of array
			add count, 1
			cmp count, 7
			je display
			jmp passFailLoop

		display : 												//display the fail and pass messages with values
			lea eax, passed											//loads passed into eax
			push pass												//pushes pass int into eax
			push eax												//stack eax
			call printf												//prints the passed string and the pass integer
			add esp, 8												//remove 8 bytes from the stack pointer

			lea eax, failed											//loads failed into eax									
			push fail												//pushes fail int into eax
			push eax												//stack eax
			call printf												//prints the failed string and the fail integer
			add esp, 8												//remove 8 bytes from the stack pointer
	}
	system("pause");
	return 0;
}
