#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

// color output:
//out vec3 ourPosition; // needed for black corner

// offset:
//uniform float xOffset; // needed for x value Offset

void main()
{
	gl_Position = vec4(aPos, 1.0);

    // For offset:
    //gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0); // add the xOffset to the x position of the vertex position
    //ourPosition = aPos; // needed for black corner 


	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
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