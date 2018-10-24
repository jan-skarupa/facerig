#include <iostream>

#include "render/render.h"

#include "input_pipeline/camera_resolution.h"
#include "input_pipeline/input_source.h"
#include "input_pipeline/webcam.h"
#include "input_pipeline/analyzers/face_detector.h"
#include "input_pipeline/analyzers/face_detector_harr.h"
#include "input_pipeline/analyzers/landmark_detector.h"
#include "input_pipeline/analyzers/landmark_detector_dlib.h"
#include "input_pipeline/analyzers/feature_detector.h"

int main(int argc, char* argv[])
{
    WindowSize render_window(800, 600);
    Camera render_camera(glm::vec3(15.0, 5.0, 0.0), glm::vec3(0.0, 5.0, 0.0));
    std::unique_ptr<Render> render = std::make_unique<Render>(render_camera, render_window);

    Light light(glm::vec3(10.0f, 15.0f, 10.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    render->set_light(light);


    glm::mat4 normalization(1.0);
    normalization = glm::scale(normalization, glm::vec3(1.2, 1.2, 1.2));
    normalization = glm::translate(normalization, glm::vec3(0, 5.0, 0));
    normalization = glm::rotate(normalization, 1.55f, glm::vec3(0.0f, 1.0f, 0.0f));

    unsigned int head = render->add_model("../resources/puppets/cartoon/head.obj", normalization);


    CamResolution cam_res(1280, 720);
    std::unique_ptr<InputSource> webcam = std::make_unique<WebCamera>();
    std::unique_ptr<FaceDetector> face_detector = std::make_unique<FaceDetectorHarr>("../resources/face_detection/haarcascade_frontalface_alt.xml");
    std::unique_ptr<LandmarkDetector> landmark_detector = std::make_unique<LandmarkDetectorDlib>("../resources/face_detection/shape_predictor_68_face_landmarks.dat");
    FeatureDetector feature_detector(cam_res);

    cv::Rect tracked_face;
    std::array<cv::Point, 68> face_landmarks;
    std::array<float,3> face_rotation = {0, 0, 0};

    webcam->open_stream(0, cam_res);
    while (true)
    {
        cv::Mat image = webcam->get_image();
        std::vector<cv::Rect> faces = face_detector->detect_faces(image);

        if (!faces.empty()) {
            tracked_face = face_detector->find_tracked_face(faces, tracked_face);
            face_landmarks = landmark_detector->detect_landmarks(image, tracked_face);
            face_rotation = feature_detector.detect_face_direction(face_landmarks);

            cv::cvtColor(image, image, CV_BGR2GRAY);
            cv::cvtColor(image, image, CV_GRAY2BGR);

            cv::rectangle(image, tracked_face, cv::Scalar(0, 0, 255));
            for (auto mark : face_landmarks) {
                cv::circle(image, cv::Point(mark.x, mark.y), 1, cv::Scalar(0,0,0), -1);
            }
        } else {
            cv::cvtColor(image, image, CV_BGR2GRAY);
        }

        cv::imshow("WebCam output", image);

        int keycode = cv::waitKey(30);
        // if (keycode == 27)
        if (keycode > 0)
            break;

        glm::mat4 rotation_matrix(1.0);
        rotation_matrix = glm::rotate(rotation_matrix,  face_rotation[0], glm::vec3(1.0f, 0.0f, 0.0f));  // forward-back
        rotation_matrix = glm::rotate(rotation_matrix, -face_rotation[1], glm::vec3(0.0f, 1.0f, 0.0f));  // x-rotation
        rotation_matrix = glm::rotate(rotation_matrix, -face_rotation[2], glm::vec3(0.0f, 0.0f, 1.0f));  // tilt

        render->set_model_transformation(head, rotation_matrix);
        render->render_scene();

    }
    webcam->close_stream();
    glfwSetWindowShouldClose(render->window, true);


    return 0;
}