# Face Rig

The aim of this project is to create an open source C++ solution 
for face rigging. The solution should be minimalistic and fast, 
modular, cross-platform, with simple API.

### Current State

The project currently includes the **Input Pipeline** that retrieves images from a camera,
detects faces and determines a head pose of dominant face using facial landmark detection. 
Further, there is **lightweight render** based on [Phong reflection model](https://en.wikipedia.org/wiki/Phong_reflection_model).
Models are loaded via [Assimp](https://github.com/assimp/assimp) therefore various 
object formats are supported.

Application rigs detected head pose to head model. The render has rather 
general-purpose nature but a facade for face rigging is defined. See the examples below.
****

### Requirements

- [OpenCV](https://opencv.org/) for face detection.

- [Dlib](http://dlib.net/) for facial landmark detection. 
(Will be downloaded & compiled automatically by CMake.)

- [OpenGl](https://www.opengl.org/) for render implementation.


### Usage

You are most likely interested in `FaceRigNoGUI` target, hence do:
```
cmake . && make 
bin/FaceRigNoGUI
```

Target `FaceRig` includes Qt based UI but for the time being 
it is just camera with landmark detection.

### Project Goals

There will be two ways how to use project code. First as library through 
input/output streams. Second as stand-alone application that process webcam 
input and routes rendered output into virtual device that can be set as *default*. 
This will allow to stream rigged face into application like Skype.

Application should also include:

- Mesh Transformation: Possibility to map facial landmark points to model bones 
and transform the mesh according to weights of vertices.

- Gaze detection: Eyes rigging.

- Configuration via UI: Ability to load different models, choose scene and its lighting
and more during runtime via user friendly UI.
