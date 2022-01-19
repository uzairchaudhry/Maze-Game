#pragma once
#include<iostream>
#include<fstream>
#include<windows.h>
#include<mmsystem.h>
using namespace std; 


class MazeTraversal {
public:
	char** maze;
	int curr_row;
	int curr_col;
	int start_row;
	int start_col;
	int end_row;
	int end_col;
	
	char Dir;  //direction, it will be needed for automation
	int RDir;
	int LDir ;
	int UDir ;
	int DDir;
	const int rsize; //initialize it in member initializer list of class constructo
	const int csize;
	// data for MFC graphics display
	int cellWidthPx;//A good value can be 40 or 60
	int cellHeightPx; 


public:
	MazeTraversal(int rsize = 15,int csize=22);
	void LoadMaze();// call in constructor
	void moveUp(CDC* pDC );
	void moveLeft(CDC* pDC);
	void moveDown(CDC* pDC);
	void moveRight(CDC* pDC);
	//void display();
	void moveToNextCell(CDC* pDC);  // it will be needed for automation
	~MazeTraversal(); 
	
	   //getter functions
	int getCellWidthPx();
	int getCellHeightPx();
	int getrSize();
	int getcSize();
	int getStartRow();
	int getStartCol();
	int getCurrRow();
	int getCurrCol();
	char getCellValueAt(int i, int j);  // the returned character is either ‘.’ or ‘#’
	bool DestinationReached();
    //You may add further functions if you need to
};   
