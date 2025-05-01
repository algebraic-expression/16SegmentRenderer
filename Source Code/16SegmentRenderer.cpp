#include "SegmentedRenderer.h"

const std::unordered_map<char, const uint16_t> char_mask =
{
	{'\0', (uint16_t)(-1)},
	{'!', 0b0100100000000000},
	{'"', 0b0000000010000100},
	{'#', 0b0100101111110000},
	{'$', 0b0100101110111011},
	{'%', 0b0111101110101001},
	{'&', 0b1001010111110001},
	{'\'', 0b0000100000000000},
	{'(', 0b1001000000000000},
	{')', 0b0010010000000000},
	{'*', 0b1111111100000000},
	{'+', 0b0100101100000000},
	{',', 0b0010000000000000},
	{'-', 0b0000001100000000},
	{'/', 0b0011000000000000},
	{'0', 0b0011000011111111},
	{'1', 0b0000000000001100},
	{'2', 0b0000001101110111},
	{'3', 0b0000001100111111},
	{'4', 0b0000001110001100},
	{'5', 0b0000001110111011},
	{'6', 0b0000001111111011},
	{'7', 0b0101000000000011},
	{'8', 0b0000001111111111},
	{'9', 0b0000001110111111},
	{';', 0b0010000000000000},
	{'<', 0b1001000100000000},
	{'=', 0b0000001100110000},
	{'>', 0b0010011000000000},
	{'?', 0b0100001000000110},
	{'@', 0b0100000101111111},
	{'A', 0b0000001111001111},
	{'B', 0b0100101000111111},
	{'C', 0b0000000011110011},
	{'D', 0b0100100000111111},
	{'E', 0b0000000111110011},
	{'F', 0b0000000111000011},
	{'G', 0b0000001011111011},
	{'H', 0b0000001111001100},
	{'I', 0b0100100000110011},
	{'J', 0b0000000001111100},
	{'K', 0b1001000111000000},
	{'L', 0b0000000011110000},
	{'M', 0b0001010011001100},
	{'N', 0b1000010011001100},
	{'O', 0b0000000011111111},
	{'P', 0b0000001111000111},
	{'Q', 0b1000000011111111},
	{'R', 0b1000001111000111},
	{'S', 0b0000001110111011},
	{'T', 0b0100100000000011},
	{'U', 0b0000000011111100},
	{'V', 0b0011000011000000},
	{'W', 0b1010000011001100},
	{'X', 0b1011010000000000},
	{'Y', 0b0101010000000000},
	{'Z', 0b0011000000110011},
	{'[', 0b0100100000100010},
	{'\\', 0b1000010000000000},
	{']', 0b0100100000010001},
	{'^', 0b1010000000000000},
	{'_', 0b0000000000110000},
	{'`', 0b0000010000000000},
	{'a', 0b0100000101110000},
	{'b', 0b0000001111111000},
	{'c', 0b0000001101110000},
	{'d', 0b0000001101111100},
	{'e', 0b0010000101110000},
	{'f', 0b0100101100000010},
	{'g', 0b0000101000111110},
	{'h', 0b0000001111001000},
	{'i', 0b0100000100110000},
	{'j', 0b0000001000111000},
	{'k', 0b1101100000000001},
	{'l', 0b0100100000100001},
	{'m', 0b0100001101001000},
	{'n', 0b0000001101001000},
	{'o', 0b0000001101111000},
	{'p', 0b0100101100000110},
	{'q', 0b0100100110100001},
	{'r', 0b0000001101000000},
	{'s', 0b1000001000110000},
	{'t', 0b0100101100100000},
	{'u', 0b0000000001111000},
	{'v', 0b0010001001000000},
	{'w', 0b1010000001001000},
	{'x', 0b0111100000000000},
	{'y', 0b0000101000111100},
	{'z', 0b0010000100110000},
	{'{', 0b0100100100100010},
	{'|', 0b0100100000000000},
	{'}', 0b0100101000010001},
	{'~', 0b0000101010000101}
};

uint16_t get_mask(const char c)
{
	auto el = char_mask.find(c);
	if (el == char_mask.end()) return 0;
	return el->second;
}


