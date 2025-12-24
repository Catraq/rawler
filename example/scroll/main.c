#include <stdio.h>
#include <stdint.h>

#include <string.h>

#include "math/vec.h"
#include "rl_gui_glfw.h"
#include "rl_gui.h"


int main(int args, char *argv[])
{

	/* First initialize opengl context */
	GLFWwindow* window = 0;
		
	/* Initialize openGL */	
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint( GLFW_SAMPLES, 16 );

	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		fprintf(stderr,"Failed to init GLFW \n");
		glfwTerminate();
		return -1;
	}
	
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

	int width_mm, height_mm;
	glfwGetMonitorPhysicalSize(glfwGetPrimaryMonitor(), &width_mm, &height_mm);

	int res_x, res_y;
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	res_x = mode->width;
	res_y = mode->height;


	glfwSetCharCallback(window, rl_gui_glfw_char_callback);

	glfwMakeContextCurrent(window);
	
  	
       	/* Enable Version 3.3 */
	glewExperimental = 1;
	if(glewInit() != GLEW_OK)
	{
		fprintf(stderr,"Failed to init Glew \n");
		glfwTerminate();
		return -1;
	}


	/* Clear any errors */
	while( glGetError() != GL_NONE)
	{
		glGetError();
	}
	
	glfwSwapBuffers(window);
	glfwPollEvents();

	
	
	int result = 0;
	/* Create gui context */	
	struct rl_gui_context context;
	result = rl_gui_context_initialize(&context, (uint32_t)res_x, (uint32_t)res_y, (uint32_t)width_mm, (uint32_t)height_mm);
	if(result < 0){
		fprintf(stderr, "rl_gui_context_initialize() failed. \n");
		exit(EXIT_FAILURE);
	}


	
	struct rl_gui_render_attribute font_render_attribute = {
		.height_mm = 10,
	};


	const char *font_filename = "../data/UbuntuMono-R.ttf";
	struct rl_gui_object_font font;

	{
		
		result = rl_gui_object_font_freetype_characters_initialize(
				&context,
				&font_render_attribute ,
				&font, 
				font_filename
		);

		if(result < 0)
		{
			fprintf(stderr, "rl_gui_object_font_freetype_characters_initialize() failed. \n");
			exit(EXIT_FAILURE);
		}
	
	}

	
	struct rl_gui_render_attribute list_render_attribute = {
		.height_mm = 3,
		.width_mm = 40, 
	};

	const char *list_entries[] = {
		"Maybe there",
		"is something more",
		"to wish for", 
		"when the world",
		"opens up",
		"and things change",
		"company",
		"a place for two",
		"makes the world",
		"different",
		"some say",
		"loneliness is bad",
		"other say it ends",
		"up with a gui"
	};

	struct rl_gui_object_text_list list_object = {
		.text_color = (struct rl_gui_vec3){.x = 1, .y = 0, .z = 0},
		.selected_text_color = (struct rl_gui_vec3){.x = 0, .y = 1, .z = 0},
		.char_scroll_per_sec = 1.0,

	};
	uint32_t list_entries_length[] = 
	{
		strlen(list_entries[0]), 	
		strlen(list_entries[1]), 	
		strlen(list_entries[2]), 	
		strlen(list_entries[3]), 	
		strlen(list_entries[4]), 	
		strlen(list_entries[5]), 	
		strlen(list_entries[6]), 	
		strlen(list_entries[7]), 	
		strlen(list_entries[8]), 	
		strlen(list_entries[9]), 	
		strlen(list_entries[10]), 	
		strlen(list_entries[11]), 	
		strlen(list_entries[12]), 	
		strlen(list_entries[13]), 	
	};
	
	struct rl_gui_glfw_frame frame = rl_gui_frame_create(window);

	while(!glfwWindowShouldClose(window))
	{

		struct rl_gui_input input = rl_gui_glfw_frame_begin(&frame, window);

		glDisable(GL_SCISSOR_TEST);
		glClearColor(0.1, 0.5, 0.5, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport(
			0, 
			0, 
			input.width_pixel,
			input.height_pixel
		);
		
		glEnable(GL_SCISSOR_TEST);
		
		/* Set the start location to draw too */
		struct rl_gui_result result = {
			.y_mm = context.screen_height_mm * (float)input.height_pixel/(float)context.screen_resolution_y,
		};

	

		result = rl_gui_object_text_list(
				&list_object,
				&context, 
				list_entries,
				list_entries_length,
				13, 
				&font, 
				&list_render_attribute,
				&input, 
				result	
		);

		rl_gui_glfw_frame_end(&frame, &input);	

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	rl_gui_context_deinitialize(&context);

	glfwDestroyWindow(window);
    	glfwTerminate();
}
