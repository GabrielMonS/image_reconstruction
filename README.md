# Image Reconstruction Software
OpenCv based program that reconstructs an image of the part of a reflective surface

The program is intended for use in very specific applications where a lightband appears when illuminating a surface and we want to extract an the information that is near to the lightband(such as scratches that only appear when directly hit by the lightband). It is intended to be used when you have a sequence of images where the surface moves at a constant rate(for example, when using a transport belt) under a fixed light arc.

The program tries to locate the first row of the image that contains the lightband and takes the rows above it and then concatenates the rows extracted from each image to create a final image.
In order for it to work, there are a series of parameters that must be adjusted:
- WHITE_THRESHOLD : The intensity to consider when evaluating if a row contains a lightband. By default, it's set to 255(maximum for 8-bit pixel images).
- WHITE_PERCENTAGE : The minimum percentage of "white" pixels that a row has to have in order to be considered a lightband.
- PIXEL_ADD_HEIGHT : Amount of pixels that will be extracted from each imaxe to compose the final one. It should be as close as possible to the amount of pixels the surface moves between images in order to make a good reconstruction. Larger values will result in an elongated image, while shorter values will result in a compressed image.
- PIXEL_OFFSET : Offset to be applied to the first lightband row before extracting the specified amount of pixels. Useful when the lightband has a slight angle or the corners of the lightband bend a bit in the extremes of the surface.

These parameters can be modified through a YAML file that contains the information. An example file has been provided.


