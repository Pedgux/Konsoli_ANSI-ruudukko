#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <sstream> 

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

// Draws the grid as a string, yay
void drawGrid(const std::vector<std::vector<int>>& grid,
  const std::unordered_map<int, std::string>& colorMap) {
  std::cout << "\x1b[H"; // Moves the console cursor to the top left corner, if it wasn't already there
  std::ostringstream drawable = packGrid(grid, colorMap);
  std::cout << drawable.str(); // Obvious
  std::cout << "\x1b[H"; // Back to the top
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

int main() {
  initialize();
  int cols = 50;
  int rows = 30;
  int value = 1;
  auto grid = createGrid(cols, rows, value);
  drawGrid(grid, colorMap);
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  grid[20][20] = 2;
  grid[21][20] = 2;
  grid[22][20] = 2;
  drawGrid(grid, colorMap);
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  clearGrid(grid);
  grid[20][20] = 3;
  grid[21][20] = 1;
  grid[22][20] = 6;
  drawGrid(grid, colorMap);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
