#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <curl/curl.h>
#include <cairo/cairo.h>
#include "tinyxml2.h"

struct GPSPoint {
    double latitude;
    double longitude;
};

// Helper function to download tile using CURL
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool downloadTile(const std::string& url, const std::string& outputPath) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::string tileData;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &tileData);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    FILE* file = fopen(outputPath.c_str(), "wb");
    if (file) {
        fwrite(tileData.c_str(), 1, tileData.size(), file);
        fclose(file);
        return true;
    }
    return false;
}

// Function to calculate OSM tile number from latitude, longitude, and zoom
void latLonToTileXY(double lat, double lon, int zoom, int& x, int& y) {
    int n = 1 << zoom;
    x = int((lon + 180.0) / 360.0 * n);
    y = int((1.0 - std::log(std::tan(lat * M_PI / 180.0) + 1.0 / cos(lat * M_PI / 180.0)) / M_PI) / 2.0 * n);
}

// Function to parse the GPX file as before
std::vector<GPSPoint> parseGPXFile(const std::string& filename) {
    std::vector<GPSPoint> points;
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filename.c_str()) == tinyxml2::XML_SUCCESS) {
        auto track = doc.FirstChildElement("gpx")->FirstChildElement("trk")->FirstChildElement("trkseg");
        for (auto point = track->FirstChildElement("trkpt"); point; point = point->NextSiblingElement("trkpt")) {
            double lat = std::stod(point->Attribute("lat"));
            double lon = std::stod(point->Attribute("lon"));
            points.push_back({ lat, lon });
        }
    } else {
        std::cerr << "Error loading GPX file: " << filename << std::endl;
    }
    return points;
}

// Draw map with GPX trace overlay
void drawMapWithTrace(const std::vector<GPSPoint>& points, const std::string& outputFilename) {
    int width = 800, height = 600;
    int zoom = 15;  // OSM zoom level

    // Determine tile range based on min/max lat/lon
    int xMin, yMin, xMax, yMax;
    latLonToTileXY(points[0].latitude, points[0].longitude, zoom, xMin, yMin);
    latLonToTileXY(points.back().latitude, points.back().longitude, zoom, xMax, yMax);

    // Download tiles and create a surface for each
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t* cr = cairo_create(surface);

    // Loop through each tile within the bounding box and draw it
    for (int x = xMin; x <= xMax; ++x) {
        for (int y = yMin; y <= yMax; ++y) {
            std::string url = "https://tile.openstreetmap.org/" + std::to_string(zoom) + "/" + std::to_string(x) + "/" + std::to_string(y) + ".png";
            std::string tileFilename = "tile_" + std::to_string(zoom) + "_" + std::to_string(x) + "_" + std::to_string(y) + ".png";

            if (downloadTile(url, tileFilename)) {
                cairo_surface_t* tile = cairo_image_surface_create_from_png(tileFilename.c_str());
                if (cairo_surface_status(tile) == CAIRO_STATUS_SUCCESS) {
                    // Position each tile correctly based on x, y coordinates
                    int tileX = (x - xMin) * 256;
                    int tileY = (y - yMin) * 256;
                    cairo_set_source_surface(cr, tile, tileX, tileY);
                    cairo_paint(cr);
                }
                cairo_surface_destroy(tile);
            }
        }
    }

    // Draw the GPS trace on top
    cairo_set_source_rgb(cr, 1, 0, 0);  // Red for the trace
    cairo_set_line_width(cr, 2.0);
    int tileX, tileY;
    latLonToTileXY(points[0].latitude, points[0].longitude, zoom, tileX, tileY);
    cairo_move_to(cr, (tileX - xMin) * 256, (tileY - yMin) * 256);

    for (const auto& point : points) {
        latLonToTileXY(point.latitude, point.longitude, zoom, tileX, tileY);
        cairo_line_to(cr, (tileX - xMin) * 256, (tileY - yMin) * 256);
    }
    cairo_stroke(cr);

    // Save the final image
    cairo_surface_write_to_png(surface, outputFilename.c_str());

    // Clean up
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}

int main()
{
    // Parse GPX file
    std::vector<GPSPoint> points = parseGPXFile("track.gpx");

    // Draw map with trace overlay
    drawMapWithTrace(points, "trace_with_map.png");

    std::cout << "Map with GPX trace saved as trace_with_map.png" << std::endl;

    return 0;
}
