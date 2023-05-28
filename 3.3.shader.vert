#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
//out vec3 ourPosition; // needed for black corner

uniform float xOffset; // needed for x value Offset (doesnt work)

void main()
{
    //gl_Position = vec4(aPos, 1.0);
    gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0); // add the xOffset to the x position of the vertex position
    ourColor = aColor;
    //ourPosition = aPos; // needed for black corner    
}

// Shader for upside down Triangle
/*
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0); // just add a - to the y position
    ourColor = aColor;
}
*/

