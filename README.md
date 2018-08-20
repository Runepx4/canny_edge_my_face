# canny_edge_my_face
Canny edge detection of live stream from the webcam of a laptop.

# Usage
Please run the launch file located in the launch directory.

Example: `roslaunch canny_edge_my_face launch.launch`

The launch file opens a rqt_image_view which should already be setup to subscribe to the correct topic: `/ryb_camera/canny_edge`. 

# Note
The code is not fully optimised. It was created with limited time and to be rather simple to understand.