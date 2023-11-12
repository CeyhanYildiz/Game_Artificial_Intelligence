#include <iostream>

#include <vector>
#include <string>

using namespace std;

/* Idee for a maze

 Samy :
⬛⬛⬛⬛⬛⬛⬛
⬛🟦🟦🟦🟦🟦⬛
⬛🟦⬛⬛⬛🟩⬛
⬛🟦🟦🟦⬛⬛⬛
⬛⬜⬛🟦🟦🟥⬛
⬛⬛⬛⬛⬛⬛⬛

⬜ = Path
⬛ = Wall

Ceyhan:


⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛        ⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛
⬛🟩🟩⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛        ⬛🟩🟩🟦🟦🟦🟨🟨🟨🟨🟨🟨⬛
⬛🟩🟩⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛        ⬛🟩🟩🟦🟦🟦🟨🟨🟨🟨🟨🟨⬛
⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛        ⬛⬛⬛⬛🟦🟦⬛⬛⬛⬛⬛⬛⬛
⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛        ⬛🟨🟨🟨🟦🟦🟦🟦🟦🟦🟦🟦⬛
⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛        ⬛🟨🟨🟨🟦🟦🟦🟦🟦🟦🟦🟦⬛
⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛        ⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛🟦🟦⬛
⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛        ⬛🟨🟨🟨🟨🟨🟨🟦🟦🟦🟦🟦⬛
⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛        ⬛🟨🟨🟨🟨🟨🟨🟦🟦🟦🟦🟦⬛
⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛        ⬛🟨🟨⬛⬛⬛⬛🟦🟦⬛⬛⬛⬛
⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛🟥🟥⬛        ⬛🟨🟨⬛⬜⬜⬜🟦🟦🟦🟥🟥⬛
⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛🟥🟥⬛        ⬛🟨🟨⬛⬜⬜⬜🟦🟦🟦🟥🟥⬛
⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛        ⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛

⬜ = Path         = P
⬛ = Wall         = W
🟦 = Correct Path = C
🟩 = Start        = S 
🟥 = End          = E
🟨 = Wrong Path   = w
*/




void printBlockSymbol(char value);

int main()
{
    
    // 8 x 8 playable maze
    int count = 25;
    cout << endl;
    for (int x = 0; x < count; x++)
    {
        for (int i = 0; i < count; i++) {
            if (i % 3 == 0 || x % 3 == 0) {
                printBlockSymbol('W'); // Print 'W' for every third element (0, 3, 6, 9, ...)
            } else {
                printBlockSymbol('P'); // Print 'P' for all other elements
            }
        }
        cout << endl;
    }    
    cout << endl;

     
    return 0;
}


void printBlockSymbol(char value) {
    switch (value) {
        case 'P': cout << "⬜"; break;
        case 'W': cout << "⬛"; break;
        case 'C': cout << "🟦"; break;
        case 'S': cout << "🟩"; break;
        case 'E': cout << "🟥"; break;
        case 'w': cout << "🟨"; break;
        default:
            cout << "Invalid value\n";
    }
}