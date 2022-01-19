#include "pch.h"
#include "MazeTraversal.h"


MazeTraversal::MazeTraversal(int rsize,int csize) :rsize(rsize),csize(csize)
{
	maze = new char* [rsize];
	for (int i = 0; i < rsize; i++)
	{
		maze[i] = new char[csize];
	}
	curr_row = 2;
	curr_col = 0;
	start_row = 2;
	start_col = 0;
	end_row = 10;
	end_col = 21;
	Dir = 'F'; 
	RDir = curr_row+1;
	LDir = curr_row-1;
	UDir = curr_col+1;
	DDir = curr_col-1;//direction, it will be needed for automation
	//initialize it in member initializer list of class constructor
   // data for MFC graphics display
	int cellWidthPx = 40; //A good value can be 40 or 60
	int cellHeightPx = 40;
	LoadMaze();
}

void MazeTraversal::LoadMaze()
{
	ifstream input("maze1.txt");
	for (int i = 0; i < rsize; i++)
	{
		for (int j = 0; j <csize; j++)
			input >> maze[i][j];
	}
	input.close();
}

int MazeTraversal::getCellWidthPx()
{
	return cellWidthPx;
}

int MazeTraversal::getCellHeightPx()
{
	return cellHeightPx;
}

int MazeTraversal::getrSize() {
	return rsize;

}

int MazeTraversal::getcSize() {
	return csize;

}

int MazeTraversal::getStartRow()
{
	return start_row;
}

int MazeTraversal::getStartCol()
{
	return start_col;
}

int MazeTraversal::getCurrRow()
{
	return curr_row;
}

int MazeTraversal::getCurrCol() {
	return curr_col;
}

char MazeTraversal::getCellValueAt(int i, int j)
{
	return maze[i][j];
}

void MazeTraversal::moveUp(CDC* pDoc)
{
	if (maze[curr_row - 1][curr_col] == '.') {
		curr_row = curr_row - 1;

		//pdc->FillSolidRect(curr_col*40,curr_row*40,40,40,RGB(0,0,100));
		HDC hDestDC;
		hDestDC = CreateCompatibleDC(NULL);
		CImage* cimage = new CImage();
		cimage->Load(L"images\\Up.png");
		cimage->Draw(pDoc->m_hDC, curr_col * 40, curr_row * 40, 40, 40);
		pDoc->FillSolidRect(curr_col * 40, (curr_row + 1) * 40, 40, 40, RGB(1, 256, 0));

	}
	else
	{

	}
}

void MazeTraversal::moveLeft(CDC* pDoc)
{
	if (!DestinationReached()) {
		if (maze[curr_row][curr_col - 1] == '.') {
			curr_col = curr_col - 1;
			//pdc->FillSolidRect(curr_col*40,curr_row*40,40,40,RGB(0,0,100));
			HDC hDestDC;
			hDestDC = CreateCompatibleDC(NULL);
			CImage* cimage = new CImage();
			cimage->Load(L"images\\Left.png");
			cimage->Draw(pDoc->m_hDC, curr_col * 40, curr_row * 40, 40, 40);
			pDoc->FillSolidRect((curr_col + 1) * 40, curr_row * 40, 40, 40, RGB(1, 256, 0));

		}
		else
		{

		}
	}

	else
	{
	}
}

void MazeTraversal::moveDown(CDC* pDoc)
{
	if (maze[curr_row + 1][curr_col] == '.') {
		curr_row = curr_row + 1;
		//pdc->FillSolidRect(curr_col*40,curr_row*40,40,40,RGB(0,0,100));
		HDC hDestDC;
		hDestDC = CreateCompatibleDC(NULL);
		CImage* cimage = new CImage();
		cimage->Load(L"images\\Down.png");
		cimage->Draw(pDoc->m_hDC, curr_col * 40, curr_row * 40, 40, 40);
		pDoc->FillSolidRect(curr_col * 40, (curr_row - 1) * 40, 40, 40, RGB(1, 256, 0));


	}
	else
	{

	}
}

void MazeTraversal::moveRight(CDC* pDoc)
{
	if (maze[curr_row][curr_col + 1] == '.') {
		curr_col = curr_col + 1;
		//pdc->FillSolidRect(curr_col*40,curr_row*40,40,40,RGB(0,0,100));
		HDC hDestDC;
		hDestDC = CreateCompatibleDC(NULL);
		CImage* cimage = new CImage();
		cimage->Load(L"images\\Right.png");
		cimage->Draw(pDoc->m_hDC, curr_col * 40, curr_row * 40, 40, 40);
		pDoc->FillSolidRect((curr_col - 1) * 40, curr_row * 40, 40, 40, RGB(1, 256, 0));



	}
	else
	{

	}

}


bool MazeTraversal::DestinationReached()
{
	if (curr_row == end_row && curr_col == end_col)
		return true;
	else
		return false;

}

void MazeTraversal::moveToNextCell(CDC* pDoc)
{
	if (!DestinationReached())
	{

		if (maze[curr_row + 1][curr_col] == '.' && Dir == 'F')
		{
			moveDown(pDoc);
			Dir = 'D';
		}
		else if (maze[curr_row + 1][curr_col] == '#' && Dir == 'F')
		{
			if (maze[curr_row][curr_col + 1] == '.')
				moveRight(pDoc);
			else if (maze[curr_row][curr_col + 1] == '#')
			{
				if (maze[curr_row - 1][curr_col] == '.')
				{
					moveUp(pDoc);
					Dir = 'U';
				}
				else
				{
					moveLeft(pDoc);
					Dir = 'L';
				}
			}
		}

		else if (maze[curr_row][curr_col + 1] == '.' && Dir == 'U')
		{
			moveRight(pDoc);
			Dir = 'F';
		}
		else if (maze[curr_row][curr_col + 1] == '#' && Dir == 'U')
		{
			if (maze[curr_row - 1][curr_col] == '.')
				moveUp(pDoc);
			else if (maze[curr_row - 1][curr_col] == '#')
			{
				if (maze[curr_row][curr_col - 1] == '.')
				{
					moveLeft(pDoc);
					Dir = 'L';
				}
				else
				{
					moveDown(pDoc);
					Dir = 'D';
				}
			}
		}
		else if (maze[curr_row][curr_col - 1] == '.' && Dir == 'D')
		{
			moveLeft(pDoc);
			Dir = 'L';
		}
		else if (maze[curr_row ][curr_col-1] == '#' && Dir == 'D')
		{
			if (maze[curr_row + 1][curr_col] == '.')
				moveDown(pDoc);
			else if (maze[curr_row + 1][curr_col] == '#')
			{
				if (maze[curr_row][curr_col + 1] == '.')
				{
					moveRight(pDoc);
					Dir = 'F';
				}
				else
				{
					moveUp(pDoc);
					Dir = 'U';
				}
			}
		}

		else if (maze[curr_row - 1][curr_col] == '.' && Dir == 'L')
		{
			moveUp(pDoc);
			Dir = 'U';
		}
		else if (maze[curr_row - 1][curr_col] == '#' && Dir == 'L')
		{
			if (maze[curr_row][curr_col - 1] == '.')
				moveLeft(pDoc);
			else if (maze[curr_row][curr_col - 1] == '#')
			{
				if (maze[curr_row + 1][curr_col] == '.')
				{
					moveDown(pDoc);
					Dir = 'D';
				}
				else
				{
					moveRight(pDoc);
					Dir = 'F';
				}
			}
		}

	}


}

MazeTraversal::~MazeTraversal()
{
	for (int i = 0; i < rsize; i++)
		delete[] maze[i];
	delete[] maze;
}