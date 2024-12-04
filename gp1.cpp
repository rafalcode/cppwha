// leave out the haversine.
// note how no freeing of arrays is necessary 
// you can try, but because they are not pointers
#include <iostream>
#include <iomanip>
#include <vector>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <cmath>

using namespace std;

// Class to hold track point data
class TrackPoint {
    public:
        double la;
        double lo;
        double el;

        TrackPoint(double lat, double lon, double ele) 
            : la(lat), lo(lon), el(ele) {}
        // note: latitude(lat) means that the latitude member variable is initialized with the value of lat, usw.

        void print() const {
            std::cout << "Latitude: " << la
                << ", Longitude: " << lo
                << ", Elevation: " << el << std::endl;
        }
};

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

    std::vector<TrackPoint> tps = parseGpx(argv[1]);

    // Output each track point
    // Uses the print method in the class.
    // for (const TrackPoint& point : trackPoints) {
    //     point.print();
    // }
    size_t sz= tps.size();
    size_t sz2=((sz-1)*sz)/2; // total number of pairwise (p-w-) comparisons.
    cout << "Num points= " << sz << " / Num p-w-comparisons= " << sz2 << endl;
    
    vector<double> dvec(sz2); // distance vec

    // double sum=0.;
    size_t k=0;
    for (size_t i = 0; i < sz; ++i) {
        if(i)
            printf("%*c", (int)i*9, ' ');
        for (size_t j = i+1; j < sz; ++j) {
            dvec[k] = sqrt( pow(tps[j].la - tps[i].la, 2) + pow(tps[j].lo - tps[i].lo, 2) );
            // cout << dvec[k] << setw(8) << setprecision(6) << " "; // always so complicated
            printf("%4.6f ", dvec[k]);
            k++;
        }
        printf("\n");
    }

    return 0;
}
