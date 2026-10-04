//
// Created by tobi on 29.09.26.
//

#ifndef RAYTRACER_CANVAS_H
#define RAYTRACER_CANVAS_H
#include <cstddef>

#include <filesystem>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

#include "Color.h"


class Canvas {
public:
    const std::size_t WIDTH;
    const std::size_t HEIGHT;

    std::vector<Color> pixels;

    Canvas(const std::size_t width, const std::size_t height) : WIDTH(width), HEIGHT(height) {
        pixels = std::vector(WIDTH * HEIGHT, Color(0, 0, 0));
    }

    void writePixel(const std::size_t x, const size_t y, const Color &color) {
        const std::size_t pixelCoordinate = y * WIDTH + x;

        pixels.at(pixelCoordinate) = color;
    }

    Color pixelAt(const std::size_t x, const size_t y) const {
        const std::size_t pixelCoordinate = y * WIDTH + x;

        return pixels.at(pixelCoordinate);
    }

    void savePpm() const {
        using namespace std;
        namespace fs = std::filesystem;

        int maxNumber = 0;
        string imagesPath = "../images";

        if (fs::exists(imagesPath) && fs::is_directory(imagesPath)) {
            regex pattern(R"(image(\d+)\.ppm)");

            for (const auto &entry: fs::directory_iterator(imagesPath)) {
                if (entry.is_regular_file()) {
                    string filename = entry.path().filename().string();
                    smatch match;

                    if (regex_match(filename, match, pattern)) {
                        int number = stoi(match[1].str());
                        maxNumber = max(maxNumber, number);
                    }
                }
            }
        }

        int nextNumber = maxNumber + 1;
        std::string outputPath = "../images/image" + std::to_string(nextNumber) + ".ppm";


        ofstream outFile(outputPath);

        if (!outFile) {
            cerr << "Error with opening file!" << endl;
            return;
        }

        // Header defines ppm type, color and image size
        std::string header = "P3\n" + std::to_string(WIDTH) + " " + std::to_string(HEIGHT) + "\n255\n";


        stringstream body;
        int linelength = 0;

        for (int i = 0; i < pixels.size(); i++) {
            const Color &color = pixels.at(i);

            // Color values are multiplied to be an int, while higher or lower values are clamped to max or min respecfully
            int red = clamp((int) (round(color.red() * 255)), 0, 255);
            int green = clamp((int) (round(color.green() * 255)), 0, 255);
            int blue = clamp((int) (round(color.blue() * 255)), 0, 255);

            std::string pixelData = std::to_string(red) + " " + std::to_string(green) + " " + std::to_string(blue);
            int size = pixelData.size();

            linelength += size;

            if (linelength > 70) {
                body << "\n";
                body << pixelData;
                body << " ";
                linelength = size + 1;
            } else {
                body << pixelData;
                body << " ";
                linelength++;
            }
        }

        body << "\n";

        outFile << header;
        outFile << body.str();

        outFile.close();
    }

private:
};


#endif //RAYTRACER_CANVAS_H
