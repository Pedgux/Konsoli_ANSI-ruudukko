#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <sstream> 
#include <Windows.h>

const std::string reset = "\x1b[0m";

const std::unordered_map<int, std::string> colorMap{
    {0, "\x1b[30m"}, // Black
    {1, "\x1b[31m"}, // Red
    {2, "\x1b[32m"}, // Green
    {3, "\x1b[33m"}, // Yellow
    {4, "\x1b[34m"}, // Blue
    {5, "\x1b[35m"}, // Magenta
    {6, "\x1b[36m"}, // Cyan
    {7, "\x1b[37m"}, // White
};

// Function to check if a specific key is pressed
bool isKeyPressed(int virtualKey) {
  return GetAsyncKeyState(virtualKey) & 0x8000;
}

// Function to set up the console
void initialize() {
  std::cout << "\x1b[?25l"; // Hides the console cursor
  system("cls");            // Clears the console if there's any leftover junk
  std::cout << "\x1b[H";    // Moves the cursor to the top left corner
  std::cout << "\x1b[37m";  // Sets the text color to white
  std::cout << "\x1b[40m";  // Sets the background color to black
}

// Creates a grid
std::vector<std::vector<int>> createGrid(int& columns, int& rows, int& value) {
  return std::vector<std::vector<int>>(rows, std::vector<int>(columns, value));
}

// Packs the grid into a string for more efficient drawing, also takes colors into account
// ANSI codes can be found online, google it :3
std::ostringstream packGrid(const std::vector<std::vector<int>>& grid,
  const std::unordered_map<int, std::string>& colorMap) {
  std::ostringstream gridStream;
  for (const auto& row : grid) {
    for (const auto& value : row) {
			// Funny thing, google unordered_map::find, if you don't know what it does and I don't want to explain it
      if (colorMap.find(value) != colorMap.end()) {
        gridStream << colorMap.at(value) << value;
      }
      else {
        // If the color is not found, reset it
        gridStream << reset;
      }
    }
    gridStream << "\n";
  }
  gridStream << reset;
  return gridStream;
}

void clearGrid(std::vector<std::vector<int>>& grid) {
  for (auto& row : grid) {
    for (auto& value : row) {
      value = 0;
    }
  }
}

bool sameGrid(const std::vector<std::vector<int>>& grid1, const std::vector<std::vector<int>>& grid2) {
  if ((grid1.size() != grid2.size()) || (grid1[0].size() != grid2[0].size())) {
    throw std::runtime_error("Grids are of different sizes");
    return false;
  }
  for (size_t i = 0; i < grid1.size(); i++) {
    for (size_t j = 0; j < grid1[0].size(); j++) {
      if (grid1[i][j] != grid2[i][j]) {
        return false;
      }
    }
  }
  return true;
}

bool isInsideGrid(int x, int y, int columns, int rows) {
	return (x >= 0 && x < columns && y >= 0 && y < rows);
}

void drawGrid(const std::vector<std::vector<int>>& grid,
  const std::unordered_map<int, std::string>& colorMap) {
  std::cout << "\x1b[H"; // Moves the console cursor to the top left corner, if it wasn't already there
  std::ostringstream drawable = packGrid(grid, colorMap); // Get the packed grid as a string
  std::cout << drawable.str(); // Output the string
  std::cout << "\x1b[H"; // Back to the top
}
/*
void drawUpdatedGrid(std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>>& newGrid, 
  const std::unordered_map<int, std::string>& colorMap) {
  try {
		sameGrid(grid, newGrid);
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return;
  }
  if (sameGrid(grid, newGrid)) {
		return;
	}
	grid = newGrid;           //assign the new state to the grid
	drawGrid(grid, colorMap); //draw the new state
}
*/

int main() {
  initialize();
	int columns = 80;
	int rows = 25;
	int value = 0;
  int positionX = 5;
	int valueX = 0;
  bool exit = false;
  //testing to see if the functions work
	std::vector<std::vector<int>> grid = createGrid(columns, rows, value);
	std::vector<std::vector<int>> newGrid = createGrid(columns, rows, value);
	drawGrid(grid, colorMap);
	while (!exit) {
    if (isKeyPressed(VK_ESCAPE)) {
			exit = true;
		}
    if (isKeyPressed(VK_SPACE)) {
			newGrid[0][positionX] = valueX;
			positionX++;
      valueX++;
      if (valueX >= 7) {
        valueX = 1;
      }
    }
		//update / draw the grid
    if (!sameGrid(grid, newGrid)) {
      grid = newGrid;
			drawGrid(grid, colorMap);
    }

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
  return 0;
}
