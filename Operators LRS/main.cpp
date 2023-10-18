//
//  main.cpp
//  Operators LRS
//
//  Created by Глеб Капустин on 18.10.2023.
//
//
// Created by Глеб Капустин on 25.09.2023.
//
#include "ImageProcessor.hpp"

int main(int argc, const char * argv[]) {
    ImageProcessor imageProcessor("/Users/gleb_kapustin/Desktop/VSU/Operators LRS/Operators LRS/Images/input2.png");
    
    // Apply the Laplace operator and save the result.
        imageProcessor.applyLaplaceOperator();
    
    // Apply the Roberts operator and save the result.
        imageProcessor.applyRobertsOperator();

        // Apply the Sobel operator and save the result.
        imageProcessor.applySobelOperator();

    return 0;
}
