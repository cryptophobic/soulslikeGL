#version 330 core

layout (location = 0) in vec3 aPos; // position has attribute position 0
layout (location = 1) in vec3 aColor; // color has attribute position 1
out vec3 ourColor; // specify a color output to the fragment shader

void main()
{
    vec3 aPosCopy = aPos;
    aPosCopy[1] = -aPos[1];

    gl_Position = vec4(aPosCopy, 1.0); // we give a vec3 to vec4’s constructor
    ourColor = aColor; // output variable to dark-red
}
