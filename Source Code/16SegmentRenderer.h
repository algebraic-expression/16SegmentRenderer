#pragma once

#include <SDL.h>
#include <unordered_map>

#define VERSION "1.0"


extern const std::unordered_map<char, const uint16_t> char_mask;


/**
 * @brief Obtain the mask for a character.
 */
uint16_t get_mask(const char c);


/**
 * @brief Render a specific segment of a character in the display.
 * @param renderer The SDL_Renderer instance.
 * @param segment The segment number; the order is CW/RTL layout.
 * @param origin The top-left corner point of the character, w.r.t. which
 * segment position is calculated.
 * @param seg_len The length of each of the segments. (Half of character
 * length and breadth.)
 * @param thickness The number of pixels wide each segment spans.
 */
void render_segment(SDL_Renderer* renderer,
					const uint8_t segment,
					SDL_FPoint origin,
					const float seg_len,
					int thickness = 1);


/**
 * @brief Render a dot on a segment at a specific spot on it.
 * @param pos The number of pixels away from the origin of the segment.
 * @param size The side length of the square that forms the dot.
 */
void render_dot_on_segment(SDL_Renderer* renderer,
						   const uint8_t segment,
						   SDL_FPoint origin,
						   const float seg_len,
						   const float pos,
						   const float size);

void render_dot(SDL_Renderer* renderer,
				SDL_FPoint dot,
				const float size);

/// @note Draw a dot w.r.t. the origin of the character on the display.
void render_dot(SDL_Renderer* renderer,
				SDL_FPoint origin,
				float del_x,
				float del_y,
				const float size);

void render_mask(SDL_Renderer* renderer,
				 const uint16_t mask,
				 SDL_FPoint origin,
				 const float char_len,
				 int thickness = 1);

void render_char(SDL_Renderer* renderer,
				 const char chr,
				 SDL_FPoint origin,
				 const float char_len,
				 int thickness = 1);

void render_text(SDL_Renderer* renderer,
				 const char text[],
				 SDL_FPoint origin,
				 const float char_len,
				 int char_sep,
				 int thickness = 1);
