#include <glad/glad.h> // Glad manages function pointers for OpenGL
#include <GLFW/glfw3.h>

#include "shader_s.h" // Use the shader header file from the Solution Explorer
//#include <rovetownshaders/shader_s.h> // Include it as a library header file from include location containing glad and glfw3

#include <iostream>

// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window);

// settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;



const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";





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



	// build and compile our shader program
	// ------------------------------------
	Shader ourShader("3.3.shader.vert", "3.3.shader.frag"); // you can name your shader files however you like


	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// Vertices for a triangle defined as a normaluzed device coordinate (NDC) in a 3D space as a float array
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

	};

	// If we wanna render a rectangle, we need to define the indices of the vertices that make up the rectangle (we dont do that now so its commented out)
	//unsigned int indices[] = {  // note that we start from 0!
	//	0, 1, 3,  // first Triangle
	//	1, 2, 3   // second Triangle
	//};

	unsigned int VBO, VAO;
	/*
		VBO: Vertex buffer object(VBO) for the triangle(first occurence of an OpenGL object); Has a unique ID corresponding to the VBO
		VAO: Vertex array object(VAO) for the triangle; Has a unique ID corresponding to the VAO
	*/

	// Generate a vertex array object name (1 = number of vertex array objects, &VAO = address of vertex array object names)
	glGenVertexArrays(1, &VAO);
	// Generate a buffer object name (1 = number of buffer objects, &VBO = address of buffer object names)
	glGenBuffers(1, &VBO);
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

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);





	// Technical Stuff
	// ---------------------------------------------------------

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Once we go 3D use this (if you do it on fragment shaders it will break the Applications Render:
	//glEnable(GL_DEPTH_TEST);




	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// Input commands here
		processInput(window);

		// Rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// render the triangle
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Shader Setting to move the Triangle by an offset; ourShader.[...] Stuff needs to be called in here!
		// set an offset value and use it to move the triangle to the right
		//float triangle_xPos_offset = 0.5f;
		//ourShader.setFloat("xOffset", triangle_xPos_offset);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);



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