#include <glad/glad.h> // Glad manages function pointers for OpenGL
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image/stb_image.h>
//#include <stb_image/stb_image.h> // Include it as a library header file from include location containing glad and glfw3

#include "shader_s.h" // Use the shader header file from the Solution Explorer
//#include <rovetownshaders/shader_s.h> // Include it as a library header file from include location containing glad and glfw3

#include <iostream>



// For more info visit: https://learnopengl.com/Getting-started/OpenGL



// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window);

// settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;


// CASE 03: UNIFORM MIX VALUE FOR SHADER
// stores how much we're seeing of either texture
//float mixValue = 0.2f;


int main()
{

	// glfw: initialize and configure
	// ------------------------------
	//glfwInit();

	// Also initializes GLFW but we set this up to print Error messages to console if GLFW fails to initialize
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// The following needs to be added for Mac OS X ONLY:
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif



	// glfw window creation
	// --------------------
	// Create a GLFWwindow object of 800 by 600 pixels, naming it "Minecraft Clone"
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minecraft Clone", NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Set the current context to the newly created window
	glfwMakeContextCurrent(window);

	// Tell OpenGL to call framebuffer_size_callback() whenever the window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	/*
		If glad wasn't initialized, else it is initialized
		(important, needs to be initialized after glfwMakeContectCurrent(window);)
	*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}



	// build and compile our shader zprogram
	// ------------------------------------
	Shader ourShader("4.2.texture.vert", "4.2.texture.frag");

	// compile and link the color shader program
	Shader Wireframe("Wireframe.vert", "Wireframe.frag"); // Assuming you have color.vert and color.frag shaders


	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------


	// If you use colors (idk if it works, outdated)
	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	//};

	float vertices[] = {
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};

	// If we wanna render a rectangle, we need to define the indices of the vertices that make up the rectangle (comment indeces out if you want a triangle)
	unsigned int indices[] = { // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};







	/* CASE 01:
		Experiment with the different texture wrapping methods by
		specifying texture coordinates in the range 0.0f to 2.0f
		instead of 0.0f to 1.0f. This below will show 4 smiley faces
		on a single container image clamped at its edge:	
	*/


	/*
		float vertices[] = {
        // positions          // colors           // texture coords (note that we changed them to 2.0f!) | from bottom row to top = range[0.0f bis 2.0f]
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left 
		};
	*/











	/* CASE 02:
		Try to display only the center pixels of the texture image on the rectangle
		in such a way that the individual pixels are getting visible by changing the texture coordinates.
		Try to set the texture filtering method to GL_NEAREST to see the pixels more clearly:
	*/




	/*
		float vertices[] = {
        // positions          // colors           // texture coords (note that we changed them to 'zoom in' on our texture image)
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.55f, 0.55f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.55f, 0.45f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.45f, 0.45f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.45f, 0.55f  // top left 
		};
	*/









	unsigned int VBO, VAO, EBO;
	/*
		VBO: Vertex buffer object(VBO) for the triangle(first occurence of an OpenGL object); Has a unique ID corresponding to the VBO
		VAO: Vertex array object(VAO) for the triangle; Has a unique ID corresponding to the VAO
		EBO: Element buffer object(EBO) for the triangle; Has a unique ID corresponding to the EBO
	*/

	// Generate a vertex array object name (1 = number of vertex array objects, &VAO = address of vertex array object names)
	glGenVertexArrays(1, &VAO);
	// Generate a buffer object name (1 = number of buffer objects, &VBO = address of buffer object names)
	glGenBuffers(1, &VBO);
	// Generate a buffer object name (1 = number of buffer objects, &EBO = address of buffer object names)
	glGenBuffers(1, &EBO);


	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);


	// Bind the buffer object to a buffer type target (GL_ARRAY_BUFFER = vertex attributes)
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Only works as long as we have different buffer types
	// Copy the vertex data into the buffer's memory (GL_STATIC_DRAW = data will most likely not change)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // We can make a call to this to copy the data into the buffers memory
	/*
		GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
		GL_STATIC_DRAW: the data is set only once and used many times.
		GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
	*/

	// Bind the element buffer object to a buffer type target (GL_ELEMENT_ARRAY_BUFFER = vertex attributes)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	/*
		GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
		GL_STATIC_DRAW: the data is set only once and used many times.
		GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
	*/

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute (for shader with color only)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);










	// load and create a texture 
	// -------------------------
	unsigned int texture1, texture2;
	// texture 1
	// ---------
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);




	// NEEDED FOR CASE 02: (dont use at the moment since it was only used for an example)
	// set texture filtering parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // set texture filtering to nearest neighbor to clearly see the texels/pixels
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	
	
	
	
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load("resources/textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// texture 2
	// ---------
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load("resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
	// either set it manually like so:
	//glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	// or set it via the texture class
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);





	// Technical Stuff
	// ---------------------------------------------------------

	// Once we go 3D use this (if you do it on fragment shaders it will break the Applications Render and show no shader (so only background color):
	//glEnable(GL_DEPTH_TEST);






	bool WireframeActivated = false;
	bool F2KeyPressed = false;

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		


		// WireframeMode
		if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS && !F2KeyPressed) {
			WireframeActivated = !WireframeActivated; // Switches between true and false
			F2KeyPressed = true; // So it doesn't keep switching and bugs out (becuase of how Windows registers the keypress by glfw3)
		}
		else if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_RELEASE) // needs to be released so it can be pressed again (so it doesn't keep switching)
		{
			F2KeyPressed = false;
		}

		if (WireframeActivated) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe
			Wireframe.use(); // For every shader we wanna use we need to compile n build it first in main()
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Default
			ourShader.use();
		}




		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);







		// Used for the rotating square
		
		 // create transformations
		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f)); // this moves the position of the square (0,0,0 = center of window)
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		// get matrix's uniform location and set matrix (add new ones for each new shader)
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		unsigned int transformLocWireframe = glGetUniformLocation(Wireframe.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glUniformMatrix4fv(transformLocWireframe, 1, GL_FALSE, glm::value_ptr(transform));







		// render container
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/* Old Triangle Code
		
		// render the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		Shader Setting to move the Triangle by an offset; ourShader.[...] Stuff needs to be called in here!
		set an offset value and use it to move the triangle to the right
		loat triangle_xPos_offset = 0.5f;
		ourShader.setFloat("xOffset", triangle_xPos_offset);

		*/
		


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}