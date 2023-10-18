#define STB_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <vector>
#include "stb_image.h"
#include "stb_image_write.h"



class ImageProcessor {
public:
    ImageProcessor(const char* filename) {
        image_data = stbi_load(filename, &width, &height, &channels, 0);
        if (!image_data) {
            std::cerr << "Failed to load the image." << std::endl;
            exit(1);
        }
    }

    ~ImageProcessor() {
        if (image_data) {
            stbi_image_free(image_data);
        }
    }

    void applyLaplaceOperator() {
        if (channels != 1) {
            std::cerr << "Laplace operator is applicable to grayscale images only." << std::endl;
            return;
        }

        std::vector<unsigned char> laplace_output(width * height);

        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                int center = image_data[y * width + x];
                int sum = 4 * center
                    - image_data[(y - 1) * width + x]
                    - image_data[(y + 1) * width + x]
                    - image_data[y * width + x - 1]
                    - image_data[y * width + x + 1];
                laplace_output[y * width + x] = static_cast<unsigned char>(std::max(0, std::min(255, sum)));
            }
        }

        saveImage("/Users/gleb_kapustin/Desktop/VSU/Operators LRS/Operators LRS/Output images/laplace_output.png", laplace_output);
    }

    void applyRobertsOperator() {
        if (channels != 1) {
            std::cerr << "Roberts operator is applicable to grayscale images only." << std::endl;
            return;
        }

        std::vector<unsigned char> roberts_output(width * height);

        for (int y = 0; y < height - 1; y++) {
            for (int x = 0; x < width - 1; x++) {
                int p1 = image_data[y * width + x];
                int p2 = image_data[y * width + x + 1];
                int p3 = image_data[(y + 1) * width + x];
                int p4 = image_data[(y + 1) * width + x + 1];
                int gx = p1 - p4;
                int gy = p2 - p3;
                int magnitude = std::sqrt(gx * gx + gy * gy);
                roberts_output[y * width + x] = static_cast<unsigned char>(std::max(0, std::min(255, magnitude)));
            }
        }

        saveImage("/Users/gleb_kapustin/Desktop/VSU/Operators LRS/Operators LRS/Output images/roberts_output.png", roberts_output);
    }

    void applySobelOperator() {
        if (channels != 1) {
            std::cerr << "Sobel operator is applicable to grayscale images only." << std::endl;
            return;
        }

        std::vector<unsigned char> sobel_output(width * height);

        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                int gx = (image_data[(y - 1) * width + x - 1] - image_data[(y - 1) * width + x + 1]) +
                         2 * (image_data[y * width + x - 1] - image_data[y * width + x + 1]) +
                         (image_data[(y + 1) * width + x - 1] - image_data[(y + 1) * width + x + 1]);
                int gy = (image_data[(y - 1) * width + x - 1] - image_data[(y + 1) * width + x - 1]) +
                         2 * (image_data[(y - 1) * width + x] - image_data[(y + 1) * width + x]) +
                         (image_data[(y - 1) * width + x + 1] - image_data[(y + 1) * width + x + 1]);
                int magnitude = std::sqrt(gx * gx + gy * gy);
                sobel_output[y * width + x] = static_cast<unsigned char>(std::max(0, std::min(255, magnitude)));
            }
        }

        saveImage("/Users/gleb_kapustin/Desktop/VSU/Operators LRS/Operators LRS/Output images/sobel_output.png", sobel_output);
    }

private:
    void saveImage(const char* filename, const std::vector<unsigned char>& output_data) {
        stbi_write_png(filename, width, height, 1, output_data.data(), width);
        std::cout << "Saved " << filename << std::endl;
    }

    int width;
    int height;
    int channels;
    unsigned char* image_data;
};

