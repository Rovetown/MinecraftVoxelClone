#version 330 core

out vec4 FragColor;
in vec3 ourColor;
//in vec3 ourPosition; // needed for the black corner

void main()
{
    FragColor = vec4(ourColor, 1.0f);
    //FragColor = vec4(ourPosition, 1.0);    // note how the position value is linearly interpolated to get all the different colors (makes left corner black)
}