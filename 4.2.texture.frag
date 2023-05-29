#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// color input:
//in vec3 ourPosition; // needed for the black corner

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{

	// color code:
	
	//FragColor = vec4(ourColor, 1.0f);
    //FragColor = vec4(ourPosition, 1.0);    // note how the position value is linearly interpolated to get all the different colors (makes left corner black)





	// texture code:

	//FragColor = texture(texture1, TexCoord);
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2); // for blending 2 textures
	//FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0); // mixes our color and our texture1

}