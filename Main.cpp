#include <glad/glad.h> // Glad manages function pointers for OpenGL
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// stb_image.h is used to load images for textures
#include <stb_image/stb_image.h>
//#include <stb_image/stb_image.h> // Include it as a library header file from include location containing glad and glfw3

// This was used for 2D, not needed for 3D
	//#include "shader_s.h" // Use the shader header file from the Solution Explorer
	////#include <rovetownshaders/shader_s.h> // Include it as a library header file from include location containing glad and glfw3

#include "shader_m.h" // Use the shader header file from the Solution Explorer
//#include <rovetownshaders/shader_m.h> // Include it as a library header file from include location containing glad and glfw3

#include "camera.h" // Use the camera header file from the Solution Explorer
//#include <rovetownshaders/camera.h> // Include it as a library header file from include location containing glad and glfw3

#include <iostream>



// For more info visit: https://learnopengl.com/Getting-started/OpenGL



// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// mouse_callback is called whenever the mouse moves
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// scroll_callback is called whenever the mouse scroll wheel scrolls
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window);

// settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const unsigned int FOV = 45.0f;
const unsigned int nearPlane = 0.1f;
const unsigned int farPlane = 100.0f;

const unsigned int view_x = 0.0f; // 0.0f = default | Width
const unsigned int view_y = 0.0f; // 0.0f = default | Height
const unsigned int view_z = -3.0f; // -3.0f = default | Depth

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// CASE 03: UNIFORM MIX VALUE FOR SHADER
// stores how much we're seeing of either texture
//float mixValue = 0.2f;

// Wireframe Mode

