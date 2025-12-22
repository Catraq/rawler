#include "nhgui_list.h"



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

)
{

	float cursor_x_mm = (float)input->width_pixel / (float)context->screen_resolution_x * (float)context->screen_width_mm/(float)input->width_pixel * (float)input->cursor_x_pixel;
	float cursor_y_mm = (float)input->height_pixel / (float)context->screen_resolution_y * (float)context->screen_height_mm/(float)input->height_pixel * (float)input->cursor_y_pixel;


	struct nhgui_result r = result;	
	for(uint32_t i = 0; i < entry_count; i++)
	{
		
		struct nhgui_result result_tmp = r;
		result_tmp.y_mm -= attribute->height_mm;
		
		if(input->cursor_button_left > 0)
		{	
			if(cursor_x_mm > result_tmp.x_mm && cursor_x_mm < result_tmp.x_mm + attribute->width_mm 
			&& cursor_y_mm > result_tmp.y_mm && cursor_y_mm < result_tmp.y_mm + attribute->height_mm)
			{
				if(list->selected_index == i)
					list->selected = list->selected ? 0 : 1;
				else
					list->selected = 1;


				list->selected_index = i;

				if(list->selected > 0)
				{
					input->selected_new_raise = 1;	
				}	
			}	
		}

		if(list->selected > 0 && list->selected_index == i)
		{
		
			struct nhgui_render_attribute selected_attribute = {
				.height_mm = attribute->height_mm,
				.width_mm = attribute->width_mm,
				.r = list->selected_field_color.x,
				.g = list->selected_field_color.y,
				.b = list->selected_field_color.z,
			};

			r = nhgui_icon_blank_no_object(
					context,
					&selected_attribute,
					input,
					r	
			);
			
			list->selected_result = r;

			uint32_t overflow_count_index = 0;
			uint32_t overflow_count = nhgui_object_font_text_overflow_count(
				r,	
				context,
				font,
				attribute,
				entry[i],
				entry_length[i]
			);
			
			
			if(overflow_count > 0 && list->char_scroll_per_sec > 0)
			{
				uint32_t s = input->time_sec/list->char_scroll_per_sec;
				overflow_count_index = s%overflow_count;
			}

			struct nhgui_render_attribute selected_font_attribute = *attribute;
			selected_font_attribute.r = list->selected_text_color.x;
			selected_font_attribute.g = list->selected_text_color.y;
			selected_font_attribute.b = list->selected_text_color.z;

			nhgui_object_font_text(
					context, 
					font, 
					&entry[i][overflow_count_index],
					entry_length[i] - overflow_count,
					&selected_font_attribute,
					input, 
					r	
			);
		}
		else
		{

			struct nhgui_render_attribute _attribute = {
				.height_mm = attribute->height_mm,	
				.width_mm = attribute->width_mm,
				.r = list->field_color.x,
				.g = list->field_color.y,
				.b = list->field_color.z,
			};


			r = nhgui_icon_blank_no_object(
					context,
					&_attribute,
					input,
					r	
			);


			uint32_t overflow_count_index = 0;
			uint32_t overflow_count = nhgui_object_font_text_overflow_count(
				r,	
				context,
				font,
				attribute,
				entry[i],
				entry_length[i]
			);

			if(overflow_count > 0 && list->char_scroll_per_sec > 0)
			{
				uint32_t s = input->time_sec/list->char_scroll_per_sec;
				overflow_count_index = (overflow_count + s)%overflow_count;
			}

			struct nhgui_render_attribute font_attribute = *attribute;
			font_attribute.r = list->text_color.x;
			font_attribute.g = list->text_color.y;
			font_attribute.b = list->text_color.z;

			nhgui_object_font_text(
					context, 
					font, 
					&entry[i][overflow_count_index],
					entry_length[i] - overflow_count,
					&font_attribute,
					input, 
					r	
			);


		}

		if(i != entry_count - 1)
			r = nhgui_result_dec_y(r);

	}

	return r;
}


