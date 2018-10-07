#include <iostream>
#include <stack>
#include <stdlib.h>

void createQueens(int numberOfQueens);
bool checkConflict(std::stack<int> RowStack, std::stack<int> ColStack, int row, int column);

int main()
{
	int numberOfQueens;

	std::cout << "How many Queens/Row x Columns do you want to have? (Must be 4 or greater) ";
	std::cin >> numberOfQueens;
	createQueens(numberOfQueens);

	return 0;
}

void createQueens(int numberOfQueens)
{
	//Stack to hold columns and rows
	std::stack<int> ColStack;

	std::stack<int> RowStack;
	
	int column = 1;
	int row = 1;
	int filled = 0;
	bool conflict = false;
	
	//Determine if the board is an impossible size
	bool specialCase = false;

	RowStack.push(row);
	ColStack.push(column);	
	
	filled++;	
	row++;

	while(RowStack.size() < numberOfQueens)
	{
		//Conflict check
		conflict = checkConflict(RowStack, ColStack, row, column);
		
		if(conflict && column != numberOfQueens)
		{
			column++;
		}
		
		else if(conflict &&  column == numberOfQueens)
		{
			//If the one already set on board can be moved, move it over one column
			if(ColStack.top() + 1 <= numberOfQueens)
			{
				column = ColStack.top() + 1;
				row = RowStack.top();
			}
			//If it cannot move, pop it off and make the one under it move over one
			else
			{
				RowStack.pop();
				ColStack.pop();
				filled--;
				if(!RowStack.empty())
				{
					column = ColStack.top() + 1;
					row = RowStack.top();
				}
			}
			//Then pop it off so we can move it and check for conflicts, ran every time
			if(!RowStack.empty())
			{
				RowStack.pop();
				ColStack.pop();
				filled--;
			}
			else
			{
				specialCase = true;
				break;
			}
		}
		//If there are no conflicts, then push it on the stack
		else
		{
			filled++;
			RowStack.push(row);
			ColStack.push(column);
			if(filled == numberOfQueens)
			{
				break;
			}
			else
			{	
				column = 1;
				row++;
			}
		}
	}

	std::cout << "Filled Spots: " << filled << std::endl;
	
	if(!specialCase)
	{
		for(int i = numberOfQueens; i > 0; i--)
		{
			std::cout <<"Row: " << RowStack.top() << " Col: " << ColStack.top() << std::endl;
			RowStack.pop();
			ColStack.pop();
		}
	}
	
	else
	{
		std::cout << "The board size of "<< numberOfQueens << " x " << numberOfQueens << " is not possible."<<std::endl;
	}

}

//Since its based by value, we can pop stuff off the stacks without actually affecting them in the other methods.
//Retruns a boolean value for if a conflict was found with current location.
bool checkConflict(std::stack<int> RowStack, std::stack<int> ColStack, int row, int column)
{
	bool conflict = false;
	while(!RowStack.empty())
	{
		//Checks columns of the queen on stack
		if(column == ColStack.top())
		{
			conflict = true;
			break;
		}
		//Check the diagonals by taking the slope and if the slope is 1 then its a diagonal
		else if(abs(row - RowStack.top()) == abs(column - ColStack.top()))
		{
			conflict = true;
			break;
		}	
		//Pop it each time so we can check all values
		ColStack.pop();
		RowStack.pop();
	}	
	return conflict;
}	
