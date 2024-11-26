// cha, 
#include <iostream>
#include <iomanip>
#include <vector>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <cmath>

// Constants
constexpr double EARTH_RADIUS = 6371000.0; // Earth radius in meters

// Class to hold track point data
class TrackPoint {
    public:
        double latitude;
        double longitude;
        double elevation;

        TrackPoint(double lat, double lon, double ele) 
            : latitude(lat), longitude(lon), elevation(ele) {}
        // note: latitude(lat) means that the latitude member variable is initialized with the value of lat, usw.

        void print() const {
            std::cout << "Latitude: " << latitude 
                << ", Longitude: " << longitude 
                << ", Elevation: " << elevation << std::endl;
        }
};

// Haversine formula to calculate distance between two points (ignoring elevation)
double haversineDistance(TrackPoint& pt1, TrackPoint& pt2)
{
    double lat1 = M_PI * pt1.latitude / 180.;
    double lat2 = M_PI * pt2.latitude / 180.;
    double lon1 = M_PI * pt1.longitude / 180.;
    double lon2 = M_PI * pt2.longitude / 180.;

    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dLon / 2) * std::sin(dLon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    double horDist = EARTH_RADIUS * c; // Distance in meters

    double elevationDifference = pt2.elevation - pt1.elevation;

    return std::sqrt(horDist * horDist +
                     elevationDifference * elevationDifference);

}

// Function to parse GPX file and return a vector of TrackPoints
std::vector<TrackPoint> parseGpx(const char* filename)
{
    std::vector<TrackPoint> trackPoints;

    xmlDoc* doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL) {
        std::cerr << "Error: unable to parse file " << filename << std::endl;
        return trackPoints;
    }

    xmlNode* root = xmlDocGetRootElement(doc);

    for (xmlNode* node = root->children; node; node = node->next) {
        if (xmlStrcmp(node->name, BAD_CAST "trk") == 0) {
            for (xmlNode* trkseg = node->children; trkseg; trkseg = trkseg->next) {
                if (xmlStrcmp(trkseg->name, BAD_CAST "trkseg") == 0) {
                    for (xmlNode* trkpt = trkseg->children; trkpt; trkpt = trkpt->next) {
                        if (xmlStrcmp(trkpt->name, BAD_CAST "trkpt") == 0) {
                            // Get latitude and longitude attributes
                            xmlChar* latStr = xmlGetProp(trkpt, BAD_CAST "lat");
                            xmlChar* lonStr = xmlGetProp(trkpt, BAD_CAST "lon");

                            double latitude = latStr ? atof((char*)latStr) : 0.0;
                            double longitude = lonStr ? atof((char*)lonStr) : 0.0;

                            // Get elevation child node
                            double elevation = 0.0;
                            xmlNode* eleNode = trkpt->children;
                            while (eleNode && xmlStrcmp(eleNode->name, BAD_CAST "ele") != 0) {
                                eleNode = eleNode->next;
                            }
                            if (eleNode) {
                                xmlChar* eleStr = xmlNodeGetContent(eleNode);
                                elevation = eleStr ? atof((char*)eleStr) : 0.0;
                                xmlFree(eleStr);
                            }

                            // Create TrackPoint and add to vector
                            trackPoints.emplace_back(latitude, longitude, elevation);

                            xmlFree(latStr);
                            xmlFree(lonStr);
                        }
                    }
                }
            }
        }
    }
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return trackPoints;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <gpx file>" << std::endl;
        return 1;
    }

    std::vector<TrackPoint> trackPoints = parseGpx(argv[1]);


    // Output each track point
    // Uses the print method in the class.
    // for (const TrackPoint& point : trackPoints) {
    //     point.print();
    // }
    trackPoints[0].print();
    trackPoints[1].print();
    trackPoints[2].print();
    size_t sz= trackPoints.size();
    trackPoints[sz-3].print();
    trackPoints[sz-2].print();
    trackPoints[sz-1].print();
    double sum=0.;
    for (size_t j = 1; j < sz; ++j) {
        sum += haversineDistance(trackPoints[0], trackPoints[j]);
        // std::cout << sum << std::setw(8) << std::setprecision(4) << " ";
        printf("%4.4f ", sum);
    }
    std::cout << std::endl;
    // pair wise
    // for (size_t i = 0; i < trackPoints.size()-1; ++i) {
    //     for (size_t j = 1; j < trackPoints.size(); ++j) {
    //         std::cout << haversineDistance(trackPoints[i], trackPoints[j]) << std::setw(8) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}
