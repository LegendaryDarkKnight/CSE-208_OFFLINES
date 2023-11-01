#include <iostream>
#include <chrono>
#include <iomanip> // Include for std::setprecision
#include <thread>

int main() {
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    // ... Your code to measure the running time ...
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration in milliseconds with high decimal precision
    auto duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count();

    // Output the duration
    std::cout <<std::fixed<<std::setprecision(8)<< "Running time: " << duration << " milliseconds" << std::endl;

    return 0;
}

