#include "cluon-complete.hpp"
#include "opendlv-standard-message-set.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Tracker.hpp"
#include "Angler.hpp"
#include "Printer.hpp"

int main(int argc, char **argv) {
    auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);
    if (commandlineArguments.count("cid") == 0 || commandlineArguments.count("name") == 0) {
        std::cerr << "Usage: " << argv[0] << " --cid=<OD4 session> --name=<shared memory area name>\n";
        return 1;
    }

    const std::string NAME = commandlineArguments["name"];
    cluon::OD4Session od4{static_cast<uint16_t>(std::stoi(commandlineArguments["cid"]))};
    cluon::SharedMemory sharedMemory{NAME};
    if (!sharedMemory.valid()) {
        std::cerr << "Failed to attach to shared memory: " << NAME << std::endl;
        return 1;
    }

    Tracker tracker;
    Angler angler;
    Printer printer;
    std::string writePath = "/tmp/lightning.csv";
    printer.clearFile(writePath);
    printer.writeToFile(writePath, "time,gsr\n");

    while (od4.isRunning()) {
        sharedMemory.wait();
        sharedMemory.lock();
        cv::Mat img(480, 640, CV_8UC4, sharedMemory.data());  // Assuming image size 640x480 for simplicity
        sharedMemory.unlock();

        // Process the image to get cones' positions
        auto [pointA, pointB] = tracker.trackObjects(img);
        float conesAngle = angler.getAngle(pointA, pointB);
        int turn_dir = angler.leftRightDeterminer(pointA, pointB);
        float ourGSR = angler.angleToGSR(conesAngle, turn_dir);

        // Log GSR value
        std::clog << "GSR: " << ourGSR << std::endl;
        printer.writeToFile(writePath, std::to_string(cluon::time::toMicroseconds(cluon::time::now())) + "," + std::to_string(ourGSR) + "\n");

        if (commandlineArguments.count("verbose") != 0) {
            cv::imshow("Debug Window", img);
            cv::waitKey(1);
        }
    }

    return 0;
}
