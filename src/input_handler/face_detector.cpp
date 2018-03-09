#include "face_detector.h"


class FaceDetectorHarr : public FaceDetector {
public:
    explicit FaceDetectorHarr(const char* detector_source)
    {
        if (!face_classifier.load(detector_source)) {
            std::cout << "Classifier not loaded" << std::endl;
            throw;
        }
    }

    cv::Rect detect_face(const cv::Mat& frame) override;

private:
    cv::CascadeClassifier face_classifier;
};


cv::Rect FaceDetectorHarr::detect_face(const cv::Mat &frame)
{
    std::vector<cv::Rect> faces;
    face_classifier.detectMultiScale(frame, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE | CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(150, 150));

    if (faces.empty()) {
        return cv::Rect();
    }
    return faces[0];
}

std::unique_ptr<FaceDetector> make_harr_face_detector(const char* source_filepath)
{
    return std::make_unique<FaceDetectorHarr>(source_filepath);
}
