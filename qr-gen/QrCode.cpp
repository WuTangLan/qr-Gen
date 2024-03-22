#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "qrcodegen.hpp"

using qrcodegen::QrCode;

// Function prototype
static std::string toSvgString(const QrCode& qr, int border);

int main() {
    // Ask the user for input
    std::string userInput;
    std::cout << "Enter text for QR Code generation: ";
    std::getline(std::cin, userInput);

    // Generate QR Code from user input
    const QrCode qr = QrCode::encodeText(userInput.c_str(), QrCode::Ecc::LOW);

    // Convert QR Code to SVG code
    const std::string svgCode = toSvgString(qr, 4);

    // Save SVG code to file
    std::ofstream file("qr.svg");
    file << svgCode;
    file.close();

    std::cout << "QR Code saved as qr.svg" << std::endl;

    return 0;
}

static std::string toSvgString(const QrCode& qr, int border) {
    // Create an output stream for SVG code
    std::ostringstream sb;

    // Start SVG document
    sb << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    sb << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
    sb << (qr.getSize() + border * 2) << " " << (qr.getSize() + border * 2) << "\" stroke=\"none\">\n";
    sb << "\t<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/>\n";

    // Add path for each QR Code module
    sb << "\t<path d=\"";
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            if (qr.getModule(x, y)) {
                if (x != 0 || y != 0)
                    sb << " ";
                sb << "M" << (x + border) << "," << (y + border) << "h1v1h-1z";
            }
        }
    }
    sb << "\" fill=\"#000000\"/>\n";
    sb << "</svg>\n";

    // Return the SVG code as a string
    return sb.str();
}