void render_segment(SDL_Renderer* renderer, const uint8_t segment, SDL_FPoint origin, const float seg_len, int thickness)
{
	SDL_FPoint terminal;
	switch (segment)
	{
		case 0:
			terminal.x = origin.x + seg_len;
			terminal.y = origin.y;
			break;
		case 1:
			origin.x += seg_len;
			terminal.x = origin.x + seg_len;
			terminal.y = origin.y;
			break;
		case 2:
			origin.x += seg_len * 2;
			terminal.x = origin.x;
			terminal.y = origin.y + seg_len;
			break;
		case 3:
			origin.x += seg_len * 2;
			origin.y += seg_len;
			terminal.x = origin.x;
			terminal.y = origin.y + seg_len;
			break;
		case 4:
			origin.y += seg_len * 2;
			terminal.x = origin.x + seg_len;
			terminal.y = origin.y;
			break;
		case 5:
			origin.x += seg_len;
			origin.y += seg_len * 2;
			terminal.x = origin.x + seg_len;
			terminal.y = origin.y;
			break;
		case 6:
			origin.y += seg_len;
			terminal.x = origin.x;
			terminal.y = origin.y + seg_len;
			break;
		case 7:
			terminal.x = origin.x;
			terminal.y = origin.y + seg_len;
			break;
		case 8:
			origin.y += seg_len;
			terminal.x = origin.x + seg_len;
			terminal.y = origin.y;
			break;
		case 9:
			origin.x += seg_len;
			origin.y += seg_len;
			terminal.x = origin.x + seg_len;
			terminal.y = origin.y;
			break;
		case 10:
			terminal.x = origin.x + seg_len;
			terminal.y = origin.y + seg_len;
			break;
		case 11:
			origin.x += seg_len;
			terminal.x = origin.x;
			terminal.y = origin.y + seg_len;
			break;
		case 12:
			origin.x += seg_len * 2;
			terminal.x = origin.x - seg_len;
			terminal.y = origin.y + seg_len;
			break;
		case 13:
			origin.x += seg_len;
			origin.y += seg_len;
			terminal.x = origin.x - seg_len;
			terminal.y = origin.y + seg_len;
			break;
		case 14:
			origin.x += seg_len;
			origin.y += seg_len;
			terminal.x = origin.x;
			terminal.y = origin.y + seg_len;
			break;
		case 15:
			origin.x += seg_len;
			origin.y += seg_len;
			terminal.x = origin.x + seg_len;
			terminal.y = origin.y + seg_len;
			break;
	}

	SDL_FPoint ob = origin, tb = terminal;
	for (int i = 0; i < thickness; ++i)
	{
		float factor = (i % 2) ? -1 : 1;
		switch (segment)
		{
			case 0: [[fallthrough]];
			case 1: [[fallthrough]];
			case 8: [[fallthrough]];
			case 9:
				origin.y = ob.y + SDL_roundf(i * factor / 2);
				terminal.y = tb.y + SDL_roundf(i * factor / 2);
				break;

			case 4: [[fallthrough]];
			case 5:
				origin.y = ob.y - SDL_roundf(i * factor / 2);
				terminal.y = tb.y - SDL_roundf(i * factor / 2);
				break;

			case 2: [[fallthrough]];
			case 3:
				origin.x = ob.x - SDL_roundf(i * factor / 2);
				terminal.x = tb.x - SDL_roundf(i * factor / 2);
				break;

			case 6: [[fallthrough]];
			case 7: [[fallthrough]];
			case 11: [[fallthrough]];
			case 14:
				origin.x = ob.x + SDL_roundf(i * factor / 2);
				terminal.x = tb.x + SDL_roundf(i * factor / 2);
				break;

			case 10:
				if (i % 2)
				{
					origin.y = ob.y + SDL_roundf(i * factor / 2);
					terminal.y = tb.y + SDL_roundf(i * factor / 2);
				}
				else
				{
					origin.x = ob.x + SDL_roundf(i * factor / 2);
					terminal.x = tb.x + SDL_roundf(i * factor / 2);
				}
				break;

			case 12:
				if (i % 2)
				{
					origin.y = ob.y + SDL_roundf(i * factor / 2);
					terminal.y = tb.y + SDL_roundf(i * factor / 2);
				}
				else
				{
					origin.x = ob.x - SDL_roundf(i * factor / 2);
					terminal.x = tb.x - SDL_roundf(i * factor / 2);
				}
				break;

			case 13:
				if (i % 2)
				{
					origin.x = ob.x + SDL_roundf(i * factor / 2);
					terminal.x = tb.x + SDL_roundf(i * factor / 2);
				}
				else
				{
					origin.y = ob.y - SDL_roundf(i * factor / 2);
					terminal.y = tb.y - SDL_roundf(i * factor / 2);
				}
				break;

			case 15:
				if (i % 2)
				{
					origin.x = ob.x - SDL_roundf(i * factor / 2);
					terminal.x = tb.x - SDL_roundf(i * factor / 2);
				}
				else
				{
					origin.y = ob.y - SDL_roundf(i * factor / 2);
					terminal.y = tb.y - SDL_roundf(i * factor / 2);
				}
				break;
		}

		SDL_RenderDrawLineF(renderer, origin.x, origin.y, terminal.x, terminal.y);
	}
}


