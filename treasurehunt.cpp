#include <stdio.h>              // For input/output (scanf, printf)
#include <unordered_set>        // To track visited locations (to detect infinite loops)

struct position
{
    int r, c;   // r = current row, c = current column (player's current GPS location)

    // Constructor: sets starting position
    position(int r, int c)
    {
        this->r = r;
        this->c = c;
    }

    // Move the player based on the direction given at current location
    void moveUp(char dir)
    {
        if (dir == 'N') r--;        // Move north (up one row)
        else if (dir == 'S') r++;   // Move south (down one row)
        else if (dir == 'W') c--;   // Move west (left one column)
        else c++;                   // Move east (right one column)
    }

    // Check if the player has walked outside the playing area
    bool out_of_bounds(int totalRows, int totalCols)
    {
        return !(this->r >= 0 && this->r < totalRows &&
                 this->c >= 0 && this->c < totalCols);
        // Returns true if player left the grid → should print "Out"
    }

    // Convert (row, col) into a unique number so we can store it in a hash set
    int toInt(int totalCols)
    {
        return this->r * totalCols + this->c;
        // Example:
        // If grid has 5 columns,
        // cell (2,3) becomes 2*5 + 3 = 13
        // This uniquely represents each cell
    }
};

int main()
{
    int r, c, step_counter = 0;   // r = rows, c = columns
                                  // step_counter = number of moves taken

    scanf("%d %d",&r,&c);         // Read grid size

    char level[r][c+1];           // Store the playing area (each row is a string)

    for (int i = 0; i < r; i++)
        scanf("%s",level[i]);     // Read each row of directions

    std::unordered_set<int> visited; 
    // This keeps track of locations we've already been to.
    // If we visit the same cell again → we are stuck in a loop → "Lost"

    struct position pos(0,0);  
    // Player always starts at first row, first column (top-left corner)

    while(1)   // Keep moving until we reach treasure, go out, or get stuck
    {
        if (pos.out_of_bounds(r, c))
        {
            // Player stepped outside the playing area
            printf("Out\n");
            break;
        }

        if (visited.find(pos.toInt(c)) != visited.end())
        {
            // We've been here before → infinite loop
            printf("Lost\n");
            break;
        }

        char val = level[pos.r][pos.c];
        // Read the instruction at current location

        if (val == 'T')
        {
            // We found the treasure!
            printf("%d\n", step_counter);
            break;
        }

        // Mark this location as visited before moving
        visited.insert(pos.toInt(c));

        // Follow the GPS direction
        pos.moveUp(val);

        // Count this move
        step_counter++;
    }

    return 0;
}