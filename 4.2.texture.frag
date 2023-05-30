#version 330 core
out vec4 FragColor;

//in vec3 ourColor;
in vec2 TexCoord;

// color input:
//in vec3 ourPosition; // needed for the black corner

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

/* CASE 03:
	Use a uniform variable as the mix function's third parameter
	to vary the amount the two textures are visible.
	Use the up and down arrow keys to change how much the container
	or the smiley face is visible:
*/
//uniform float mixValue;


void main()
{

	// color code:
	
	//FragColor = vec4(ourColor, 1.0f);
    //FragColor = vec4(ourPosition, 1.0);    // note how the position value is linearly interpolated to get all the different colors (makes left corner black)



	// CASE 03:
	// linearly interpolate between both textures
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);





	// texture code:

	//FragColor = texture(texture1, TexCoord);
	// linearly interpolate between both textures
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2); // for blending 2 textures
	//FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0); // mixes our color and our texture1



	// How to make sure only the happy face looks in the other/reverse direction by changing the fragment shader:
	//FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);

}