void render_dot_on_segment(SDL_Renderer* renderer, const uint8_t segment, SDL_FPoint origin, const float seg_len, const float pos, const float size)
{
	SDL_FRect dot{origin.x - (size / 2), origin.y - (size / 2), size, size};
	switch (segment)
	{
		case 0:
			dot.x += pos;
			break;
		case 1:
			dot.x += seg_len + pos;
			break;
		case 2:
			dot.x += seg_len * 2;
			dot.y += pos;
			break;
		case 3:
			dot.x += seg_len * 2;
			dot.y += seg_len + pos;
			break;
		case 4:
			dot.x += pos;
			dot.y += seg_len * 2;
			break;
		case 5:
			dot.x += seg_len + pos;
			dot.y += seg_len * 2;
			break;
		case 6:
			dot.y += seg_len + pos;
			break;
		case 7:
			dot.y += pos;
			break;
		case 8:
			dot.x += pos;
			dot.y += seg_len;
			break;
		case 9:
			dot.x += seg_len + pos;
			dot.y += seg_len;
			break;
		case 10:
			dot.x += pos;
			dot.y += pos;
			break;
		case 11:
			dot.x += seg_len;
			dot.y += pos;
			break;
		case 12:
			dot.x += (seg_len * 2) - pos;
			dot.y += pos;
			break;
		case 13:
			dot.x += seg_len - pos;
			dot.y += seg_len + pos;
			break;
		case 14:
			dot.x += seg_len;
			dot.y += seg_len + pos;
			break;
		case 15:
			dot.x += seg_len + pos;
			dot.y += seg_len + pos;
			break;
	}

	SDL_RenderFillRectF(renderer, &dot);
}


void render_dot(SDL_Renderer* renderer, SDL_FPoint dot, const float size)
{
	SDL_FRect rdot{dot.x, dot.y, size, size};
	SDL_RenderFillRectF(renderer, &rdot);
}


void render_dot(SDL_Renderer* renderer, SDL_FPoint origin, float del_x, float del_y, const float size)
{
	render_dot(renderer, SDL_FPoint{origin.x + del_x, origin.y + del_y}, size);
}


void render_mask(SDL_Renderer* renderer, const uint16_t mask, SDL_FPoint origin, const float char_len, int thickness)
{
	for (uint8_t i = 0; i < 16; ++i) if (mask & (((uint16_t) 1) << i)) render_segment(renderer, i, origin, char_len / 2, thickness);
}


void render_char(SDL_Renderer* renderer, const char chr, SDL_FPoint origin, const float char_len, int thickness)
{
	render_mask(renderer, get_mask(chr), origin, char_len, thickness++);   // Dot should be thicker than the lines.
	switch (chr)
	{
		case '.': [[fallthrough]];
		case '!': [[fallthrough]];
		case '?': render_dot(renderer, origin, char_len/2 - 1, char_len - 2, 3); break;

		case ':':
			render_dot(renderer, origin, char_len/2 - (thickness / 2), char_len - 2, thickness);
			[[fallthrough]];
		case 'i':
			render_dot(renderer, origin, char_len/2 - (thickness / 2), char_len/3 - 1, thickness);
			break;

		case 'j':
			render_dot(renderer, origin, char_len - (thickness / 2), char_len/4 - 1, thickness);
			break;

		case ';':
			render_dot(renderer, origin, char_len/4 - (thickness / 2), char_len/3 - 1, thickness);
			break;
	}
}


void render_text(SDL_Renderer* renderer, const char text[], SDL_FPoint origin, const float char_len, int char_sep, int thickness)
{
	SDL_FPoint _origin = origin;
	for (const char* i = text; *i; ++i)
	{
		render_char(renderer, *i, origin, char_len, thickness);
		switch (*i)
        {
            case '\n':
                origin.y += char_len + char_sep;
                origin.x = _origin.x;
                continue;
            case '\r':
                origin.x = _origin.x;
                continue;
            case '\t':
                origin.x += (char_len + char_sep) * (4 - ((int)((origin.x - _origin.x) / (char_len + char_sep)) % 4));
                continue;
        }
        origin.x += (char_len + char_sep);
	}
}
