#ifndef NHGUI_LIST_H
#define NHGUI_LIST_H

#include "nhgui.h"

struct nhgui_object_text_list
{
	
	/* Color of text and background of none selected */
	struct nhgui_vec3 text_color;
	struct nhgui_vec3 field_color;

	/* Color of text and background of selected */
	struct nhgui_vec3 selected_field_color;
	struct nhgui_vec3 selected_text_color;
	
	/* > 0, then scroll the text if it overflows */
	float char_scroll_per_sec;
	
	/* > 0 if anything is selected */
	uint32_t selected;

	/* Index of the selcted */
	uint32_t selected_index;
	
	/* Used internaly */	
	uint32_t selected_prev;

	/* Result of the selected background */
	struct nhgui_result selected_result;

};


/*
 * attribute height sets font height and width sets the width 
 * of the list object. 
 */
struct nhgui_result
nhgui_object_text_list(
		struct nhgui_object_text_list *list,
		const struct nhgui_context *context,
		const char *entry[],
		const uint32_t *entry_length,
		const uint32_t entry_count,
		const struct nhgui_object_font *font,
		const struct nhgui_render_attribute *attribute,
		struct nhgui_input *input, 
		const struct nhgui_result result

);

#endif 

