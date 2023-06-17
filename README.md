# RockPaperETC
Rock Paper Scissors Lizard Spock Game done in C++

Description:
This code implements a Rock Paper Scissors Lizard Spock game where two players can compete against each other.

Technology Choices:
- Language: C++
- Threading: C++11 standard threads
- Mutex: `std::mutex` from the C++ Standard Library for synchronization
- Visual Studio 22 (one I'm most used to)

How to Run the Solution:
To see the working solution, follow these steps:
1. Go to where ever you've saved the file
2. Go to RockPaperETC\x64\Debug
3. Run RockPaperETC.exe

Additional Comments:
- The code has been structured into separate functions for better organization and readability.
- The use of threads allows both players to make their moves concurrently, simulating a real-time game experience.
- The code uses a mutex to synchronize access to shared resources and prevent data races.
- Random moves are generated for Setup 1 using the `randomChar()` function.
- The game results are displayed at the end, showing the number of wins for each player and the number of ties.
