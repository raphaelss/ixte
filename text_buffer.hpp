#ifndef TEXT_BUFFER_HPP_INCLUDED
#define TEXT_BUFFER_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include "processor.hpp"

namespace xts {

class text_buffer {
public:
	text_buffer(int size, sf::Font &font, processor &proc);
	void resized(double width, double height);
	void insert(sf::Uint32 ch);
	bool active() const;
	void keypress(sf::Keyboard::Key key);
	void draw(sf::RenderTarget &target);

private:
	void reset();
	void backspace();
	void delete_char();
	void right();
	void left();
	void execute();

	std::size_t _cursor;
	sf::String _buffer, _single_char;
	sf::Text _text;
	sf::Vertex _cursor_line [2];
	processor &_processor;
};

}

#endif