bool WireframeActivated = false;
bool F2KeyPressed = false;

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
	// Cursor Position Callback
	glfwSetCursorPosCallback(window, mouse_callback);
	// Scroll Callback
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	/*
		If glad wasn't initialized, else: it is initialized
		(important, needs to be initialized after glfwMakeContectCurrent(window);)
	*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // glfwGetProcAddress: Loads the address of the OpenGL function pointers
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate(); // Terminate GLFW (This is not in the original code, but i included it for good reasons i guess???)
		return -1;
	}

	// Once we go 3D use this (if you do it on fragment shaders it will break the Applications Render and show no shader (so only background color):
	// This sets the OpenGL state so that it knows how to draw the vertices properly (this is now enabled since 3d coordinates are used)
	glEnable(GL_DEPTH_TEST); // Enable depth testing (3D)


	// Wireframe Shader
	// compile and link the color shader program
	Shader Wireframe("Wireframe.vert", "Wireframe.frag"); // Assuming you have color.vert and color.frag shaders

	// Shader
	// build and compile our shader zprogram
	// ------------------------------------
	Shader ourShader("7.4.camera.vert", "7.4.camera.frag");





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

	// This is outdated (It is used for 2d coordinates, so if this is split into 2d/3d engines, delete 3d and use this one)
		//float vertices[] = {
		//	// positions          // texture coords
		//	 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		//	 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		//	-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
		//};

		// If we wanna render a rectangle, we need to define the indices of the vertices that make up the rectangle (comment any one indeces out if you want a triangle)
		//unsigned int indices[] = { // note that we start from 0!
		//	0, 1, 3, // first triangle
		//	1, 2, 3  // second triangle
		//};







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


	// I think this is how we setup objects in a scene, i probably need a way to not have this like this (automate it or smth)
	// Cube Vertices Setup (3D) - Part of Vertex Data Setup
	// ------------------------------------------------------------------

	// Vertex Data and vertex attribute config for a cube (3D - copied directly from LearnOpenGL Source Code)
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	// world space positions of our cubes
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};





	// Also use EBO later on for Objects with more complex shapes to gain performance
	unsigned int VBO, VAO;
	/*
		VBO: Vertex buffer object(VBO) for the triangle(first occurence of an OpenGL object); Has a unique ID corresponding to the VBO
		VAO: Vertex array object(VAO) for the triangle; Has a unique ID corresponding to the VAO
		EBO: Element buffer object(EBO) for the triangle; Has a unique ID corresponding to the EBO
	*/

	// Generate a vertex array object name (1 = number of vertex array objects, &VAO = address of vertex array object names)
	glGenVertexArrays(1, &VAO);
	// Generate a buffer object name (1 = number of buffer objects, &VBO = address of buffer object names)
	glGenBuffers(1, &VBO);
	// Use this later for Objects with more complex shapes to increase performance
		// Generate a buffer object name (1 = number of buffer objects, &EBO = address of buffer object names)
		//glGenBuffers(1, &EBO);


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

	// Use this later for Objects with more complex shapes to increase performance
		//// Bind the element buffer object to a buffer type target (GL_ELEMENT_ARRAY_BUFFER = vertex attributes)
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		//*
		//	GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
		//	GL_STATIC_DRAW: the data is set only once and used many times.
		//	GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
		//*/

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute (for shader with color only) - in 3D currently not needed, not sure if would work in 3D
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); //prev 2, 2 in the 2D version
	glEnableVertexAttribArray(1); //prev 2 in the 2D version

	

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


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic (basically the delta time you know from Unity, Godot and Unreal Engine)
		// --------------------
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// WireframeMode
		if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS && !F2KeyPressed) {
			WireframeActivated = !WireframeActivated; // Switches between true and false
			F2KeyPressed = true; // So it doesn't keep switching and bugs out (because of how Windows registers the keypress by glfw3)
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
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // This is the background color (RGBA)
		// This is needed for 2D only, use the one below for 3D
		//glClear(GL_COLOR_BUFFER_BIT);

		// This is needed for 3D only, use the one above for 2D
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Also clear the depth buffer now! Hence the additional clear flag. (3D)

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);



		// Since we use Shaders in combination with transformations, we need to use the shader in the render loop
		ourShader.use();


		// Used for the rotating square
		
		// create transformations
		
		// This was used instead of shaders/the one below for 2D, not used for 3D
			//glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		




		// pass projection matrix to shader (note that in this case it could change every frame
		
		// VERSION 1: WITHOUT CAMERA CLASS since it is not changing every frame
		//glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first (Identity Matrix = 1.0f)
		//projection = glm::perspective(glm::radians((float)FOV), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, (float)nearPlane, (float)farPlane); // 45.0f = FOV, 0.1f = near plane, 100.0f = far plane | Set in settings section


		// VERSION 2: WITH CAMERA CLASS
		//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, (float)nearPlane, (float)farPlane);


		// Projection Matrix (3D)
		// VERSION 1: WITHOUT CAMERA CLASS since it is not changing every frame
		//glm::mat4 projection = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3((float)view_x, (float)view_y, (float)view_z)); // 0.0f, 0.0f, -3.0f = x, y, z | Set in settings section

		// VERSION 2: WITH CAMERA CLASS
		//glm::mat4 view = camera.GetViewMatrix();
		

		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);


		// pass transformation matrices to the shader [I can group this  for the main version together with the respective matrix]
		//ourShader.setMat4("projection", projection); // This sets the projection matrix for the cube
		//ourShader.setMat4("view", view); // This sets the view matrix for the cube

		// This was for 2D, which is why we did not need to use outShader.use(); inside the Render Loop. In 3D you need to.
			//transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f)); // this moves the position of the square (0,0,0 = center of window)
			//transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
			//
			//// get matrix's uniform location and set matrix (add new ones for each new shader)
			//unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
			//unsigned int transformLocWireframe = glGetUniformLocation(Wireframe.ID, "transform");
			//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
			//glUniformMatrix4fv(transformLocWireframe, 1, GL_FALSE, glm::value_ptr(transform));





		//Here is commented code that'll make the square rotate around the screen
		/*
			// create transformations
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); // switched the order
			transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f)); // switched the order
		*/

		/*	Why does our container now spin around our screen?:
			== ===================================================
			Remember that matrix multiplication is applied in reverse. This time a translation is thus
			applied first to the container positioning it in the bottom-right corner of the screen.
			After the translation the rotation is applied to the translated container.
			
			A rotation transformation is also known as a change-of-basis transformation
			for when we dig a bit deeper into linear algebra. Since we're changing the
			basis of the container, the next resulting translations will translate the container
			based on the new basis vectors. Once the vector is slightly rotated, the vertical
			translations would also be slightly translated for example.
			
			If we would first apply rotations then they'd resolve around the rotation origin (0,0,0), but
			since the container is first translated, its rotation origin is no longer (0,0,0) making it
			looks as if its circling around the origin of the scene.
			
			If you had trouble visualizing this or figuring it out, don't worry. If you
			experiment with transformations you'll soon get the grasp of it; all it takes
			is practice and experience.
		*/







		// Code to draw a 2nd Container, but placed in a different position using transformations only
		/*
			glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			// first container
			// ---------------
			transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
			transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
			// get their uniform location and set matrix (using glm::value_ptr)
			unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

			// with the uniform matrix set, draw the first container (remove the below one if using these:)
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			// second transformation
			// ---------------------
			transform = glm::mat4(1.0f); // reset it to identity matrix
			transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
			float scaleAmount = static_cast<float>(sin(glfwGetTime()));
			transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]); // this time take the matrix value array's first element as its memory pointer value

			// now with the uniform matrix being replaced with new transformations, draw it again.
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		*/
		









		// Render Object(s)

		// THis draws the 2D Container
			//// render container
			//glBindVertexArray(VAO);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/* Old Triangle Code
		
		// render the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		Shader Setting to move the Triangle by an offset; ourShader.[...] Stuff needs to be called in here!
		set an offset value and use it to move the triangle to the right
		loat triangle_xPos_offset = 0.5f;
		ourShader.setFloat("xOffset", triangle_xPos_offset);

		*/

		// Render boxes (3D)
		// ------------------------------------------------------------------
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++) { // 10 = number of cubes, change it to 1 if you only want 1 cube, etc.
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f); // This sets the model matrix to 1.0f (default) which is the identity matrix
			model = glm::translate(model, cubePositions[i]); // Set the cube model to the cube positions
			float angle = 20.0f * i; // 20.0f = angle | i = cube number [This Angle sets the Angle we view the Cube from]
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f)); // This rotates the cube along the vec3 axis
			ourShader.setMat4("model", model); // This sets the model matrix for the cube

			glDrawArrays(GL_TRIANGLES, 0, 36); // 0 = starting index, 36 = number of vertices
		}
		


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// Needed if we use EBO's (which we will later on)
	//glDeleteBuffers(1, &EBO);

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

	// Camera Movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}